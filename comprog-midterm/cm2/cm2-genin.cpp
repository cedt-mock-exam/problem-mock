#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------- //
// Header
const int szT[6] = {1, 1, 4, 4, 6, 4};
const int mxN[6] = {3, 3, int(3e4), int(3e4), int(3e6), int(3e6)};
const int mnN[6] = {3, 3, int(1e4), int(1e4), int(1e6), int(3e6)};
const double mxK[6] = {3, -0.000001, 3, -0.000001, 3, 3};
const double mnK[6] = {0.000001, -3, 0.000001, -3, -3, -3};
// ---------------------------------------------------- //
// Generate Method
vector<double> genSample(int n) {
    vector<double> vec(n);
    for(int i=0; i<n; ++i) {
        vec[i] = (int)(rnd.next(0, 100) + vec[i-1])%100;
    }
    return vec;
}

double getAvg(vector<double> &vec) {
    double res = accumulate(vec.begin(), vec.end(), 0.00);
    res /= (double)(vec.size());
    return res;
}

double getSD(vector<double> &vec) {
    double avg = getAvg(vec);
    double x2_sum = 0.00;
    for(auto &x: vec) x2_sum += x*x;
    return sqrt((x2_sum/vec.size())-(avg*avg));
}

double getZ(vector<double> &vec, double k) {
    return (k-getAvg(vec))/getSD(vec);
}

double getMinZ(vector<double> &vec) {
    return getZ(vec, *min_element(vec.begin(), vec.end()));
}

double getMaxZ(vector<double> &vec) {
    return getZ(vec, *max_element(vec.begin(), vec.end()));
}

bool validateSD(vector<double> &vec) {
    return getSD(vec) > 0;
}


// ---------------------------------------------------- //

int cur = 1;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(0x9e3779b9 + time(0));
    for(int T=0; T<6; ++T) {
        for(int i=0; i<szT[T]; ++i, ++cur) {

            cout << "["<<T<<","<<i<<","<<cur<<"]"; // DEBUG
            
            string fname = string(cur<10?"0":"") + to_string(cur) + ".in";
            ofstream fout;
            fout.open("testcase/" + fname);

            int n = rnd.next(mnN[T], mxN[T]);
            vector<double> vec = genSample(n);
            double k = rnd.next(max(mnK[T], getMinZ(vec)), min(mxK[T], getMaxZ(vec)));
            cout << k; // DEBUG
            for(int j=0; j<n && !validateSD(vec); ++j) vec[j]=rnd.next(0, 100);

            fout << k << "\n";
            for(auto &x: vec) fout << x << "\n";
            fout << "-1";

            cout << "\n"; // DEBUG
        }
    }
}