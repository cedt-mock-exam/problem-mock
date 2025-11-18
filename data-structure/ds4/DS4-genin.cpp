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
    int t,i,temp;
    registerGen(argc, argv, 1);
    rnd.setSeed(1);
    for (t=1;t<=20;t++) {
        string tc = "testcase/" + to_string(t) + ".in";
        int A,B,pos1,pos2,count;
        freopen(tc.c_str(), "w", stdout);
        // determining size
        if(t<=6){
            A=20;
            B=20;
        }
        else{
            A=1e5;
            B=1e5;
        }
        // determining pos1
        if(t==2){
            pos1=0;
        }
        else{
            if(t==3){
                pos1=A-1;
            }
            else{
                pos1=rnd.next(0,A-2);
            }
        }
        // determining pos2
        pos2=rnd.next(0,B-1);
        // determining count
        if(t==1){
            count=0;
        }
        else{
            count=rnd.next(1,B-pos2);
        }
        cout << A << " " << B << endl;
        for(i=0;i<A;i++){
            temp=rnd.next(INT_MIN, INT_MAX);
            cout << temp;
            if(i!=A-1){
                cout << " ";
            }
        }
        cout << endl;
        for(i=0;i<B;i++){
            temp=rnd.next(INT_MIN, INT_MAX);
            cout << temp;
            if(i!=B-1){
                cout << " ";
            }
        }
        cout << endl;
        cout << pos1 << " " << pos2 << " " << count;
    }
    return 0;
}
