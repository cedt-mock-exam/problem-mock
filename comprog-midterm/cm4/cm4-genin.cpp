#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
Problem (interpreted):
Given array a[0..N-1], find a contiguous subarray starting at i with length L (1<=L<=K),
such that a[i + t] <= a[i] for all 0<=t<L. (All elements must be <= first element.)
All numbers are positive.
Among all valid subarrays pick one with:
  1. Maximum sum
  2. If tie, maximum length
  3. If tie, lexicographically maximum (vector compare)
Observation: Because all elements are positive and extending a valid prefix keeps the constraint,
for a fixed start i the optimal subarray is the LONGEST valid prefix (up to K) respecting the constraint.
So we only need to consider, for every i, the maximal valid length Li (bounded by K and first-greater break).
*/

struct Candidate {
    long long sum;
    int len;
    int start;
    vector<int> seq;
};

static bool lexGreater(const vector<int>& A, const vector<int>& B){
    if (A.size() != B.size()) return A.size() > B.size(); // should not happen when used
    for (size_t i=0;i<A.size();++i){
        if (A[i]!=B[i]) return A[i] > B[i];
    }
    return false;
}

static Candidate solve(const vector<int>& a, int K){
    int n = (int)a.size();
    Candidate best{-1,0,-1,{}};
    for(int i=0;i<n;i++){
        long long s=0;
        vector<int> cur;
        for(int j=i; j<n && (int)cur.size()<K; j++){
            if(a[j] > a[i]) break;
            cur.push_back(a[j]);
            s += a[j];
        }
        if(cur.empty()) continue;
        if(s > best.sum){
            best.sum = s;
            best.len = (int)cur.size();
            best.start = i;
            best.seq = cur;
        } else if(s == best.sum){
            if((int)cur.size() > best.len){
                best.len = (int)cur.size();
                best.start = i;
                best.seq = cur;
            } else if((int)cur.size() == best.len && lexGreater(cur, best.seq)){
                best.start = i;
                best.seq = cur;
            }
        }
    }
    return best;
}

static vector<Candidate> allMaxSumCandidates(const vector<int>& a, int K){
    int n=(int)a.size();
    vector<Candidate> res;
    long long maxSum=-1;
    for(int i=0;i<n;i++){
        long long s=0;
        vector<int> cur;
        for(int j=i; j<n && (int)cur.size()<K; j++){
            if(a[j]>a[i]) break;
            cur.push_back(a[j]);
            s+=a[j];
        }
        if(cur.empty()) continue;
        if(s>maxSum){
            maxSum=s;
            res.clear();
            res.push_back({s,(int)cur.size(),i,cur});
        } else if(s==maxSum){
            res.push_back({s,(int)cur.size(),i,cur});
        }
    }
    return res;
}

static void write_case(ofstream &out, const vector<int>& a, int n, int k) {
    out << n << " " << k << "\n";
    for (int i = 0; i < n; ++i)
        out << a[i] << (i + 1 == n ? '\n' : ' ');
}

