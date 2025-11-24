#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Q {
    int r, c, cnt;
    Q(int r, int c, int cnt): r(r), c(c), cnt(cnt) {}
};

queue<Q> q;
pair<int, int> pop_bus[6];

const int dr[3] = {0, 0, 1};
const int dc[3] = {-1, 1, 0};

int n, m;

char arr[5001][5001];

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for(int i=0; i<6; ++i) pop_bus[i] = {1e9, 1e9};
    cin >> n >> m;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> arr[i][j];
            if(arr[i][j] >= '1' && arr[i][j] <= '5') {
                auto &[f, s] = pop_bus[arr[i][j]-'0'];
                if(abs(i-n)+abs(j-m)<abs(f-n)+abs(s-m)) {
                    f = i;
                    s = j;
                }
            }
        }   
    }
    q.emplace(0, 0, 0);
    while(!q.empty()) {
        auto [r, c, cnt] = q.front();
        q.pop();
        if(r==n-1 && c==m-1) {
            cout << cnt;
            return 0;
        }
        for(int k=0; k<3; ++k) {
            int i = dr[k], j = dc[k];
            if(r+i>=n || c+j<0 || c+j>=m || arr[r+i][c+j] == 'X') continue;     
            q.emplace(r+i, c+j, cnt+1);
            if(arr[r+i][c+j] >= '1' && arr[r+i][c+j] <= '5') {
                auto &[f, s] = pop_bus[arr[r+i][c+j]-'0'];
                if(r+i==f&&c+j==s) continue;
                q.emplace(f, s, cnt+1);
            }       
        }
    }
    return 0;
}