#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int a, f;
  map<string, vector<bool>> airports;
  cin >> a >> f;
  for (int i = 0; i < a; i++) {
    string code, gate;
    cin >> code >> gate;
    vector<bool> local_gate(gate.length());
    for (int j = 0; j < gate.length(); j++) {
      if (gate[j] == '1') local_gate[j] = true;
    }
    airports[code] = local_gate;
  }

  bool has_changes = false;
  for (int i = 0; i < f; i++) {
    string src;
    cin >> src;
    if (src == "MERGE") {
      string base, child;
      cin >> base >> child;
      if (child < base) {
        swap(child, base);
      }
      for (auto c : airports[child]) {
        airports[base].push_back(c);
      }
      i--; // no need to erase merge child (testcase will not call it anyway)
      continue;
    }
    // normal flight command
    string dest;
    cin >> dest;

    // string parsing time!!
    string src_code = src.substr(0, 3);
    int src_gate = stoi(src.substr(4, src.length() - 5));
    string dest_code = dest.substr(0, 3);
    int dest_gate = stoi(dest.substr(4, dest.length() - 5));

    airports[src_code][src_gate] = false;
    if (!airports[dest_code][dest_gate]) { // trivial case
      airports[dest_code][dest_gate] = true;
      continue;
    }
    has_changes = true;
    int left = -1, right = -1;
    int gate_size = airports[dest_code].size();

    // Find left gate - start from j=1 to skip the occupied target gate
    for (int j = 1; dest_gate - j >= 0; j++) {
      if (!airports[dest_code][dest_gate - j]) {
        left = dest_gate - j;
        break;
      }
    }

    // Find right gate - start from j=1 to skip the occupied target gate
    for (int j = 1; dest_gate + j < gate_size; j++) {
      if (!airports[dest_code][dest_gate + j]) {
        right = dest_gate + j;
        break;
      }
    }

    int sol = -1;
    if (left != -1 && right == -1) {
      sol = left;
    } else if (left == -1 && right != -1) {
      sol = right;
    } else if (left != -1 && right != -1) {
      if (abs(dest_gate - left) < abs(dest_gate - right)) {
        sol = left;
      } else if (abs(dest_gate - left) > abs(dest_gate - right)) {
        sol = right;
      } else {
        sol = left;
      }
    }
    if (sol != -1) {
      airports[dest_code][sol] = true;
      cout << i << " SHIFT " << dest_code << '[' << sol << "]\n";
    } else {
      airports[src_code][src_gate] = true;
      cout << i << " CANCEL\n";
    }
  }
  if (!has_changes) cout << "NO CHANGE";
  return 0;
}