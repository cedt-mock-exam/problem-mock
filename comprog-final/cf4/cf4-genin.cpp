#include "gentools.hpp"
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <pthread.h>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

typedef unordered_map<string, vector<bool>> airports;

struct Flight {
  string src;
  int src_gate;
  string dest;
  int dest_gate;

  Flight(string s, int sg, string d, int dg)
      : src(s), src_gate(sg), dest(d), dest_gate(dg) {}
};

const int MAX_TRIES = 5000;

// 1-8: 1758122801

enum ResultType {
  CANCEL,
  NO_CHANGE,
  SHIFT_LEFT,
  SHIFT_RIGHT,
  SHIFT_PRIORITY,
  ANY
};

pair<airports, set<string>> generate_airports(random_t *rnd, int a, bool multiple_digit);
bool pick_and_flight(random_t *rnd, airports &airports,
                     vector<Flight> &flight_record,
                     set<string> &available_codes, ResultType result_type);
void pick_and_merge(random_t *rnd, airports &airports,
                    vector<Flight> &flight_record, set<string> &available_codes,
                    bool shuffle);

ResultType get_type(random_t *rnd, int idx) {
  if (idx == 1) return NO_CHANGE;
  if (idx == 2) return CANCEL;
  if (idx == 3) return rnd->next() < 0.33 ? NO_CHANGE : CANCEL;
  if (idx == 4) return SHIFT_LEFT;
  if (idx == 5) return SHIFT_RIGHT;
  if (idx == 6) return SHIFT_PRIORITY;
  else return ANY;
}

int main(int argc, char **argv) {
  useGenIn(
      1, 20,
      [](int tc, random_t *rnd, ofstream *out) {
        int f, a;
        airports static_airports, airports;
        set<string> available_codes;
        vector<Flight> flights;

        for (int retry = 0; retry < MAX_TRIES; retry++) {
          bool ok = false;
          flights.clear();

          if (tc <= 5) {
            a = rnd->next(2, 5);
            f = rnd->next(tc == 2 ? 3 : 8, 20);
          } else if (tc >= 5 && tc <= 10) {
            a = rnd->next(10, 20);
            f = rnd->next(20, 50);
          } else if (tc >= 11 && tc <= 14) {
            a = rnd->next(20, 30);
            f = rnd->next(50, 100);
          } else if (tc >= 15 && tc <= 20) {
            a = rnd->next(50, 75);
            f = rnd->next(100, 120);
          }

          // for paper testcase
          if (tc == 21) {
            a = 2;
            f = 2;
          } else if (tc == 22) {
            a = 3;
            f = 5;
          } else if (tc == 5) {
            a = 5;
            f = 5;
          }

          int merge_quota = rnd->next(a / 3, a - 2);

          auto res = generate_airports(rnd, a, tc >= 4);

          static_airports = res.first;
          available_codes = res.second;
          airports = static_airports;

          for (int i = 0; i < f; i++) {
            if (tc < 15) {
              ok = pick_and_flight(rnd, airports, flights, available_codes,
                                   get_type(rnd, tc));
            } else if (tc <= 20) {
              if (rnd->next() < 0.2 && merge_quota > 0 &&
                  available_codes.size() > 2 && i != f - 1) {
                pick_and_merge(rnd, airports, flights, available_codes,
                               tc >= 15);
                ok = true;
                merge_quota--;
                i--;
              } else {
                int local_tries = 0;
                ok = false;
                ok = pick_and_flight(rnd, airports, flights, available_codes,
                                     ANY);
                local_tries++;
                if (!ok && local_tries < MAX_TRIES) {
                  i--;
                }
              }
            }
            if (!ok) {
              break;
            }
          }

          if (ok) break;
          else if (retry == MAX_TRIES - 1) {
            cerr << "Test case " << tc << " failed after " << MAX_TRIES
                 << " retries." << endl;
          }
        }
        // writeout
        *out << a << ' ' << f << '\n';
        for (auto &air : static_airports) {
          *out << air.first << ' ';
          for (auto gate : air.second)
            *out << (gate ? '1' : '0');
          *out << '\n';
        }
        for (auto &flight : flights) {
          if (flight.src_gate == -1) {
            *out << "MERGE " << flight.src << ' ' << flight.dest << '\n';
            continue;
          }
          *out << flight.src << '[' << flight.src_gate << "] " << flight.dest
               << '[' << flight.dest_gate << "]\n";
        }
      },
      argc, argv, 1758255853);
  return 0;
}

