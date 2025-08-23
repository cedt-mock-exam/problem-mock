#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    for(int in=1; in<=20; in++) {
        ofstream fout;
        fout.open(to_string(in)+".in");
        int n = rand()%1000000000,m = rand()%1000000000;
        fout << n << " "<<m;
    }
    return 0;
}