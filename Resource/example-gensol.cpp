#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(std::istream& cin, std::ostream& cout) {
    int n;
    cin>>n;
    int keep[n];
    for(int i=0;i<n;i++){
        cin>>keep[i];
    }
    int maxx = keep[0];
    for(int i=0;i<n;i++){
        maxx = max(maxx,keep[i]);
    }
    cout<<maxx;
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