pair<airports, set<string>> generate_airports(random_t *rnd, int a, bool multiple_digit) {
  airports airports;

  set<string> codes;
  for (int i = 0; i < a; i++) {
    string code;
    do {
      code = rnd->next("[A-Z]{3}");
    } while (codes.count(code));
    codes.insert(code);

    int gate_len = 3 + rnd->next(10); // Between 3 and 9 gates
    if (multiple_digit && rnd->next() < 0.7) {
      gate_len = rnd->next(10, 20);
    }
    vector<bool> gates(gate_len);
    for (int j = 0; j < gate_len; j++) {
      gates[j] = (rnd->next(2));
    }

    airports[code] = gates;
  }
  return {airports, codes};
}

bool pick_and_flight(random_t *rnd, airports &airports,
                     vector<Flight> &flight_record,
                     set<string> &available_codes, ResultType result_type) {
  int tries = 0;
  bool ok = false;
  ResultType local_result_type;
  if (result_type != ANY) local_result_type = result_type;
  do {
    tries++;
    if (result_type == ANY) {
      local_result_type = (ResultType)rnd->next(5);
    }
    auto src = rnd->any(available_codes);
    vector<int> valid_src_gate;
    for (int i = 0; i < airports[src].size(); i++) {
      if (airports[src][i]) {
        valid_src_gate.push_back(i);
      }
    }
    if (valid_src_gate.empty()) continue; // No available source gate
    int src_gate = rnd->any(valid_src_gate);

    auto dest = rnd->any(available_codes);
    auto dest_gate = rnd->wnext((int)airports[dest].size(), 4);

    int actual_gate = dest_gate;

    airports[src][src_gate] = false;

    if (local_result_type == NO_CHANGE) {
      ok = !airports[dest][dest_gate];
    } else {
      if (!airports[dest][dest_gate]) {
        ok = false;
        continue;
      }

      int lgate = -1, rgate = -1;
      int gate_size = airports[dest].size();

      for (int j = 0; dest_gate - j >= 0; j++) {
        if (!airports[dest][dest_gate - j]) {
          lgate = dest_gate - j;
          break;
        }
      }

      for (int j = 0; dest_gate + j < gate_size; j++) {
        if (!airports[dest][dest_gate + j]) {
          rgate = dest_gate + j;
          break;
        }
      }

      int sol = -1;
      if (lgate != -1 && rgate == -1) {
        sol = lgate;
      } else if (lgate == -1 && rgate != -1) {
        sol = rgate;
      } else if (lgate != -1 && rgate != -1) {
        if (abs(dest_gate - lgate) > abs(dest_gate - rgate)) {
          sol = rgate;
        } else if (abs(dest_gate - lgate) < abs(dest_gate - rgate)) {
          sol = lgate;
        } else {
          sol = lgate;
        }
      }

      if (local_result_type == SHIFT_LEFT) {
        ok = (sol != -1 && sol < dest_gate);
        actual_gate = sol;
      } else if (local_result_type == SHIFT_RIGHT) {
        ok = (sol != -1 && sol > dest_gate);
        actual_gate = sol;
      } else if (local_result_type == SHIFT_PRIORITY) {
        ok = (sol != -1);
        actual_gate = sol;
      } else if (local_result_type == CANCEL) {
        ok = (sol == -1);
      }
    }

    if (ok) {
      if (local_result_type == CANCEL) airports[src][src_gate] = true;
      else airports[dest][actual_gate] = true;
      flight_record.emplace_back(src, src_gate, dest, actual_gate);
      break;
    } else {
      airports[src][src_gate] = true;
    }

  } while (tries <= MAX_TRIES && !ok);
  return ok;
}

void pick_and_merge(random_t *rnd, airports &airports,
                    vector<Flight> &flight_record, set<string> &available_codes,
                    bool shuffle) {
  string first = rnd->any(available_codes);
  string second = rnd->any(available_codes);
  while (first == second) {
    second = rnd->any(available_codes);
  }
  if (first > second) swap(first, second);
  for (auto g : airports[second])
    airports[first].push_back(g);
  available_codes.erase(second);
  if (rnd->next(2) && shuffle) swap(first, second);
  flight_record.emplace_back(first, -1, second, -1);
}