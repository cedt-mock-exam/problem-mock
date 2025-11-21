#include <bits/stdc++.h>
using namespace std;

const long long MOD = 100000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    cin >> N;

    if(N == 1){
        cout << 4 << "\n";
        return 0;
    }

    // dp[i] = number of strings ending with C,E,D,T
    long long dp[4] = {1,1,1,1};  // base case: N=1
    long long next[4];

    for(long long i = 2; i <= N; i++){
        next[0] = (dp[2] + dp[3]) % MOD; // C can follow D or T
        next[1] = (dp[0] + dp[3]) % MOD; // E can follow C or T
        next[2] = dp[1] % MOD;           // D can follow E
        next[3] = dp[0] % MOD;           // T can follow C

        for(int j=0;j<4;j++) dp[j] = next[j];
    }

    long long ans = 0;
    for(int i=0;i<4;i++) ans = (ans + dp[i]) % MOD;

    cout << ans << "\n";
}
