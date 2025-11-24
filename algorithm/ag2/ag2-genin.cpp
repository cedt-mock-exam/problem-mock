#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------- //
// Header
const vector<int> szT[5] = {
    {1, 2, 1, 1}, // [(7, 7), (10, 10), (10, 10), (100, 100), (1000, 1000)]
    {1, 1, 1}, // [(10, 10), (50, 50), (500, 500)]
    {3, 2}, // [(7, 7), (7, 7), (7, 7), (20, 20), (20, 20)]
    {3}, // [(1000, 1000)]
    {2, 2} // [(2500, 2500), (2500, 2500), (5000, 5000), (5000, 5000)]
};
const vector<int> mxN[5] = {
    {7, 10, 100, 1000},
    {10, 50, 500},
    {7, 20},
    {1000},
    {2500, 5000}
};
const vector<int> mnN[5] = {
    {7, 9, 60, 700},
    {10, 30, 450},
    {7, 16},
    {1000},
    {2500, 5000}
};
const int max_pop[5] = {0, 0, 5, 5, 5};
const int min_pop[5] = {0, 0, 1, 1, 5};

// ---------------------------------------------------- //
// FUNCTION DECLARATION
bool valid_checker(int &n, int &m, vector<vector<char>> &adj, vector< pair<int, int> > &dest, int &pop_size, int &max_pop_size);
vector<vector<char>> genMap(int n, int m, bool isObstacle, int pop_size, int max_pop_target);
// ---------------------------------------------------- //

// ---------------------------------------------------- //
// MAP GENERATOR FUNCTION
vector<vector<char>> genMap(int n, int m, bool isObstacle, int pop_size, int max_pop_target) {

    vector<vector<char>> adj = vector<vector<char>>(n, vector<char>(m));

    // --------- GEN POP NUMBER ------------
    set<int> rand_pop;
    while(rand_pop.size() != pop_size) rand_pop.insert(rnd.next(1, 5));
    vector<int> pop_bus;
    for(auto &x: rand_pop) pop_bus.emplace_back(x);
    shuffle(pop_bus.begin(), pop_bus.end());
    // --------- -------------- ------------

    vector< pair<int, int> > dest(6, {-1, -1});

    // --------- GEN MAP WITHOUT POP BUS ------------
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            adj[i][j] = isObstacle ? rnd.next(0, 5) > 0 ? '.' : 'X' : '.';
        }
    }
    // --------- -------------- ------------

    // --------- GEN POP BUS LOCATION ------------
    for(int i=0; i<pop_size; ++i) {
        for(int j=0; j<2; ++j) {
            int r = 0, c = 0;
            while((r==0&&c==0) || (r==n-1&&c==m-1) || (adj[r][c]>='1'&&adj[r][c]<='5')) {
                r = rnd.next(0, n-1);
                c = rnd.next(0, m-1);
            }
            adj[r][c] = pop_bus[i]+'0';
            auto &[f, s] = dest[adj[r][c]-'0'];
            if(abs(r-n)+abs(c-m)<abs(f-n)+abs(s-m)) {
                f = r;
                s = c;
            }
        }
    }
    // --------- -------------- ------------

    // --------- CHOOSE REMAIN POP BUS ------------
    int cnt = max_pop_target;
    while(!pop_bus.empty()&&cnt--) pop_bus.pop_back();
    // --------- -------------- ------------
    
    // --------- BLOCK ALL REMAIN POP BUS AT THEIR DESTINATION ------------
    for(auto &x: pop_bus) {
        auto &[r, c] = dest[x];
        for(int i=-1; i<=1; ++i) {
            for(int j=-1; j<=1; ++j) {
                if(r+i<0||r+i>=n||c+j<0||c+j>=m||adj[r+i][c+j]!='.') continue;
                adj[r+i][c+j] = 'X';
            }
        }
    }
    // --------- -------------- ------------
    adj[0][0] = adj[n-1][m-1] = '.';
    return valid_checker(n, m, adj, dest, pop_size, max_pop_target) ? adj : genMap(n, m, isObstacle, pop_size, max_pop_target);
}
// ---------------------------------------------------- //
// MAP VALID CHECKER

bitset<5001> vs[5001];

const int dr[3] = {0, 0, 1}; // LEFT RIGHT BOTTOM
const int dc[3] = {-1, 1, 0};

struct Q {
    int r, c, cnt;
    Q(int r, int c, int cnt): r(r), c(c), cnt(cnt) {}
};

bool valid_checker(int &n, int &m, vector<vector<char>> &adj, vector< pair<int, int> > &dest, int &pop_size, int &max_pop_size) {
    for(int i=0; i<5001; ++i) vs[i].reset();
    queue<Q> q;
    q.emplace(0, 0, 0);
    vs[0][0] = 0;
    while(!q.empty()) {
        auto [r, c, cnt] = q.front();
        q.pop();
        for(int k=0, i, j; k<3; ++k) {
            i = dr[k], j = dc[k];
            if(r+i<0||r+i>=n||c+j<0||c+j>=m||adj[r+i][c+j]=='X'||vs[r+i][c+j]) continue;
            if(r+i==n-1&&c+j==m-1) return (pop_size == 0 && max_pop_size == 0) || (pop_size != 0 && n+m-2 != cnt+1);
            q.emplace(r+i, c+j, cnt+1);
            vs[r+i][c+j]=1;
            if(pop_size != 0 && adj[r+i][c+j]>='1'&&adj[r+i][c+j]<='5') {
                auto &[f, s] = dest[adj[r+i][c+j]-'0'];
                vs[f][s]=1;
                q.emplace(f, s, cnt+1);
            }
        }
    }
    return false;
}
// ---------------------------------------------------- //

int cur = 1;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(0x9e3779b9 + time(0));
    for(int T=0; T<5; ++T) {
        for(int k=0, t; k<szT[T].size(); ++k) {
            t = szT[T][k];
            for(int i=0; i<t; ++i, ++cur) {
                cout << "["<<T+1<<","<<t<<"->"<<i+1<<","<<cur<<"]"; // DEBUG
            
                string fname = to_string(cur) + ".in";
                ofstream fout;
                fout.open("testcase/" + fname);
                int n = rnd.next(mnN[T][k], mxN[T][k]);
                int m = rnd.next(mnN[T][k], mxN[T][k]);
                fout << n << " " << m << "\n";
                int pop_size = T!=0?rnd.next(1, 5):0;
                int max_pop_size = rnd.next(min_pop[T], max_pop[T]);
                auto adj = genMap(n, m, T!=0, pop_size, max_pop_size);
                for(int i=0; i<n; ++i) {
                    for(int j=0; j<m; ++j) {
                        fout << adj[i][j];
                    }
                    fout << "\n";
                }
                cout << "[POP="<<pop_size<<" MAX="<<max_pop_size<<"]\n";
            }
        }
    }
}