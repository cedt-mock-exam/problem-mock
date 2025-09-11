#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plpll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, q;
    cin >> n >> q;
    ll id = 0;
    multiset<pll> st;
    deque<plpll> favors;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        st.emplace(x, id);
        favors.emplace_back(x, make_pair(0, id++));
    }
    ll cur = 0;
    map<ll, bool> mp;
    for (int i = 0; i < q; i++) {
        char comd;
        cin >> comd;
        if (comd == '1') {
            ll p;
            cin >> p;
            st.emplace(p - cur, id);
            favors.emplace_back(p - cur, make_pair(cur, id++));
        }
        else if (comd == '2') {
            while (mp[favors.front().S.S]) {
                favors.pop_front();
            }
            st.erase(st.find(make_pair(favors.front().F, favors.front().S.S)));
            favors.pop_front();
        }
        else if (comd == '3') {
            while (mp[favors.back().S.S]) {
                favors.pop_back();
            }
            st.erase(st.find(make_pair(favors.back().F, favors.back().S.S)));
            favors.pop_back();
        }
        else if (comd == '4') {
            ll x;
            cin >> x;
            cur += x;
        }
        else if (comd == '5') {
            ll k;
            cin >> k;
            auto it = st.begin();
            while (it != st.end() && (it -> F) + cur < k) {
                mp[(it -> S)] = true;
                it = st.erase(it);
            }
        }
        else if (comd == '6') {
            ll m;
            cin >> m;
            ll sum = 0;
            while (m--) {
                while (mp[favors.back().S.S]) {
                    favors.pop_back();
                }
                sum += favors.back().F + cur - favors.back().S.F;
                st.erase(st.find(make_pair(favors.back().F, favors.back().S.S)));
                favors.pop_back();
            }
            st.emplace(sum - cur, id);
            favors.emplace_front(sum - cur, make_pair(cur, id++));
        }
    }
    ll ans = 0;
    for (auto e : st) {
        ans += e.F + cur;
    }
    cout << st.size() << " " << ans << "\n";
    return 0;
}