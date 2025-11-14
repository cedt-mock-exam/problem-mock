#include "gentools.hpp"
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <vector>

using namespace std;

struct Airport {
  string code;
  int position;
  vector<bool> gates;
};

struct Flight {
  string src;
  int src_gate;
  string dest;
  int dest_gate;

  Flight(string s, int sg, string d, int dg)
      : src(s), src_gate(sg), dest(d), dest_gate(dg) {}
};
struct MergeNode {
  int position;
  int order;
};

const int MAX_TRIES = 2000;

enum ResultType {
  CANCEL,
  NO_CHANGE,
  ROUND_TRIVIAL,
  SHIFT_LEFT,
  ROUND_SHIFT_LEFT,
  SHIFT_RIGHT,
  ROUND_SHIFT_RIGHT,
  SHIFT_PRIORITY_LEFT,
  ROUND_SHIFT_PRIORITY_LEFT,
  SHIFT_PRIORITY_RIGHT,
  ROUND_SHIFT_PRIORITY_RIGHT,
};

string generate_gates(random_t *rnd, int length);
pair<vector<Airport>, vector<int>> generate_airports(random_t *rnd, int a,
                                                     int merge_depth = 0,
                                                     int max_group_size = -1);
pair<vector<MergeNode>, vector<int>>
generate_merge_trees(random_t *rnd, int count, int depth,
                     int max_group_size = -1);
bool pick_and_flight(random_t *rnd, vector<Airport> &airports,
                     vector<Flight> &flight_record, ResultType result_type);

