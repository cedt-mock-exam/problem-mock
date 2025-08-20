#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

// ref https://codeforces.com/blog/entry/69370
// ref https://github.com/MikeMirzayanov/testlib

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    rnd.setSeed(time(0));
    cout << rnd.next(5) << "\n";

    cout << rnd.next(1, 10) << "\n"; /* Random number in the range [1,10]. */

    cout << rnd.next(5.00, 500.00) << "\n";

    cout << rnd.next(10.0) << "\n"; // An equiprobable random real number in the half-interval [0;10)

    cout << rnd.next("one|two|three") << "\n"; //	An equiprobable random word out of 'one', 'two' and 'three'

    cout << rnd.next("[1-9][0-9]{5}") << "\n"; // An equiprobable random (5+1)-digit number as a string

    cout << rnd.next("[a-zA-Z0-9]{1,100}") << "\n"; /* Random word of length [1,100]. */

    cout << rnd.next("1|2|3|4|6|7|8{5}") << "\n";

    for (int i = 0; i < 10; i++) {              //An equiprobable random 10-digit number as a string but don't want some digit
        cout << rnd.next("1|2|3|4|5|8|9"); 
    } 
    cout<<"\n";

    // shuffle
    vector<int> v = {1, 2, 3, 4, 5};
    for (auto x : v)
    {
        cout << x << " ";
    }
    cout << "\n";
    shuffle(v.begin(), v.end());
    for (auto x : v)
    {
        cout << x << " ";
    }
    cout << "\n";
}