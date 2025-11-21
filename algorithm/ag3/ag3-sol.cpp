#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const long long MOD = 100000007;

int main() {
    for (int t = 1; t <= 20; t++) {
        string tc = to_string(t) + ".in";
        string tc2 = to_string(t) + ".sol";
        freopen(tc.c_str(), "r", stdin);
        freopen(tc2.c_str(), "w", stdout);

        long long N;
        cin >> N;

        if(N == 1){
            cout << 4 << endl;
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

        cout << ans << endl;
    }
    return 0;
}