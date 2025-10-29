#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

static void solveOne(istream& in, ostream& out) {
    int n,m,k,s;
    if(!(in >> n >> m >> k >> s)) return;

    vector<vector<pair<int,long long>>> adj[2];
    adj[0].resize(n+1);
    adj[1].resize(n+1);

    for(int i=1;i<=m;i++) {
        int u,v,type;
        long long w;
        in >> u >> v >> w >> type;
        adj[type][u].push_back({v,w});
    }

    vector<int> start(k);
    for(int i=0;i<k;i++) {
        in >> start[i];
    }

    vector<vector<vector<long long>>> dist(k,vector<vector<long long>>(2,vector<long long>(n+1,LLONG_MAX)));
    for(int i=0;i<k;i++) {
        for(int j=0;j<2;j++) {
            int source = start[i];
            dist[i][j][source] = 0;
            priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
            pq.push({0,source});
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

    long long ans = LLONG_MAX;
    vector<string> combination;
    function<void(int,string)> recur = [&](int idx,string c) {
        if(idx == k) {
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
        recur(idx+1,c + '0');
        recur(idx+1,c + '1');
    };

    recur(0,"");

    out << (ans == LLONG_MAX? -1 : ans) << '\n';
    if(ans == LLONG_MAX) return;
    for(const string& c : combination) out << c << '\n';
}

static bool hasInExtension(const fs::path& p) {
    return p.has_extension() && p.extension() == ".in";
}

static void processFile(const fs::path& inPath) {
    ifstream fin(inPath);
    if (!fin) {
        cerr << "Failed to open: " << inPath << "\n";
        return;
    }
    fs::path outPath = inPath.parent_path() / (inPath.stem().string() + ".sol");
    ofstream fout(outPath);
    if (!fout) {
        cerr << "Failed to create: " << outPath << "\n";
        return;
    }
    solveOne(fin, fout);
    cerr << "Wrote: " << outPath << "\n";
}

int main(int argc, char* argv[]) {
    vector<fs::path> targets;
    if (argc <= 1) {
        targets.push_back(fs::current_path());
    } else {
        for (int i = 1; i < argc; i++) targets.emplace_back(argv[i]);
    }

    for (const auto& t : targets) {
        if (!fs::exists(t)) {
            cerr << "Not found: " << t << "\n";
            continue;
        }
        if (fs::is_regular_file(t)) {
            if (hasInExtension(t)) processFile(t);
        } else if (fs::is_directory(t)) {
            for (const auto& entry : fs::directory_iterator(t)) {
                if (entry.is_regular_file() && hasInExtension(entry.path())) {
                    processFile(entry.path());
                }
            }
        }
    }
    return 0;
}