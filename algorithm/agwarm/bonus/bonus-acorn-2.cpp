#include<iostream>
using namespace std;
int main ()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int D,H,W;
    cin>>D>>H>>W;
    int arr[D+1][H+1][W+1];
    for(int k=0;k<=D;k++)
    {
        for(int i=0;i<=H;i++)
        {
            for(int j=0;j<=W;j++)
            {
                if(k == 0 || i == 0 || j == 0)
                {
                    arr[k][i][j] = 0;
                }else{
                    cin>>arr[k][i][j];
                    arr[k][i][j] += arr[k-1][i][j];
                    arr[k][i][j] += arr[k][i-1][j];
                    arr[k][i][j] += arr[k][i][j-1];
                    arr[k][i][j] -= arr[k-1][i-1][j];
                    arr[k][i][j] -= arr[k-1][i][j-1];
                    arr[k][i][j] -= arr[k][i-1][j-1];
                    arr[k][i][j] += arr[k-1][i-1][j-1];
                }
            }
        }
    }
    int Q,d1,h1,w1,d2,h2,w2;
    cin>>Q;
    while(Q--)
    {
        cin>>d1>>h1>>w1>>d2>>h2>>w2;
        cout<<(arr[d2][h2][w2] - arr[d1-1][h2][w2] - arr[d2][h1-1][w2] - arr[d2][h2][w1-1] + arr[d1-1][h1-1][w2] + arr[d1-1][h2][w1-1] + arr[d2][h1-1][w1-1] - arr[d1-1][h1-1][w1-1])<<"\n";
    }
    return 0;
}