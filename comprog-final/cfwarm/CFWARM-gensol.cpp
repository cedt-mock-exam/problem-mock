#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<string,int>lottery;

void clean(){
    lottery.clear();
}

void solve(std::istream& cin, std::ostream& cout) {
    string most;
    int mostcount = 0;
    int howmany = 0;
    while(1){
        char m;
        cin>>m;
        if(m=='E'){
            break;
        }
        else if(m=='K'){
            string number;
            cin>>number;
            if(lottery[number]==0){
                howmany++;
            }
            lottery[number]++;
            if(lottery[number]>mostcount){
                mostcount = lottery[number];
                most = number;
            }
        }
        else if(m=='P'){
            string number;
            cin>>number;
            cout<<lottery[number]<<"\n";
        }
        else if(m=='H'){
            cout<<most<<"\n";
        }
        else if(m=='N'){
            cout<<howmany<<"\n";
        }
    }
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
        clean();
        solve(fin, fout);
    }
    return 0;
}