#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,tw=0,th=0,fv=0,sv=0;
    cin>>n>>m;
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
    cout << "Divisible by 2 : " << tw << "\nDivisible by 3 : "<< th << "\nDivisible by 5 : "<< fv<< "\nDivisible by 7 : "<<sv; 
}