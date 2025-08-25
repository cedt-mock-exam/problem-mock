#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    for(int in=1; in<=20; in++) {
        ofstream fout;
        fout.open(to_string(in)+".in");
        int n = rand()%4999,m = rand()%5000+n;
        if(in<7) fout << n << " "<<m;
        else 
        {
            n = rand()%1000000+10000,m = rand()%1000000+n+10000;
            fout << m << " "<<n;
        }
    }
    return 0;
}

