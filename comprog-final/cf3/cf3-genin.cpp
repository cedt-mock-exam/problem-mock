#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(911);

    for (int t = 1; t <= 20; t++) {
        string filename = to_string(t) + ".in";
        freopen(filename.c_str(), "w", stdout);

        const ll minn = 1'669;
        const ll maxn = 2'000;
        const ll minq = 15'000;
        const ll maxq = 20'000;
        ll mina = 0;
        ll maxa = 1e7;


        vector<ll> comd(7, 0);

        if (t >= 1 && t <= 6) {
            comd[1] = 700; // 70%
            comd[2] = 850; // 15%
            comd[3] = 1000; // 15%
            comd[4] = 1000; // 0%
            comd[5] = 1000; // 0%
            comd[6] = 1000; // 0%
            maxa = 1000;
        }
        else if (t >= 7 && t <= 10) {
            comd[1] = 800; // 80%
            comd[2] = 900; // 10%
            comd[3] = 1000; // 10%
            comd[4] = 1000; // 0%
            comd[5] = 1000; // 0%
            comd[6] = 1000; // 0%
        }
        else if (t >= 11 && t <= 14) {
            comd[1] = 699; // 69.9%
            comd[2] = 709; // 1%
            comd[3] = 739; // 3%
            comd[4] = 999; // 26%
            comd[5] = 999; // 0%
            comd[6] = 1000; // 0.1%
        }
        else if (t >= 15 && t <= 18) {
            comd[1] = 708; // 70.8%
            comd[2] = 718; // 1%
            comd[3] = 728; // 1%
            comd[4] = 998; // 27%
            comd[5] = 1000; // 0.2%
            comd[6] = 1000; // 0%
        }
        else if (t >= 19 && t <= 20) {
            comd[1] = 797; // 79.7%
            comd[2] = 807; // 1%
            comd[3] = 837; // 3%
            comd[4] = 997; // 16%
            comd[5] = 999; // 0.2%
            comd[6] = 1000; // 0.1%
        }

        ll n = rnd.next(minn, maxn), q = rnd.next(minq, maxq);
        cout << n << " " << q << endl;
        vector<ll> favors;
        for (int i = 0; i < n; i++) {
            ll val = rnd.next(mina, maxa);
            cout << val << " ";
        }
        cout << endl;
        for (int i = 0; i < q; i++) {
            ll cur = lower_bound(comd.begin() + 1, comd.end(), rnd.next(1, 1000)) - comd.begin();
            if ((cur == 2 || cur == 3) && favors.empty()) {
                i--;
                continue;
            }
            if ((cur == 5 || cur == 6) && favors.size() <= 3) {
                i--;
                continue;
            }
            cout << cur << " ";
            if (cur == 1) {
                ll val = rnd.next(mina, maxa);
                favors.push_back(val);
                cout << val << endl;
            }
            else if (cur == 2) {
                favors.erase(favors.begin());
            }
            else if (cur == 3) {
                favors.pop_back();
            }
            else if (cur == 4) {
                ll val = rnd.next(-1 * maxa, maxa);
                for (auto &favor : favors) {
                    favor += val;
                }
                cout << val << endl;
            }
            else if (cur == 5) {
                vector<ll> temp = favors;
                sort(temp.begin(), temp.end());
                ll sus = rnd.next(1, 130); // 1.0% - 13.0% of present size
                sus = (favors.size() * sus + 1000) / 1000;
                sus--; // based 0 index
                assert(0 <= sus && sus < favors.size());
                ll val = rnd.next((sus == 0 ? temp[sus] - maxa : temp[sus - 1]), temp[sus]);
                auto it = favors.begin();
                while (it != favors.end()) {
                    if (*it < val) {
                        it = favors.erase(it);
                    }
                    else {
                        it++;
                    }
                }
                cout << val << endl;
                temp.clear();
            }
            else if (cur == 6) {
                ll val = rnd.next(1, 130); // 1.0% - 13.0% of present size
                val = (favors.size() * val + 1000) / 1000;
                ll sum = 0;
                for (int i = 0; i < val; i++) {
                    sum += favors.back();
                    favors.pop_back();
                }
                favors.insert(favors.begin(), sum);
                cout << val << endl;
            }
        }
        comd.clear();
        favors.clear();
    }
    return 0;
}