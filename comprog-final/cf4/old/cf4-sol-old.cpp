#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

map<string, vector<bool>> code2gate;
map<int, string> pos2code;
map<string, pair<string, int>> alias;

int main(int argc, const char **argv) {
  int a, f, merge_dist;
  cin >> a >> f;
  for (int i = 0; i < a; i++) { // airport
    string code, gate;
    int pos;
    cin >> code >> pos >> gate;
    pos2code[pos] = code;
    code2gate[code] = vector<bool>(gate.length());
    for (int j = 0; j < gate.length(); j++)
      code2gate[code][j] = (gate[j] == '1');
  }

  vector<pair<string, int>> route(2); // {{src, src_gate}, {dest, dest_gate}}
  string raw_string;
  bool has_changes = false;
  for (int i = 0; i < f; i++) {
    bool is_merging = false;
    for (int j = 0; j < 2 && !is_merging; j++) {
      cin >> raw_string;
      if (raw_string == "MERGE") {
        cin >> merge_dist;
        vector<pair<string, int>> merge_group; // {{alias, offset}}
        vector<int> deleted_pos;
        int left = pos2code.begin()->first;
        bool last = false;
        for (auto it = pos2code.begin(); it != pos2code.end() || !last; it++) {
          if (it == pos2code.end()) last = true;

          if (!last && (merge_group.empty() ||
                        it->first - left <= merge_dist)) { // merge
            merge_group.push_back({it->second, it->first});
            continue;
          }
          if (merge_group.size() > 1) {
            sort(merge_group.begin(), merge_group.end());
            for (int k = 1; k < merge_group.size(); k++) {
              deleted_pos.push_back(merge_group[k].second);
              alias[merge_group[k].first].first = merge_group[0].first;
              alias[merge_group[k].first].second =
                  code2gate[merge_group[0].first].size();
              for (auto &x : alias) {
                if (x.second.first == merge_group[k].first) {
                  x.second.first = merge_group[0].first;
                  x.second.second += alias[merge_group[k].first].second;
                }
              }
              for (auto gate : code2gate[merge_group[k].first])
                code2gate[merge_group[0].first].push_back(gate);
            }
          }
          if (last) break;
          left = it->first;
          merge_group = {{it->second, it->first}};
        }
        is_merging = true;
        for (auto pos : deleted_pos)
          pos2code.erase(pos);
      }
      if (is_merging) {
        i--;
        break;
      }

      route[j].first = raw_string.substr(0, 3);
      route[j].second = stoi(raw_string.substr(4, raw_string.length() - 5));
      if (alias.find(route[j].first) != alias.end()) {
        auto alias_info = alias[route[j].first];
        route[j].first = alias_info.first;
        route[j].second += alias_info.second;
      }
    }

    if (is_merging) continue;

    bool is_round = (route[0].first == route[1].first);
    code2gate[route[0].first][route[0].second] = false;

    if (!code2gate[route[1].first][route[1].second]) {
      code2gate[route[1].first][route[1].second] = true;
      if (is_round) {
        has_changes = true;
        cout << i << " ROUND " << route[1].first << '[' << route[1].second
             << "]\n";
      }
      continue;
    }

    has_changes = true;
    vector<bool> &dest_gate = code2gate[route[1].first];
    int lo = route[1].second - 1, hi = route[1].second + 1;
    int shifted_gate = -1;
    while (shifted_gate == -1 && (lo >= 0 || hi < dest_gate.size())) {
      if (lo >= 0 && !dest_gate[lo]) {
        dest_gate[lo] = true;
        shifted_gate = lo;
      } else if (hi < dest_gate.size() && !dest_gate[hi]) {
        dest_gate[hi] = true;
        shifted_gate = hi;
      }
      lo--, hi++;
    }
    if (shifted_gate != -1) {
      cout << i << ' ';
      if (is_round) cout << "ROUND_";
      cout << "SHIFT " << route[1].first << '[' << shifted_gate << "]\n";
      continue;
    }
    cout << i << " CANCEL\n";
    code2gate[route[0].first][route[0].second] = true;
  }

  if (!has_changes) {
    cout << "NO CHANGE";
  }

  return 0;
}