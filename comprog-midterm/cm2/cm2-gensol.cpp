#include <bits/stdc++.h>
using namespace std;

void solve(string fname) {
    ifstream fin;
    ofstream fout;
    fin.open(fname+".in");
    fout.open(fname+".sol");
    int n = 0, xi = 0;
    double x_sum = 0, x_sum2 = 0, x_avg = 0, sd = 0, z = 0, ans = 0;
    fin >> z;
    while(fin >> xi && xi != -1) {
        x_sum += xi;
        x_sum2 += xi*xi;
        ++n;
    }
    x_avg = x_sum / n;
    sd = sqrt( (x_sum2/n) - (x_avg*x_avg) );
    ans = z*sd + x_avg;
    fout << fixed << setprecision(5) << ans;
}

int main() {
    for(int i=1; i<=20; ++i) {
        cout << "[" << i << "]"; // DEBUG
        solve("testcase/"+to_string(i));
    }
    return 0;
}