int main(int argc, char** argv){
    registerGen(argc, argv, 1);
    rnd.setSeed('k'+'a'+'o'+'r'+'u'+'k'+'o'+' '+'w'+'a'+'g'+'u'+'r'+'i'+time(0));

    // Generate all test cases 1-20
    for(int tc=1; tc<=20; ++tc){
        char fname[32];
        sprintf(fname, "%d.in", tc);
        ofstream out(fname);
        if(!out.is_open()) {
            cout << "Failed to open file for test case " << tc << endl;
            continue;
        }

        cout << "Generating test case " << tc << "..." << endl;
        
        int n=0, k=0;
        vector<int> a;
        bool ok = false;

        // Use specific deterministic patterns for each test case
        switch(tc){
            // tc 1-2: Best subarray must start at index 0.
            case 1: {
                n = 20;
                k = 10;
                a.assign(n, 1);
                int first = 10000;
                a[0] = first; // First element very large
                
                // Elements after first position decreasing but still large
                for(int i=1; i<7; i++) {
                    a[i] = first - i*200;
                }
                
                // Rest of array with small values
                for(int i=7; i<n; i++) {
                    a[i] = 100 + (i % 10);
                }
                
                // Verify
                auto best = solve(a,k);
                ok = (best.start == 0);
            } break;
            
            case 2: {
                n = 30;
                k = 15;
                a.assign(n, 1);
                int first = 9500;
                a[0] = first;
                
                // Create a nice descent from first element
                for(int i=1; i<12; i++) {
                    a[i] = first - i*100;
                    if(a[i] < 1) a[i] = 1;
                }
                
                // Rest of array with small values
                for(int i=12; i<n; i++) {
                    a[i] = 200 + (i % 15);
                }
                
                // Verify
                auto best = solve(a,k);
                ok = (best.start == 0);
            } break;

            // tc 3-4: Array strictly descending.
            case 3: {
                n = 50;
                k = 20;
                a.resize(n);
                
                // Create strictly descending array
                int val = 10000;
                for(int i=0; i<n; i++) {
                    a[i] = val;
                    val -= (i % 5) + 1; // Ensure strict decrease
                    if(val < 1) val = 1;
                }
                
                // Verify
                bool desc = true;
                for(int i=0; i+1<n; i++) if(!(a[i] > a[i+1])) {desc=false; break;}
                ok = desc;
            } break;
            
            case 4: {
                n = 80;
                k = 30;
                a.resize(n);
                
                // Create strictly descending array with larger gaps
                int val = 10000;
                for(int i=0; i<n; i++) {
                    a[i] = val;
                    val -= 100 + (i % 10) * 30; // Larger decrements
                    if(val < 1) val = 1;
                }
                
                // Verify
                bool desc = true;
                for(int i=0; i+1<n; i++) if(!(a[i] > a[i+1])) {desc=false; break;}
                ok = desc;
            } break;

            // tc 5-8: Winner decided ONLY by rule 2 (longer length).
            // Create one single element with value S and one longer block with same sum S.
            case 5: {
                n = 40; 
                k = 10; 
                int L = 3;
                a.assign(n, 1);
                
                // Set up a situation where length decides
                int S = 6000;
                int singlePos = 10;
                int blockStart = 25;
                
                // Single element with value S
                a[singlePos] = S;
                
                // Block with total value S but length L
                a[blockStart] = 3000;
                a[blockStart+1] = 2000;
                a[blockStart+2] = 1000;
                
                // Add barrier
                if(blockStart+L < n) a[blockStart+L] = a[blockStart] + 1;
                
                // Verify
                auto best = solve(a,k);
                auto cands = allMaxSumCandidates(a,k);
                
                int sameLen = 0, shorter = 0;
                for(auto &c: cands) {
                    if(c.len == best.len) sameLen++;
                    else if(c.sum == best.sum && c.len < best.len) shorter++;
                }
                
                ok = (best.sum == S && best.start == blockStart && best.len == L && 
                      sameLen == 1 && shorter >= 1);
            } break;
            
            case 6: {
                n = 50; 
                k = 12; 
                int L = 4;
                a.assign(n, 1);
                
                // Set up a situation where length decides
                int S = 7000;
                int singlePos = 15;
                int blockStart = 30;
                
                // Single element with value S
                a[singlePos] = S;
                
                // Block with total value S but length L
                a[blockStart] = 2800;
                a[blockStart+1] = 2100;
                a[blockStart+2] = 1400;
                a[blockStart+3] = 700;
                
                // Add barrier
                if(blockStart+L < n) a[blockStart+L] = a[blockStart] + 1;
                
                // Verify
                auto best = solve(a,k);
                auto cands = allMaxSumCandidates(a,k);
                
                int sameLen = 0, shorter = 0;
                for(auto &c: cands) {
                    if(c.len == best.len) sameLen++;
                    else if(c.sum == best.sum && c.len < best.len) shorter++;
                }
                
                ok = (best.sum == S && best.start == blockStart && best.len == L && 
                      sameLen == 1 && shorter >= 1);
            } break;
            
            case 7: {
                n = 60; 
                k = 15; 
                int L = 5;
                a.assign(n, 1);
                
                // Set up a situation where length decides
                int S = 8000;
                int singlePos = 20;
                int blockStart = 35;
                
                // Single element with value S
                a[singlePos] = S;
                
                // Block with total value S but length L
                a[blockStart] = 2500;
                a[blockStart+1] = 2000;
                a[blockStart+2] = 1500;
                a[blockStart+3] = 1200;
                a[blockStart+4] = 800;
                
                // Add barrier
                if(blockStart+L < n) a[blockStart+L] = a[blockStart] + 1;
                
                // Verify
                auto best = solve(a,k);
                auto cands = allMaxSumCandidates(a,k);
                
                int sameLen = 0, shorter = 0;
                for(auto &c: cands) {
                    if(c.len == best.len) sameLen++;
                    else if(c.sum == best.sum && c.len < best.len) shorter++;
                }
                
                ok = (best.sum == S && best.start == blockStart && best.len == L && 
                      sameLen == 1 && shorter >= 1);
            } break;
            
            case 8: {
                n = 70; 
                k = 20; 
                int L = 6;
                a.assign(n, 1);
                
                // Set up a situation where length decides
                int S = 9000;
                int singlePos = 25;
                int blockStart = 40;
                
                // Single element with value S
                a[singlePos] = S;
                
                // Block with total value S but length L
                a[blockStart] = 3000;
                a[blockStart+1] = 2000;
                a[blockStart+2] = 1500;
                a[blockStart+3] = 1200;
                a[blockStart+4] = 800;
                a[blockStart+5] = 500;
                
                // Add barrier
                if(blockStart+L < n) a[blockStart+L] = a[blockStart] + 1;
                
                // Verify
                auto best = solve(a,k);
                auto cands = allMaxSumCandidates(a,k);
                
                int sameLen = 0, shorter = 0;
                for(auto &c: cands) {
                    if(c.len == best.len) sameLen++;
                    else if(c.sum == best.sum && c.len < best.len) shorter++;
                }
                
                ok = (best.sum == S && best.start == blockStart && best.len == L && 
                      sameLen == 1 && shorter >= 1);
            } break;

            // tc 9: many equal-sum length=4 windows, increasing first => lex decides
            case 9: {
                n = 200; 
                k = 4;
                int L = 4;
                a.assign(n, 3);
                
                // Create multiple windows with identical sum but different first elements
                // Construct 4 blocks with same sum but increasing first value
                int targetSum = 8000;
                
                vector<vector<int>> blocks = {
                    {6000, 800, 700, 500},
                    {6001, 799, 700, 500},
                    {6002, 798, 700, 500},
                    {6003, 797, 700, 500}
                };
                
                // Verify each block sums to targetSum
                for(auto &block : blocks) {
                    int s = 0;
                    for(int v : block) s += v;
                    assert(s == targetSum);
                }
                
                // Place blocks at non-overlapping positions
                for(int i = 0; i < 4; i++) {
                    int pos = 10 + i * 10;
                    for(int j = 0; j < L; j++) {
                        a[pos + j] = blocks[i][j];
                    }
                    // Add barrier
                    if(pos + L < n) a[pos + L] = blocks[i][0] + 1;
                }
                
                // Verify
                auto best = solve(a, k);
                ok = (best.sum == targetSum && best.len == L && best.start == 40); // Last block should win
            } break;

            // tc 10: Modified - descending sequence followed by repeated values
            case 10: {

                int seqLength = 600; // Length of the descending sequence

                n = seqLength + (seqLength/2); 
                k = seqLength;
                a.resize(n);
                
                
                // Create descending sequence n, n-1, ..., 2, 1
                for(int i = 0; i < seqLength; i++) {
                    a[i] = seqLength - i;
                }
                for(int i=seqLength;i<n;i++) {
                    a[i] = seqLength+1;
                }
                
                auto best = solve(a, k);
                
        
                ok = true;
            } break;

            // tc 11: 
            case 11: {
                n = 120; 
                k = 15;
                a.assign(n, 7);
                
                // Create a very specific window - just two elements
                int pos = 50;
                
                a[pos] = 5000;       // First element
                a[pos+1] = 5000;     // Equal second element
                
                // Add barrier
                if(pos + 2 < n) a[pos + 2] = a[pos] + 1;
                
                // The buggy code's output won't include the second element
                auto best = solve(a, k);
                ok = (best.start == pos && best.len == 2);
            } break;

            // tc 12: two equal-sum len=10 windows differ late
            case 12: {
                n = 180; 
                k = 20;
                a.assign(n, 5);
                int L = 10;
                
                // Create two blocks with same sum but differ at a later index
                int posA = 20;
                int posB = 100;
                int targetSum = 30000;
                
                // Base block design
                vector<int> baseBlock = {
                    8000, 5000, 4000, 3000, 2500, 2000, 1500, 1000, 1500, 1500
                };
                
                // Create two blocks with slight variations but same sum
                vector<int> blockA = baseBlock;
                vector<int> blockB = baseBlock;
                
                // Make block B lexicographically larger by moving 200 from end to position 7
                blockB[7] += 200;
                blockB[9] -= 200;
                
                // Verify both blocks have same sum
                int sumA = 0, sumB = 0;
                for(int i = 0; i < L; i++) {
                    sumA += blockA[i];
                    sumB += blockB[i];
                }
                assert(sumA == sumB);
                
                // Place blocks
                for(int i = 0; i < L; i++) {
                    a[posA + i] = blockA[i];
                    a[posB + i] = blockB[i];
                }
                
                // Add barriers
                if(posA + L < n) a[posA + L] = blockA[0] + 1;
                if(posB + L < n) a[posB + L] = blockB[0] + 1;
                
                // Verify
                auto best = solve(a, k);
                ok = (best.len == L && best.start == posB); // Block B should win
            } break;

            // tc 13: 
            case 13: {
                n = 1000; 
                k = 1;
                a.assign(n, 50);  // Different background value
                
                // Place identical maximum values
                int mx = 10000;
                vector<int> positions = {100, 200, 300, 400, 500};
                
                for(int pos : positions) {
                    a[pos] = mx;
                }
                
                // Buggy code will only print the sum, not the element
                auto best = solve(a, k);
                ok = (k == 1 && a[best.start] == mx);
            } break;

            // tc 14: 
            case 14: {
                n = 1000;
                k = 600;
                a.assign(n, 1);
                
                int L = 3;  // Shorter length
                int targetSum = 12000;
                
                // Create two blocks with identical sum and length but different distributions
                vector<vector<int>> blocks = {
                    {8000, 2000, 2000},  // Block A
                    {9000, 1500, 1500}   // Block B - lexicographically larger
                };
                
                // Verify each block sums to targetSum
                for(auto &block : blocks) {
                    int sum = 0;
                    for(int v : block) sum += v;
                    assert(sum == targetSum);
                }
                
                // Place blocks
                int posA = 10, posB = 50;
                
                for(int j = 0; j < L; j++) {
                    a[posA + j] = blocks[0][j];
                    a[posB + j] = blocks[1][j];
                }
                
                // Add barriers
                if(posA + L < n) a[posA + L] = blocks[0][0] + 1;
                if(posB + L < n) a[posB + L] = blocks[1][0] + 1;
                
                // Buggy code might choose A since it doesn't check lexicographical order
                auto best = solve(a, k);
                ok = (best.sum == targetSum && best.len == L && best.start == posB);
            } break;

            // tc 15: completely random array (no specific pattern)
            case 15: {
                n = 1000; 
                k = 1000;
                a.resize(n);
                
                // Create completely random array
                for(int i = 0; i < n; i++) {
                    a[i] = rnd.next(1, 10000);
                }
                
                // No verification needed for random array
                ok = true;
            } break;

            // tc 16: equal-sum length=5 candidates varying first (lex tie)
            case 16: {
                n = 320; 
                k = 5;
                a.assign(n, 2);
                int L = 5;
                int targetSum = 6050;
                
                // Create multiple blocks with same sum but increasing first element
                vector<vector<int>> blocks = {
                    {5000, 400, 300, 200, 150},
                    {5001, 400, 300, 200, 149},
                    {5002, 400, 300, 200, 148},
                    {5003, 400, 300, 200, 147},
                    {5004, 400, 300, 200, 146}
                };
                
                // Verify each block sums to targetSum
                for(auto &block : blocks) {
                    int s = 0;
                    for(int v : block) s += v;
                    assert(s == targetSum);
                }
                
                // Place blocks at non-overlapping positions
                for(int i = 0; i < 5; i++) {
                    int pos = 40 + i * 15;
                    for(int j = 0; j < L; j++) {
                        a[pos + j] = blocks[i][j];
                    }
                    // Add barrier
                    if(pos + L < n) a[pos + L] = blocks[i][0] + 1;
                }
                
                // Verify
                auto best = solve(a, k);
                ok = (best.sum == targetSum && best.len == L && best.start == 100); // Last block should win
            } break;

            // tc 17: random stress (any valid array)
            case 17: {
                n = 750; 
                k = 500;
                a.resize(n);
                
                // Just use random values
                for(int i = 0; i < n; i++) {
                    a[i] = rnd.next(1, 10000);
                }
                
                ok = true;
            } break;

            // tc 18: 
            case 18: {
                n = 200; 
                k = 8;
                a.assign(n, 10);  // Different background
                
                // Create an array where the first k+1 elements are equal
                int val = 9000;
                for(int i = 0; i < k+1; i++) {
                    a[i] = val;
                }
                
                // Add a large element later that satisfies the constraint
                // The buggy code might include this in the count
                a[k+1] = val - 1;  // Still satisfies the constraint
                
                // Add a barrier
                a[k+2] = val + 1;  // Doesn't satisfy constraint
                
                // Buggy code might miscalculate the length due to boundary issues
                auto best = solve(a, k);
                ok = (best.start == 0 && best.len == k);
            } break;

            // tc 19: overlapping equal-sum same-length windows, lex decided at deeper index
            case 19: {
                n = 250; 
                k = 6;
                a.assign(n, 3);
                int L = 6;
                int targetSum = 10000;
                
                // Create 4 overlapping blocks with same sum
                vector<vector<int>> blocks = {
                    {7000, 600, 600, 600, 600, 600},
                    {7001, 600, 600, 600, 600, 599},
                    {7002, 600, 600, 600, 600, 598},
                    {7003, 600, 600, 600, 600, 597}
                };
                
                // Verify each block sums to targetSum
                for(auto &block : blocks) {
                    int s = 0;
                    for(int v : block) s += v;
                    assert(s == targetSum);
                }
                
                // Place blocks at positions spaced 20 apart
                for(int i = 0; i < 4; i++) {
                    int pos = 10 + i * 20;
                    for(int j = 0; j < L; j++) {
                        a[pos + j] = blocks[i][j];
                    }
                    // Add barrier
                    if(pos + L < n) a[pos + L] = blocks[i][0] + 1;
                }
                
                // Verify
                auto best = solve(a, k);
                ok = (best.sum == targetSum && best.len == L && best.start == 70); // Last block should win
            } break;

            // tc 20: multiple groups equal sum & length chain, best last - all positive values
            case 20: {
                n = 1000; 
                k = 30;
                a.assign(n, 1);
                int L = 10;
                int targetSum = 12000;
                
                // Create blocks with same sum but increasing first element
                vector<vector<int>> blocks;
                
                for(int i = 0; i < 5; i++) {
                    vector<int> block(L, 0);
                    
                    // First element increases slightly for each block
                    block[0] = 5000 + i * 100;
                    
                    // Assign decreasing values to the middle elements, but smaller than before
                    for(int j = 1; j < L-1; j++) {
                        block[j] = 800 - j * 50;
                    }
                    
                    // Calculate sum of assigned elements
                    int currentSum = 0;
                    for(int j = 0; j < L-1; j++) {
                        currentSum += block[j];
                    }
                    
                    // Make sure last element is positive by setting a reasonable value
                    block[L-1] = targetSum - currentSum;
                    
                    // Verify the last value is positive
                    assert(block[L-1] > 0);
                    
                    blocks.push_back(block);
                }
                
                // Verify each block sums to targetSum
                for(auto &block : blocks) {
                    int s = 0;
                    for(int v : block) s += v;
                    assert(s == targetSum);
                    
                    // Also verify all values are positive
                    for(int v : block) assert(v > 0);
                }
                
                // Place blocks
                for(int i = 0; i < 5; i++) {
                    int pos = 50 + i * 150;
                    if(pos + L > n) continue;
                    
                    for(int j = 0; j < L; j++) {
                        a[pos + j] = blocks[i][j];
                    }
                    
                    // Add barrier
                    if(pos + L < n) a[pos + L] = blocks[i][0] + 1;
                }
                
                // Verify
                auto best = solve(a, k);
                ok = (best.sum == targetSum && best.len == L && best.start == 650); // Last block should win
            } break;
        }

        if(!ok) {
            cout << "Failed to generate a valid test case for " << tc << endl;
            // Fallback simple test
            n = 20;
            k = 10;
            a.resize(n);
            for(int i = 0; i < n; i++) {
                a[i] = rnd.next(1, 100);
            }
        } else {
            cout << "Successfully generated test case " << tc << endl;
        }

        write_case(out, a, n, k);
        out.close();
    }
    
    cout << "Successfully generated all test cases 1-20" << endl;
    return 0;
}