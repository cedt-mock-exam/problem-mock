#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int tc = 1; tc <= 20; tc++) {
        // เตรียมชื่อไฟล์ input/output
        string inFile = to_string(tc) + ".in";
        string outFile = to_string(tc) + ".sol";

        ifstream fin(inFile);
        ofstream fout(outFile);

        if (!fin.is_open()) {
            cerr << "Cannot open " << inFile << "\n";
            continue;
        }

        int n, m, k;
        fin >> n >> m >> k;

        // ใช้ vector แทน VLA เพื่อปลอดภัย
        vector<vector<char>> grid(n, vector<char>(m, '-'));

        while (k--) {
            char c;
            int r, x, y;
            fin >> c >> r >> x >> y;

            for (int i = x - r; i <= x + r; i++) {
                int range = r - abs(x - i);
                for (int j = y - range; j <= y + range; j++) {
                    if (i >= 0 && j >= 0 && i < n && j < m) {
                        grid[i][j] = c;
                    }
                }
            }
        }

        // print output
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fout << grid[i][j];
                if (j < m - 1) fout << ' ';
            }
            fout << '\n';
        }

        fin.close();
        fout.close();
    }

    return 0;
}
