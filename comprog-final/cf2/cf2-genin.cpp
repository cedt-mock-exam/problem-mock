#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string randomTitle() {
    int len = rnd.next(3, 6); // ชื่อยาว 3-6 ตัวอักษร
    string s;
    for (int i = 0; i < len; i++) {
        char c = (i == 0 ? rnd.next('A', 'Z') : rnd.next('a', 'z'));
        s.push_back(c);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(time(0) ^ (long)getpid());

    const int X_MIN = 1, X_MAX = 100000;
    const int N_MIN = 1, N_MAX = 100;
    const int M_MIN = 1, M_MAX = 100;
    const int PRICE_MIN = 1, PRICE_MAX = 100000;

    // (group_id, number_of_files)
    vector<pair<int,int>> groups = {
        {0, 2},  // 10%: N<=10, M<=10
        {1, 4},  // 20%: ทุกเรื่องซื้อได้
        {2, 4},  // 20%: มี >=1 เรื่องซื้อได้
        {3, 4},  // 20%: ไม่มีเรื่องไหนซื้อได้เลย
        {4, 4},  // 20%: อย่างน้อย 2 เรื่อง "ขาดเท่ากัน" แต่อันนึงซื้อไม่ได้
        {5, 2}   // 10%: ครึ่งหนึ่งขาดเท่ากัน อีกครึ่งขาดมากกว่า
    };

    filesystem::create_directories("testcase");

    int fileIdx = 1;
    for (auto &g : groups) {
        int gid = g.first, cnt = g.second;
        for (int t = 0; t < cnt; t++) {
            string fname = "testcase/" + to_string(fileIdx) + ".in";
            ofstream fout(fname);

            int X = rnd.next(X_MIN, X_MAX);
            int N = (gid == 0 ? rnd.next(1, 10) : rnd.next(N_MIN, N_MAX));
            fout << X << " " << N << "\n";

            vector<vector<int>> novels(N);
            vector<string> titles(N);

            bool atLeastOneAffordable = false;

            for (int i = 0; i < N; i++) {
                string title = randomTitle();
                int M = (gid == 0 ? rnd.next(1, 10) : rnd.next(M_MIN, M_MAX));
                vector<int> prices(M);

                for (int j = 0; j < M; j++) {
                    prices[j] = rnd.next(PRICE_MIN, PRICE_MAX);
                }

                if (gid == 1) {
                    // ทุกเรื่องเล่มแรก <= X
                    prices[0] = rnd.next(1, min(X, PRICE_MAX));
                } else if (gid == 2) {
                    // มีอย่างน้อย 1 เรื่องที่ซื้อได้
                    if (!atLeastOneAffordable && i == N-1) {
                        prices[0] = rnd.next(1, min(X, PRICE_MAX));
                        atLeastOneAffordable = true;
                    }
                } else if (gid == 3) {
                    // ทุกเรื่องเล่มแรก > X
                    prices[0] = rnd.next(X+1, PRICE_MAX);
                } else if (gid == 4) {
                    // จะปรับทีหลัง: ทำให้มี 2 เรื่องขาดเงินเท่ากัน
                }

                titles[i] = title;
                novels[i] = prices;
            }

            if (gid == 4) {
                // ต้องมีอย่างน้อย 2 เรื่อง
                if (N < 2) N = 2;

                // เรื่องแรก: ซื้อไม่ได้เลย แต่มี M เล่ม => ขาด M เล่ม
                int M1 = rnd.next(2, 5);
                novels[0].assign(M1, 0);
                novels[0][0] = X + rnd.next(1, 500);
                for (int j = 1; j < M1; j++) {
                    novels[0][j] = rnd.next(PRICE_MIN, PRICE_MAX);
                }
                titles[0] = randomTitle();

                // เรื่องที่สอง: ขาดเท่ากันกับเรื่องแรก
                int M2 = M1;
                novels[1].assign(M2, 0);
                int sum = 0;
                int buyable = rnd.next(1, M2-1);
                for (int j = 0; j < buyable; j++) {
                    int val = rnd.next(1, max(1, X / buyable));
                    novels[1][j] = val;
                    sum += val;
                }
                novels[1][buyable] = (X - sum) + rnd.next(1, 200);
                for (int j = buyable+1; j < M2; j++) {
                    novels[1][j] = rnd.next(PRICE_MIN, PRICE_MAX);
                }
                titles[1] = randomTitle();

                for (int i = 2; i < N; i++) {
                    int M = rnd.next(1, M_MAX);
                    novels[i].resize(M);
                    for (int j = 0; j < M; j++) novels[i][j] = rnd.next(PRICE_MIN, PRICE_MAX);
                    titles[i] = randomTitle();
                }
            }

            if (gid == 5) {
                int half = N / 2;
                if (half == 0) half = 1; // กัน N=1
                int baseMissing = rnd.next(1, 3); // เล่มที่ขาดเท่ากัน

                // ครึ่งแรก: ขาดเท่ากัน
                for (int i = 0; i < half; i++) {
                    int M = rnd.next(baseMissing + 1, baseMissing + 4);
                    novels[i].assign(M, 0);
                    int canBuy = M - baseMissing;
                    int remaining = X;
                    for (int j = 0; j < canBuy; j++) {
                        int val = rnd.next(1, max(1, remaining / (canBuy - j)));
                        novels[i][j] = val;
                        remaining -= val;
                    }
                    novels[i][canBuy] = remaining + rnd.next(1, 200);
                    for (int j = canBuy + 1; j < M; j++) {
                        novels[i][j] = rnd.next(PRICE_MIN, PRICE_MAX);
                    }
                    titles[i] = randomTitle();
                }

                // ครึ่งหลัง: ขาดมากกว่า baseMissing
                for (int i = half; i < N; i++) {
                    int extraMissing = rnd.next(baseMissing + 1, baseMissing + 3);
                    int M = rnd.next(extraMissing + 1, extraMissing + 4);
                    novels[i].assign(M, 0);
                    int canBuy = M - extraMissing;
                    int remaining = X;
                    for (int j = 0; j < canBuy; j++) {
                        int val = rnd.next(1, max(1, remaining / (canBuy - j)));
                        novels[i][j] = val;
                        remaining -= val;
                    }
                    novels[i][canBuy] = remaining + rnd.next(1, 200);
                    for (int j = canBuy + 1; j < M; j++) {
                        novels[i][j] = rnd.next(PRICE_MIN, PRICE_MAX);
                    }
                    titles[i] = randomTitle();
                }
            }

            // write output
            for (int i = 0; i < N; i++) {
                fout << titles[i] << " " << (int)novels[i].size() << "\n";
                for (int j = 0; j < (int)novels[i].size(); j++) {
                    if (j) fout << " ";
                    fout << novels[i][j];
                }
                fout << "\n";
            }

            fout.close();
            fileIdx++;
        }
    }
}
