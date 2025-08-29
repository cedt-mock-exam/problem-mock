#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

const ll minn = 10;
const ll maxn = 100;
const ll mina = 0;
const ll maxa = 10000;

int main() {
    for (int t = 1; t <= 10; t++) {
        string tc = "testcase/" + to_string(t) + ".in";
        freopen(tc.c_str(), "w", stdout);

        ll temp = rnd.next(696969);
        for (int i = 1; i < temp; i++) {
            rnd.next(i);
            rnd.next(i, i);
        }
        //you gen code
        ll n = rnd.next(minn, maxn);
        cout<<n<<endl;
        for(int i=0;i<n;i++){
            cout<<rnd.next(mina, maxa)<<" ";
        }
    }
    return 0;
}
