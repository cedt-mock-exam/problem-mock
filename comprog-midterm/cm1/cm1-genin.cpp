#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    for(int in=1; in<=6; in++) {
        ofstream fout;
        fout.open(to_string(in)+".in");
        int n = rand()%10000000,m = rand()%10000000+n;
        fout << n << " "<<m;
    }
    for(int in=7; in<=20; in++) {
        ofstream fout;
        fout.open(to_string(in)+".in");
        int n = rand()%100000000,m = rand()%100000000+n;
        fout << m << " "<<n;
    }
    return 0;
}
