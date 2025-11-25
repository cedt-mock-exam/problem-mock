#include <bits/stdc++.h>
using namespace std;

vector<string> ans;
vector<bool> used;
string word;

void permu(int n, string t) {
    if (n == 0) {
        ans.push_back(t);
        return;
    }
    for (int i = 0; i < (int)word.size(); i++) {
        if (i != 0 && word[i] == word[i - 1] && !used[i - 1]) {
            continue;
        }
        if (!used[i]) {
            used[i] = true;
            permu(n - 1, t + word[i]);
            used[i] = false;
        }
    }
}

void solve(istream& cin, ostream& cout) {
    cin >> word;
    ans.clear();
    used.assign(word.size(), false);

    sort(word.begin(), word.end());
    permu(word.size(), "");

    cout << ans.size() << "\n";
    for (auto &s : ans) {
        cout << s << "\n";
    }
}

int main() {
    for (int t = 1; t <= 20; t++) {  // Generate for testcase 1–20
        string inPath = "testcase/" + to_string(t) + ".in";
        string solPath = "testcase/" + to_string(t) + ".sol";

        ifstream fin(inPath);
        ofstream fout(solPath);

        if (!fin.is_open() || !fout.is_open()) continue;
        solve(fin, fout);
    }
    return 0;
}
