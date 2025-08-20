#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

const ll minn = 10;
const ll maxn = 2000;
const ll mina = 1;
const ll maxa = 1e9;

// rnd.next(a,b) = random between a-b
// use cout to show in .in file
// if you want more tc, just change t<=10
// after finish , just run file c++

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
    }
    return 0;
}
