#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
vector<vector<pair<int,long long>>> adj[2];
vector<vector<vector<long long>>> dist(30,vector<vector<long long>>(2,vector<long long>(MAXN,LLONG_MAX)));
int n,m,k,s;
long long ans = LLONG_MAX;
vector<string> combination;
void recur(int i,string c) {
    if(i == k) {
        long long current = 0;
        bool walk = true;
        for(int people=0;people<k;people++) {
            if(dist[people][c[people]-'0'][s] == LLONG_MAX) {
                walk = false;
                break;
            }
            current += dist[people][c[people]-'0'][s];
        }
        if(!walk) return;
        if(current < ans) {
            combination.clear();
            combination.push_back(c);
            ans = current;
        }
        else if(current == ans) {
            combination.push_back(c);
        }
        return;
    }
    recur(i+1,c + '0');
    recur(i+1,c + '1');
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //Input the number of nodes and edges
    cin >> n >> m >> k >> s;

    // Initialize the size of graph
    adj[0].resize(n+1); adj[1].resize(n+1);;

    // Input edges
    for(int i=1;i<=m;i++) {
        int u,v,type;
        long long w;
        cin >> u >> v >> w >> type;
        adj[type][u].push_back({v,w});
    }
    // Starting point for each people
    vector<int> start(k);
    for(int i=0;i<k;i++) {
        cin >> start[i];
    }

    // Shortest path algorithm
    for(int i=0;i<k;i++) {
        for(int j=0;j<2;j++) {
            int s = start[i];
            dist[i][j][s] = 0;
            priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
            pq.push({dist[i][j][s],s});
            while(!pq.empty()) {
                auto [d,u] = pq.top();
                pq.pop();
                if(d != dist[i][j][u]) continue;
                for(auto [v,w] : adj[j][u]) {
                    if(d + w < dist[i][j][v]) {
                        dist[i][j][v] = d + w;
                        pq.push({dist[i][j][v],v});
                    }
                }
            }
        }
    }
    recur(0,"");
    cout << (ans == LLONG_MAX? -1 : ans) << '\n';
    if(ans == LLONG_MAX) return 0;
    for(string c : combination) cout << c << '\n';
}