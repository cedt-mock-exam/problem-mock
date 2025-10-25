#include <bits/stdc++.h>
using namespace std;

enum class actype { REG, CAN };

struct Action {
    actype type;
    string ename; 
    string mb;
    bool en = true;
};

void solve(string ifname, string ofname) {
    ifstream fin;
    ofstream fout;
    fin.open(ifname);
    fout.open(ofname);

    map<string, set<string>> evnt;
    map<string, string> bl;
    stack<Action> und;

    int N; 
    fin>>N;
    while (N--) {
        string cmd; 
        fin >> cmd;

        if (cmd == "ADDEVENT") {
            string e; fin >> e;
            evnt.emplace(e, set<string>());
        }
        else if (cmd == "REGISTER") {
            string e, name; 
            fin >> e >> name;
            auto &S = evnt[e];

            bool ok = true;
            auto itb = bl.find(name);
            if (itb != bl.end()) {
                if (itb->second != e) ok = false;
                else ok = false;
            }

            if (ok) {
                bool insrt = S.insert(name).second;
                if (insrt) {
                    bl[name] = e;
                    und.push(Action{actype::REG, e, name, true});
                } else {
                    und.push(Action{actype::REG, e, name, false});
                }
            } else {
                und.push(Action{actype::REG, e, name, false});
            }
        }
        else if (cmd == "CANCEL") {
            string e, name; 
            fin >> e >> name;

            bool rm = false;
            auto itE = evnt.find(e);
            if (itE != evnt.end()) {
                auto &S = itE->second;
                auto itM = S.find(name);
                if (itM != S.end() && bl.count(name) && bl[name] == e) {
                    S.erase(itM);
                    bl.erase(name);
                    rm = true;
                }
            }
            und.push(Action{actype::CAN, e, name, rm});
        }
        else if (cmd == "SHOW") {
            string e; fin >> e;
            auto it = evnt.find(e);
            if (it == evnt.end() || it->second.empty()) {
                fout << "\n";
            } else {
                bool first = true;
                for (auto &name : it->second) {
                    if (!first) fout << ' ';
                    fout << name;
                    first = false;
                }
                fout << "\n";
            }
        }
        else if (cmd == "UNDO") {
            if (und.empty()) continue;
            Action a = und.top(); und.pop();
            if (!a.en) continue;

            if (a.type == actype::REG) {
                auto itE = evnt.find(a.ename);
                if (itE != evnt.end()) itE->second.erase(a.mb);
                auto itB = bl.find(a.mb);
                if (itB != bl.end() && itB->second == a.ename) {
                    bl.erase(itB);
                }
            } else {
                auto &S = evnt[a.ename]; 
                S.insert(a.mb);
                bl[a.mb] = a.ename;
            }
        }
        else {
            string rs; getline(fin, rs);
        }
    }
}

int main() {
    for(int i=1; i<=20; i++) {
        solve(to_string(i)+".in", to_string(i)+".sol");
    }
    return 0;
}