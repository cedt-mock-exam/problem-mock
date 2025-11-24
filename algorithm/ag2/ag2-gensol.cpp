#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Q {
    int r, c, cnt, warp;
    Q(int r, int c, int cnt, int warp): r(r), c(c), cnt(cnt), warp(warp) {}
};

queue<Q> q;
pair<int, int> pop_bus[6];
bitset<5001> vs[5001];

const int dr[3] = {0, 0, 1};
const int dc[3] = {-1, 1, 0};

int n, m;

char arr[5001][5001];

void solve(string name) {
    ifstream fin;
    fin.open("./testcase/" + name + ".in");
    ofstream fout;
    fout.open("./testcase/" + name + ".sol");
    for(int i=0; i<6; ++i) pop_bus[i] = {1e9, 1e9};
    while(!q.empty()) q.pop();
    for(int i=0; i<5001; ++i) vs[i].reset();
    fin >> n >> m;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            fin >> arr[i][j];
            if(arr[i][j] >= '1' && arr[i][j] <= '5') {
                auto &[f, s] = pop_bus[arr[i][j]-'0'];
                if(abs(i-n)+abs(j-m)<abs(f-n)+abs(s-m)) {
                    f = i;
                    s = j;
                }
            }
        }   
    }
    q.emplace(0, 0, 0, 0);
    while(!q.empty()) {
        auto [r, c, cnt, warp] = q.front();
        q.pop();
        if(r==n-1 && c==m-1) {
            fout << cnt;
            cout << name << " = " << cnt << " WARP=" << warp << "(" << n << ", " << m << ")\n"; // DEBUG
            break;
        }
        for(int k=0; k<3; ++k) {
            int i = dr[k], j = dc[k];
            if(r+i>=n || c+j<0 || c+j>=m || arr[r+i][c+j] == 'X' || vs[r+i][c+j]) continue;     
            q.emplace(r+i, c+j, cnt+1, warp);
            vs[r+i][c+j] = 1;
            if(arr[r+i][c+j] >= '1' && arr[r+i][c+j] <= '5') {
                auto &[f, s] = pop_bus[arr[r+i][c+j]-'0'];
                if(r+i==f&&c+j==s) continue;
                q.emplace(f, s, cnt+1, warp+1);
            }       
        }
    }
}

int main() {
    for(int i=1; i<=20; ++i) solve(to_string(i));
    return 0;
}