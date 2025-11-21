#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(67);

    vector<ll> fixed = {2, 5, 6, 7};
    ll last = 7;

    for(int t = 1; t <= 20; t++) {
        string filename = to_string(t) + ".in";
        freopen(filename.c_str(), "w", stdout);

        ll val;
        if(t <= 4) {
            val = fixed[t-1];
            last = val;
        } else {
            ll max_val;
            if(t <= 10) max_val = 30;
            else max_val = 1000000;

            int remaining = 10 - t;
            ll upper_bound = max_val - remaining;
            ll lower_bound = last + 1;

            if(lower_bound > upper_bound) {
                val = upper_bound;
            } else {
                val = rnd.next(lower_bound, upper_bound);
            }

            last = val;
        }

        cout << val << endl;
    }

    return 0;
}
