#include <bits/stdc++.h>
using namespace std;

const long long MOD = 100000007;

using Matrix = vector<vector<long long>>;

Matrix mul(Matrix a, Matrix b){
    Matrix r(4, vector<long long>(4, 0));
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            long long sum = 0;
            for(int k=0;k<4;k++){
                sum = (sum + a[i][k] * b[k][j]) % MOD;
            }
            r[i][j] = sum;
        }
    }
    return r;
}

Matrix matpow(Matrix base, long long exp){
    Matrix result(4, vector<long long>(4, 0));
    for(int i=0;i<4;i++) result[i][i]=1; // identity
    
    while(exp){
        if(exp & 1) result = mul(result, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return result;
}

int main(){
    long long N;
    cin >> N;

    if(N == 1){
        cout << 4 << "\n";
        return 0;
    }

    Matrix M = {
        {0,0,1,1}, // C from D,T
        {1,0,0,1}, // E from C,T
        {0,1,0,0}, // D from E
        {1,0,0,0}  // T from C
    };

    Matrix P = matpow(M, N-1);

    long long base[4] = {1,1,1,1};
    long long ans = 0;

    for(int i=0;i<4;i++){
        long long sum = 0;
        for(int j=0;j<4;j++){
            sum = (sum + P[i][j] * base[j]) % MOD;
        }
        ans = (ans + sum) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
