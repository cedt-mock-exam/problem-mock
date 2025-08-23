#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    for(int in=1; in<=20; in++) {
        ofstream fout;
        fout.open(to_string(in)+".in");
        int n = rand()%10000000,m = rand()%10000000+n;
        if(in<7) fout << n << " "<<m;
        else fout << m << " "<<n;
    }
    return 0;
}

