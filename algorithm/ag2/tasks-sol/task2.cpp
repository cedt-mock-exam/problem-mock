#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Q {
    int r, c, cnt;
    Q(int r, int c, int cnt): r(r), c(c), cnt(cnt) {}
};

queue<Q> q;
bitset<5001> vs[5001];

const int dr[3] = {0, 0, 1};
const int dc[3] = {-1, 1, 0};

int n, m;

char arr[5001][5001];

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> arr[i][j];
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
            if(r+i>=n || c+j<0 || c+j>=m || arr[r+i][c+j] == 'X' || vs[r+i][c+j]) continue;     
            q.emplace(r+i, c+j, cnt+1);
            vs[r+i][c+j] = 1;  
        }
    }
    return 0;
}