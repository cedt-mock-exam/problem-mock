#include <bits/stdc++.h>

using namespace std;
void solve(string ifname, string ofname) {
    ifstream fin;
    ofstream fout;
    fin.open(ifname);
    fout.open(ofname);
    int n,m,tw=0,th=0,fv=0,sv=0;
    fin>>n>>m;
    if(n>m)
    {
        int tmp;
        tmp = n;
        n = m;
        m = tmp;
    }
    for (int i = n ;i<=m;i++)
    {
        if(i%2==0)tw++;
        if(i%3==0)th++;
        if(i%5==0)fv++;
        if(i%7==0)sv++;
    }
    fout << "Divisible by 2 : " << tw << "\nDivisible by 3 : "<< th << "\nDivisible by 5 : "<< fv<< "\nDivisible by 7 : "<<sv;  
}

int main() {
    for(int i=1; i<=20; i++) {
        solve(to_string(i)+".in", to_string(i)+".sol");
    }
    return 0;
}