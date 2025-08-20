#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

// ref https://codeforces.com/blog/entry/69370
// ref https://github.com/MikeMirzayanov/testlib
// rnd.next(a,b) = random between a-b
// use cout to show in .in file
// if you want more tc, just change t<=10
// after finish , just run this file

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // rnd.setSeed(time(0)); 
    //if you want to reset tc every run file , just uncomment

    for (int t = 1; t <= 10; t++) {
        string tc = "testcase/" + to_string(t) + ".in";
        freopen(tc.c_str(), "w", stdout);
        //you gen code
        
    }
    return 0;
}
