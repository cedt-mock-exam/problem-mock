#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static void write_arr(ofstream &out, const vector<int>& a, int n, int k) {
    out << n << " " << k << "\n";
    for (int i=0; i<n; ++i)
        out << a[i] << (i+1==n? "\n" : " ");
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    rnd.setSeed('k'+'a'+'o'+'r'+'u'+'k'+'o'+' '+'w'+'a'+'g'+'u'+'r'+'i'+time(0));

    // Testcases 1-8 remain unchanged.
    for (int tc = 1; tc <= 20; ++tc) {
        char fname[16];
        sprintf(fname, "%d.in", tc);
        ofstream out(fname);
        if (!out.is_open()) continue;
        
        if (tc <= 8) {
            if (tc == 1) {
                int n = rnd.next(4, 8), k = rnd.next(1, n);
                vector<int> a(n);
                a[0] = rnd.next(9000, 10000);
                for (int i=1; i<n; i++) a[i] = rnd.next(1, 500);
                write_arr(out, a, n, k);
            } else if (tc == 2) {
                int n = rnd.next(5, 10), k = rnd.next(1, n);
                vector<int> a(n);
                a[0] = rnd.next(9000, 10000);
                for (int i=1; i<n; i++) a[i] = rnd.next(1, 2000);
                write_arr(out, a, n, k);
            } else if (tc == 3) {
                int n = rnd.next(5, 9), k = rnd.next(1, n);
                vector<int> a(n);
                int cur = rnd.next(2000, 10000);
                for (int i=0; i<n; i++) { a[i]=cur; cur = max(1, cur - rnd.next(1,1500)); }
                write_arr(out, a, n, k);
            } else if (tc == 4) {
                int n = rnd.next(6, 12), k = rnd.next(1, n);
                vector<int> a(n);
                int cur = rnd.next(5000, 10000);
                for (int i=0; i<n; i++) { a[i]=cur; cur = max(1, cur - rnd.next(50,1200)); }
                write_arr(out, a, n, k);
            } else if (tc == 5) {
                int n = rnd.next(7, 12), k = rnd.next(1, n);
                vector<int> a(n);
                for (int i=0; i<n; i++) a[i] = rnd.next(1,2000);
                int pos = rnd.next(1, n-2);
                a[pos] = rnd.next(8000,10000);
                if(pos+1<n) a[pos+1] = rnd.next(1, min(1000, a[pos]));
                if(pos-1>=0) a[pos-1] = rnd.next(1, min(1000,a[pos]));
                write_arr(out, a, n, k);
            } else if (tc == 6) {
                int n = rnd.next(4, 9), k = rnd.next(1, n);
                vector<int> a(n);
                for (int i=0; i<n; i++) a[i] = rnd.next(1,2000);
                int bigpos = rnd.next(0, n-1);
                a[bigpos] = rnd.next(9000,10000);
                write_arr(out, a, n, k);
            } else if (tc == 7) {
                int n = rnd.next(4, 8), k = rnd.next(1, n);
                vector<int> a(n);
                int big = rnd.next(5000,9000);
                a[0] = big; a[1] = big;
                for (int i=2; i<n; i++) a[i] = rnd.next(1,2000);
                write_arr(out, a, n, k);
            } else if (tc == 8) {
                int n = rnd.next(5, 10), k = rnd.next(1, n);
                vector<int> a(n);
                for (int i=0; i<n-1; i++) a[i] = rnd.next(1,2000);
                a[n-1] = rnd.next(8000,10000);
                write_arr(out, a, n, k);
            }
        }
        // For tc 9..20, we want to enforce specific purposes.
        else if (tc >= 9 && tc <= 20) {
            // We'll try up to 1000 iterations or until the candidate passes the check.
            const int MAX_TRIES = 1000;
            bool ok = false;
            vector<int> a;
            int n=0, k=0;
            for (int iter = 0; iter < MAX_TRIES && !ok; iter++) {
                // Use different generation logic per test case.
                if (tc == 9) {
                    // Many equal-length candidates (length 2 windows) with SAME sum S.
                    n = rnd.next(80, 150);
                    k = 2;
                    a.assign(n, 1);
                    // Fill background with small numbers.
                    for (int i=0; i<n; i++) a[i] = rnd.next(1, 3);
                    // Pick candidate start positions
                    vector<int> idx(n-2);
                    iota(idx.begin(), idx.end(), 0);
                    shuffle(idx.begin(), idx.end());
                    vector<int> starts;
                    for (int p : idx) {
                        bool okLocal = true;
                        for (int s : starts) {
                            if (abs(p - s) < 3) { okLocal = false; break; }
                        }
                        if (okLocal) starts.push_back(p);
                        if ((int)starts.size() == 8) break;
                    }
                    sort(starts.begin(), starts.end());
                    int x0 = rnd.next(5000,9000);
                    int y0 = rnd.next(10, min(3000, x0));
                    int S = x0 + y0;
                    int countPlaced = 0;
                    for (int t = 0; t < (int)starts.size(); t++) {
                        int x = x0 + t, y = S - x;
                        if (y < 1 || y > x) continue;
                        int p = starts[t];
                        if (p+1 < n) { a[p] = x; a[p+1] = y; }
                        if (p+2 < n) { a[p+2] = x+1; } // barrier
                        countPlaced++;
                    }
                    ok = (countPlaced >= 2); // must have at least 2 candidate windows
                }
                else if (tc == 10) {
                    // Equal-sum pairs; we want earlier candidate's pair to be lex larger.
                    n = rnd.next(60,150);
                    k = rnd.next(2, n);
                    a.assign(n, rnd.next(1,10000));
                    auto pick_pos2 = [&](int pos1, int len)->int {
                        vector<int> cand;
                        for (int p = 0; p <= n-len; p++) {
                            if (abs(p - pos1) >= len)
                                cand.push_back(p);
                        }
                        return cand.empty() ? max(0, min(n-len, pos1+len)) : cand[rnd.next(0, (int)cand.size()-1)];
                    };
                    int pos1 = rnd.next(0, n-2);
                    int pos2 = pick_pos2(pos1, 2);
                    int p1 = rnd.next(3000,9000), q1 = rnd.next(2, p1);
                    int S = p1 + q1;
                    int low = max(p1+1, (S+1)/2), high = min(10000, S-1);
                    if (low > high) low = (S+1)/2;
                    int p2 = rnd.next(low, high);
                    int q2 = S - p2;
                    if (q2 > p2) swap(p2, q2);
                    a[pos1] = p1; if(pos1+1<n) a[pos1+1] = q1;
                    a[pos2] = p2; if(pos2+1<n) a[pos2+1] = q2;
                    // Check condition: earlier pair lex larger i.e. a[pos1] > a[pos2]
                    ok = (a[pos1] > a[pos2]);
                }
                else if (tc == 11) {
                    // Longer vs. shorter tie on sum: insert a subarray of length=3 and a single element with same sum.
                    n = rnd.next(100,200);
                    k = rnd.next(3, n);
                    a.assign(n, rnd.next(1,10000));
                    int posL = rnd.next(0, n-3);
                    int posS = rnd.next(0, n);
                    while (abs(posS - posL) < 3 && n>=6)
                        posS = rnd.next(0, n);
                    int p0 = rnd.next(5000,9500);
                    int t1 = rnd.next(1, min(4000, p0));
                    int t2 = rnd.next(1, min(4000, p0));
                    int S = p0 + t1 + t2;
                    a[posL] = p0; 
                    if(posL+1<n) a[posL+1] = t1;
                    if(posL+2<n) a[posL+2] = t2;
                    a[posS] = S;
                    // Check: S equals the 3-element block sum.
                    ok = (S == (a[posL] + a[posL+1] + a[posL+2]));
                }
                else if (tc == 12) {
                    // Deep lex: two length-4 blocks with equal sum; block B must be lex larger at index1.
                    n = rnd.next(80,160);
                    k = rnd.next(4, n);
                    a.assign(n, rnd.next(1,10000));
                    auto pick_pos2 = [&](int pos1, int len)->int {
                        vector<int> cand;
                        for (int p =0; p<= n-len; p++){
                            if (abs(p - pos1)>= len) cand.push_back(p);
                        }
                        return cand.empty() ? max(0, min(n-len, pos1+len)) : cand[rnd.next(0, (int)cand.size()-1)];
                    };
                    int posA = rnd.next(0, n-4);
                    int posB = pick_pos2(posA, 4);
                    if (posA > posB) swap(posA, posB);
                    int p0 = rnd.next(6000,10000);
                    int a1 = rnd.next(1, p0);
                    int a2 = rnd.next(1, p0);
                    int a3 = rnd.next(100, p0);
                    int maxDelta = min({p0 - a1, a3 - 1, 2000});
                    if (maxDelta < 1) maxDelta = 1;
                    int d = rnd.next(1, maxDelta);
                    // Set block A and block B so that the sum is equal
                    a[posA]   = p0; a[posA+1] = a1;       a[posA+2] = a2;       a[posA+3] = a3;
                    a[posB]   = p0; a[posB+1] = a1 + d;   a[posB+2] = a2;       a[posB+3] = a3 - d;
                    // Check condition: equal sum and block B lex larger (compare at index 1)
                    int sumA = p0 + a1 + a2 + a3;
                    int sumB = p0 + (a1+d) + a2 + (a3-d);
                    ok = (sumA==sumB && (a[posB+1] > a[posA+1]));
                }
                else if (tc == 13) {
                    // Three equal-sum, equal-length blocks; want the third one lex largest.
                    n = rnd.next(120,220);
                    k = rnd.next(3, n);
                    a.assign(n, rnd.next(1,10000));
                    int L = rnd.next(3,6);
                    vector<int> starts;
                    vector<int> ids(n - L + 1);
                    iota(ids.begin(), ids.end(), 0);
                    shuffle(ids.begin(), ids.end());
                    for (int p : ids) {
                        bool okLocal = true;
                        for (int s: starts)
                            if (abs(s-p) < L) { okLocal = false; break; }
                        if (okLocal) { starts.push_back(p); }
                        if (starts.size() == 3) break;
                    }
                    if (starts.size() < 3) { starts = {0, L, 2*L}; }
                    // Set first block A, second block B, third block C.
                    int p0 = rnd.next(5000,9000);
                    vector<int> base(L-1);
                    for (int i=0; i<L-1; i++) {
                        base[i] = rnd.next(1, min(4000, p0));
                    }
                    // Fill block A exactly
                    for (int i=0; i<L; i++) {
                        if(i==0) a[starts[0]] = p0;
                        else a[starts[0]+i] = base[i-1];
                    }
                    // Block B: adjust second element by d1
                    int d1 = rnd.next(1,300);
                    a[starts[1]] = p0;
                    for (int i=0; i<L; i++) {
                        if(i==0) continue;
                        a[starts[1]+i] = base[i-1];
                    }
                    a[starts[1]+1] = base[0] + d1;
                    a[starts[1]+L-1] = base.back() - d1;
                    // Block C: adjust second element by (d1+d2)
                    int d2 = rnd.next(1,300);
                    a[starts[2]] = p0;
                    for (int i=0; i<L; i++) {
                        if(i==0) continue;
                        a[starts[2]+i] = base[i-1];
                    }
                    a[starts[2]+1] = base[0] + d1 + d2;
                    a[starts[2]+L-1] = base.back() - (d1+d2);
                    // Check: sum of each block equal? And lex order: block C > block B >= block A
                    auto block = [&](int start) -> vector<int> {
                        vector<int> ret;
                        for (int i=0; i<L; i++)
                            ret.push_back(a[start+i]);
                        return ret;
                    };
                    vector<int> A = block(starts[0]), B = block(starts[1]), C = block(starts[2]);
                    int sumA = accumulate(A.begin(), A.end(), 0);
                    int sumB = accumulate(B.begin(), B.end(), 0);
                    int sumC = accumulate(C.begin(), C.end(), 0);
                    ok = (sumA==sumB && sumB==sumC && lexicographical_compare(B.begin(),B.end(),A.begin(),A.end())==false && lexicographical_compare(C.begin(),C.end(),B.begin(),B.end())==false);
                }
                else if (tc == 14) {
                    // All-equal values.
                    n = rnd.next(80,200);
                    k = rnd.next(2, max(2, n/10));
                    int val = rnd.next(10,1000);
                    a.assign(n, val);
                    ok = true;  // trivially all equal.
                }
                else if (tc == 15) {
                    // n = k = 500 full-length random (no extra check needed).
                    n = 500; k = 500;
                    a.resize(n);
                    for (int i=0; i<n; i++) a[i] = rnd.next(1,10000);
                    ok = true;
                }
                else if (tc == 16) {
                    // Large N with many equal-sum pairs injected.
                    n = rnd.next(300,500);
                    k = rnd.next(2, max(2, n/2));
                    a.assign(n, rnd.next(1,10000));
                    int injections = 20;
                    for (int t=0; t<injections; t++) {
                        int pos1 = rnd.next(0, n-2);
                        int x = rnd.next(400,8000);
                        int y = rnd.next(2, x);
                        int S = x+y;
                        int x2low = max(x-50, (S+1)/2);
                        int x2high = min(10000, S-1);
                        if (x2low> x2high) x2low = (S+1)/2;
                        int x2 = rnd.next(x2low, x2high);
                        int y2 = S - x2;
                        a[pos1]=x; a[pos1+1]=y;
                        int pos2 = pos1 + rnd.next(2,20);
                        if (pos2 > n-2) pos2 = n-2;
                        a[pos2]=x2; a[pos2+1]=y2;
                    }
                    // Check: see if at least one pair injection exists.
                    ok = true;
                }
                else if (tc == 17) {
                    // k = 1: several max elements.
                    n = rnd.next(100,300);
                    k = 1;
                    a.assign(n, rnd.next(1,9999));
                    int mx = 10000;
                    for (int t=0; t<5; t++) {
                        a[rnd.next(0, n-1)] = mx;
                    }
                    // Check that at least one element equals 10000.
                    ok = (find(a.begin(), a.end(), 10000) != a.end());
                }
                else if (tc == 18) {
                    // Two length-7 blocks that differ at index 3.
                    n = rnd.next(100,200);
                    k = rnd.next(7, n);
                    a.assign(n, rnd.next(1,10000));
                    auto pick_pos2 = [&](int pos1, int len)->int {
                        vector<int> cand;
                        for (int p=0; p<= n-len; p++){
                          if (abs(p-pos1)>=len) cand.push_back(p);
                        }
                        return cand.empty()? max(0, min(n-len, pos1+len)) : cand[rnd.next(0,(int)cand.size()-1)];
                    };
                    int L = 7;
                    int posA = rnd.next(0, n-L);
                    int posB = pick_pos2(posA, L);
                    if (posA > posB) swap(posA,posB);
                    int p0 = rnd.next(6000,10000);
                    vector<int> tail(L-1);
                    for (int i=0; i<L-1; i++) tail[i] = rnd.next(1, min(4000, p0));
                    int d = rnd.next(1, min(300, tail.back()-1));
                    for (int i=0; i<L; i++) {
                        if(i==0){ a[posA] = p0; a[posB] = p0; }
                        else { a[posA+i] = tail[i-1]; a[posB+i] = tail[i-1]; }
                    }
                    a[posB+1+2] = tail[2] + d; // index 3 in block B increased
                    a[posB+1+L-2] = tail.back() - d; // last decreased
                    // Check: block B is lex larger at index 3
                    ok = (a[posB+1+2] > a[posA+1+2]);
                }
                else if (tc == 19) {
                    // Early break on larger next element and equal-sum pair tie.
                    n = rnd.next(120,220);
                    k = rnd.next(2, max(2, n/3));
                    a.assign(n, rnd.next(1,10000));
                    int pos = rnd.next(0, n-2);
                    a[pos]   = rnd.next(100,9000);
                    a[pos+1] = rnd.next(a[pos]+1, 10000);
                    int p1 = rnd.next(1000,6000);
                    int q1 = rnd.next(2, p1);
                    int S = p1+q1;
                    int x2 = rnd.next(max((S+1)/2, p1-500), S-1);
                    int y2 = S - x2;
                    int pair1 = rnd.next(0, n-2);
                    int pair2 = rnd.next(0, n-2);
                    while(abs(pair2-pair1)<2)
                        pair2 = rnd.next(0, n-2);
                    a[pair1] = p1; a[pair1+1] = q1;
                    a[pair2] = x2; a[pair2+1] = y2;
                    ok = true; // assume injection success.
                }
                else if (tc == 20) {
                    // n = k = 500, many tied windows with increasing lex order.
                    n = 500; k = 500;
                    a.resize(n);
                    for (int i=0; i<n; i++) a[i] = rnd.next(1,10000);
                    int inject = 16;
                    for (int t=0; t<inject; t++) {
                        int pos = rnd.next(0, n-4);
                        int S = rnd.next(2000,9500);
                        int u = rnd.next(1, S-3);
                        int v = rnd.next(1, S-u-2);
                        int w = rnd.next(1, S-u-v-1);
                        int z = S - u - v - w;
                        int bump = min(50, min(10000 - u, S - (u+v+w) - 1));
                        if(bump < 0) bump = 0;
                        int u2 = min(10000, u + (t/2));
                        int rem = S - u2;
                        int v2 = min(rem-1, v);
                        int w2 = min(rem - v2 - 1, w);
                        int z2 = rem - v2 - w2;
                        if(z2 < 1){ z2 = 1; w2 = max(1, rem - v2 - z2); }
                        a[pos]   = u2;
                        a[pos+1] = v2;
                        a[pos+2] = w2;
                        a[pos+3] = z2;
                    }
                    ok = true;
                }
                // End of generation for current tc.
            } // end for(MAX_TRIES)
            write_arr(out, a, n, k);
        } // end tc>=9
        cout << tc << '\n';
        out.close();
    }
    return 0;
}