#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(std::istream& cin, std::ostream& cout) {
    //your sol
}

int main() {
    for (int t = 1; t <= 10; ++t) {
        std::string inPath  = "testcase/" + std::to_string(t) + ".in";
        std::string solPath = "testcase/" + std::to_string(t) + ".sol";
        std::ifstream fin(inPath);
        std::ofstream fout(solPath);
        if (!fin.is_open() || !fout.is_open()) {
            // cerr << "Cannot open " << inPath << " or " << solPath << "\n";
            continue;
        }
        solve(fin, fout);
    }
    return 0;
}