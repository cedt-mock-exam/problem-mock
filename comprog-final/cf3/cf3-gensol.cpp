#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    for (int t = 1; t <= 20; t++) {
        string tc = to_string(t) + ".in";
        string tc2 = to_string(t) + ".sol";
        freopen(tc.c_str(), "r", stdin);
        freopen(tc2.c_str(), "w", stdout);

        ll n, q;
        cin >> n >> q;
        vector<ll> favors;
        for (int i = 0; i < n; i++) {
            ll x;
            cin >> x;
            favors.push_back(x);
        }
        for (int i = 0; i < q; i++) {
            char comd;
            cin >> comd;
            if (comd == '1') {
                ll p;
                cin >> p;
                favors.push_back(p);
            }
            else if (comd == '2') {
                assert(!favors.empty());
                favors.erase(favors.begin());
            }
            else if (comd == '3') {
                assert(!favors.empty());
                favors.pop_back();
            }
            else if (comd == '4') {
                ll x;
                cin >> x;
                for (auto &favor : favors) {
                    favor += x;
                }
            }
            else if (comd == '5') {
                ll k;
                cin >> k;
                auto it = favors.begin();
                while (it != favors.end()) {
                    if (*it < k) {
                        it = favors.erase(it);
                    }
                    else {
                        it++;
                    }
                }
            }
            else if (comd == '6') {
                ll m;
                cin >> m;
                ll sum = 0;
                assert(favors.size() >= m);
                while (m--) {
                    sum += favors.back();
                    favors.pop_back();
                }
                favors.insert(favors.begin(), sum);
            }
        }
        ll ans = 0;
        for (auto favor : favors) {
            ans += favor;
        }
        cout << favors.size() << " " << ans << endl;
        favors.clear();
    }
    return 0;
}