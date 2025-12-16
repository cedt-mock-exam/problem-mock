#include<iostream>
using namespace std;
int main ()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long row,col;
    long long mod = 1000000007;
    cin>>row>>col;
    char map[row+1][col+1];
    long long acorn[row+1][col+1];
    for(long long i=0;i<=row;i++)
    {
        for(long long j=0;j<=col;j++)
        {
            if(i == 0 || j == 0)
            {
                map[i][j] = '.';
                acorn[i][j] = 0;
            }else{
                cin>>map[i][j];
                if(map[i][j] == 'a')
                {
                    acorn[i][j] = 1;
                }else{
                    acorn[i][j] = 0;
                }
                acorn[i][j] += acorn[i][j-1];
                acorn[i][j] += acorn[i-1][j];
                acorn[i][j] -= acorn[i-1][j-1];
            }
        }
    }
    long long dp[1001][1001];
    for(long long i=0;i<=1000;i++)
    {
        for(long long j=0;j<=i;j++)
        {
            if(j == 1 || j == 0)
            {
                dp[i][j] = 1%mod;
            }else{
                dp[i][j] = (dp[i-1][j-1]%mod + dp[i-1][j]%mod)%mod;
            }
        }
    }
    long long t,r1,c1,r2,c2,k;
    cin>>t;
    while(t--)
    {
        cin>>r1>>c1>>r2>>c2>>k;
        long long sumacorn = acorn[r2][c2] - acorn[r2][c1-1] - acorn[r1-1][c2] + acorn[r1-1][c1-1];
        if(sumacorn<k)
        {
            cout<<"-1\n";
        }else{
            cout<<dp[sumacorn][k]%mod<<"\n";
        }
    }
    return 0;
}