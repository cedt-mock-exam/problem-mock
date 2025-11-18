#include <bits/stdc++.h>
#include "list_for_gensol.h"
#include "student_sol.h"
using namespace std;
using ll = long long;

void solve(std::istream& cin, std::ostream& cout) {
    int A, B;
    cin >> A >> B;
    int t,pos1,pos2,count;
    CP::list<int> l1;
    CP::list<int> l2;
    for(int i=0;i<A;i++){
        cin >> t;
        l1.push_back(t);
    }
    for(int i=0;i<B;i++){
        cin >> t;
        l2.push_back(t);
    }
    cin >> pos1 >> pos2 >> count;
    l1.implant(l2,pos1,pos2,count);
    cout << l1.size() << "\n";
    l1.print_gensol(cout);
    cout << l2.size() << "\n";
    l2.print_gensol(cout);
}

int main() {
    for (int t = 1; t <= 20; ++t) {
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