int main(int argc, char **argv) {
  useGenIn(
      16, 20,
      [](int tc, random_t *rnd, ofstream *out) {
        int f, a;
        vector<Airport> static_airports, airports;
        vector<Flight> flights;

        for (int retry = 0; retry < MAX_TRIES; retry++) {
          bool ok = false;
          flights.clear();
          a = 10 + rnd->next(4);
          f = 50 + rnd->next(6);
          static_airports = generate_airports(rnd, a).first;
          airports = static_airports;

          for (int i = 0; i < f; i++) {
            int local_tries = 0;
            ok = pick_and_flight(rnd, airports, flights,
                                 (ResultType)rnd->next(0, 11));
            if (!ok) {
              i--;
              local_tries++;
              if (local_tries >= MAX_TRIES / 10) break;
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
          *out << air.code << ' ' << air.position << ' ';
          for (auto gate : air.gates)
            *out << (gate ? '1' : '0');
          *out << '\n';
        }
        for (auto &flight : flights) {
          if (flight.src_gate == -1) {
            *out << "MERGE " << flight.dest_gate << '\n';
            continue;
          }
          *out << flight.src << '[' << flight.src_gate << "] " << flight.dest
               << '[' << flight.dest_gate << "]\n";
        }
      },
      argc, argv);
  return 0;
}

string num2code(int num) {
  string res = "";
  for (int i = 0; i < 3; i++) {
    res += (char)('A' + (num % 26));
    num /= 26;
  }
  reverse(res.begin(), res.end());
  return res;
}

pair<vector<Airport>, vector<int>>
generate_airports(random_t *rnd, int a, int merge_depth, int max_group_size) {
  vector<Airport> airports;

  set<string> codes;
  set<int> positions;

  vector<MergeNode> elements;
  vector<int> kValues;
  if (merge_depth > 0) {
    tie(elements, kValues) =
        generate_merge_trees(rnd, a, merge_depth, max_group_size);
  }

  int prev_code = rnd->next(26 * 26);

  for (int i = 0; i < a; i++) {
    Airport airport;

    if (!merge_depth) {
      do {
        airport.code = num2code(rnd->next(26 * 26 * 26));
      } while (codes.count(airport.code));
      codes.insert(airport.code);

      do {
        airport.position = rnd->next(-100, 100);
      } while (positions.count(airport.position));
      positions.insert(airport.position);
    } else {
      airport.code = num2code(prev_code + rnd->next((26 * 26 * 25) / a));
      airport.position = elements[i].position;
    }

    int gate_len = 3 + rnd->next(5); // Between 3 and 7 gates
    for (int j = 0; j < gate_len; j++) {
      airport.gates.push_back(rnd->next(2));
    }

    airports.push_back(airport);
  }
  return {airports, kValues};
}

bool pick_and_flight(random_t *rnd, vector<Airport> &airports,
                     vector<Flight> &flight_record, ResultType result_type) {
  int tries = 0;
  bool ok = false;
  do {
    tries++;
    auto src = &airports[rnd->next(airports.size())];
    int src_gate = -1;
    for (int i = 0; i < src->gates.size(); i++) {
      if (src->gates[i]) {
        src_gate = i;
        break;
      }
    }
    if (src_gate == -1) continue; // No available source gate

    auto dest = &airports[rnd->next(airports.size())];
    auto dest_gate = rnd->next(dest->gates.size());

    if (result_type == CANCEL) {
      for (int i = 0; i < dest->gates.size(); i++) {
        if (!dest->gates[i] &&
            !(src->code == dest->code && src_gate == dest_gate)) {
          ok = false;
          break;
        }
      }
    } else if (result_type == NO_CHANGE)
      ok = !dest->gates[dest_gate] && src->code != dest->code;
    else if (result_type == ROUND_TRIVIAL)
      ok = !dest->gates[dest_gate] && src->code == dest->code;
    else {
      int lo = dest_gate - 1, hi = dest_gate + 1;
      int save_lo = -1, save_hi = -1;
      while ((save_lo == -1 && save_hi == -1) &&
             (lo >= 0 || hi < dest->gates.size())) {
        if (lo >= 0 && !dest->gates[lo] && save_lo == -1) {
          save_lo = lo;
        } else if (hi < dest->gates.size() && !dest->gates[hi] &&
                   save_hi == -1) {
          save_hi = hi;
        }
        lo--, hi++;
      }
      int diff = abs(save_hi - (int)dest_gate) - abs(save_lo - (int)dest_gate);
      if (diff > 0) {
        ok = (result_type == SHIFT_LEFT && src->code != dest->code) ||
             (result_type == ROUND_SHIFT_LEFT && src->code == dest->code);
      } else if (diff < 0) {
        ok = (result_type == SHIFT_RIGHT && src->code != dest->code) ||
             (result_type == ROUND_SHIFT_RIGHT && src->code == dest->code);
      } else if (result_type == SHIFT_PRIORITY_LEFT) {
        ok = (dest->gates[save_lo] < dest->gates[save_hi]) &&
             (src->code != dest->code);
      } else if (result_type == ROUND_SHIFT_PRIORITY_LEFT) {
        ok = (dest->gates[save_lo] < dest->gates[save_hi]) &&
             (src->code == dest->code);
      } else if (result_type == SHIFT_PRIORITY_RIGHT) {
        ok = (dest->gates[save_lo] > dest->gates[save_hi]) &&
             (src->code != dest->code);
      } else if (result_type == ROUND_SHIFT_PRIORITY_RIGHT) {
        ok = (dest->gates[save_lo] > dest->gates[save_hi]) &&
             (src->code == dest->code);
      }
    }

    if (ok) {
      src->gates[src_gate] = false;
      dest->gates[dest_gate] = true;
      flight_record.emplace_back(src->code, src_gate, dest->code, dest_gate);
    }
  } while (tries <= MAX_TRIES && !ok);
  return ok;
}

vector<vector<MergeNode>> test_merge(const vector<vector<MergeNode>> &groups,
                                     int k, int max_group_size = -1) {
  vector<vector<MergeNode>> result;
  vector<bool> used(groups.size(), false);

  for (int i = 0; i < groups.size(); i++) {
    if (used[i]) continue;

    vector<MergeNode> newGroup = groups[i];
    int leftmostPos = groups[i][0].position; // base position
    used[i] = true;

    // find all groups that can merge with this one
    for (int j = i + 1; j < groups.size(); j++) {
      if (used[j]) continue;

      int otherPos = groups[j][0].position; // base position of other group
      if (abs(otherPos - leftmostPos) <= k) {
        // ceck if merging would exceed group size limit
        if (max_group_size != -1 &&
            newGroup.size() + groups[j].size() > max_group_size) {
          continue; // Skip this merge to respect group size limit
        }

        // Merge groups - stack by order of bottommost elements
        if (groups[j][0].order < newGroup[0].order) {
          // Other group goes to bottom
          vector<MergeNode> temp = groups[j];
          temp.insert(temp.end(), newGroup.begin(), newGroup.end());
          newGroup = temp;
          leftmostPos = groups[j][0].position;
        } else {
          // Current group stays at bottom
          newGroup.insert(newGroup.end(), groups[j].begin(), groups[j].end());
        }
        used[j] = true;
      }
    }

    // update positions to base position
    for (auto &elem : newGroup) {
      elem.position = leftmostPos;
    }

    result.push_back(newGroup);
  }

  return result;
}

pair<vector<MergeNode>, vector<int>>
generate_merge_trees(random_t *rnd, int amount, int depth, int max_group_size) {
  vector<MergeNode> elements(amount);
  set<int> usedOrders;

  // Generate unique orders from 1 to amount
  for (int i = 0; i < amount; i++) {
    int order;
    do {
      order = rnd->next(1, amount);
    } while (usedOrders.count(order));
    usedOrders.insert(order);
    elements[i].order = order;
  }

  // Generate positions between -100 and 100
  vector<int> positions;
  set<int> usedPositions;

  for (int i = 0; i < amount; i++) {
    int pos;
    do {
      pos = rnd->next(-100, 100);
    } while (usedPositions.count(pos));
    usedPositions.insert(pos);
    positions.push_back(pos);
  }

  // Assign positions to elements
  for (int i = 0; i < amount; i++) {
    elements[i].position = positions[i];
  }

  // Sort by position as required
  sort(elements.begin(), elements.end(),
       [](const MergeNode &a, const MergeNode &b) {
         return a.position < b.position;
       });

  // Generate K values that will create the desired depth
  vector<int> kValues(depth);

  // Start with individual elements as groups
  vector<vector<MergeNode>> currentGroups;
  for (const auto &elem : elements) {
    currentGroups.push_back({elem});
  }

  // For each merge operation, calculate appropriate k value
  for (int d = 0; d < depth; d++) {
    if (currentGroups.size() <= 1) break;

    // We want to reduce the number of groups
    // Calculate distances between adjacent groups
    vector<int> distances;
    for (int i = 0; i < currentGroups.size() - 1; i++) {
      int dist =
          abs(currentGroups[i + 1][0].position - currentGroups[i][0].position);
      distances.push_back(dist);
    }

    if (distances.empty()) break;

    sort(distances.begin(), distances.end());

    // Choose k to merge some but not all groups
    // Consider group size limit when determining target groups
    int targetGroups;
    if (max_group_size == -1) {
      targetGroups = max(1, (int)currentGroups.size() / 2);
    } else {
      // With group size limit, we might not be able to merge as aggressively
      int maxPossibleMerges = 0;
      for (int i = 0; i < currentGroups.size() - 1; i++) {
        if (currentGroups[i].size() + currentGroups[i + 1].size() <=
            max_group_size) {
          maxPossibleMerges++;
        }
      }
      targetGroups = max(1, (int)currentGroups.size() - maxPossibleMerges / 2);
    }

    int k = distances[min((int)distances.size() - 1, targetGroups - 1)];

    // Ensure we actually reduce the number of groups
    if (k == 0) k = distances[0] + 1;

    kValues[d] = k;
    currentGroups = test_merge(currentGroups, k, max_group_size);

    // If we've merged everything into one group, we're done
    if (currentGroups.size() <= 1) {
      kValues.resize(d + 1);
      break;
    }
  }
  sort(
      elements.begin(), elements.end(),
      [](const MergeNode &a, const MergeNode &b) { return a.order < b.order; });
  return {elements, kValues};
}