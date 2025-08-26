#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int n, xi;
double x_sum, x_sum2, x_avg, sd, k, ans;

int main() {
    cin >> k;
    while(cin >> xi && xi != -1) {
        x_sum += xi;
        x_sum2 += xi*xi;
        ++n;
    }
    x_avg = x_sum / n;
    sd = sqrt( (x_sum2/n) - (x_avg*x_avg) );
    ans = k*sd + x_avg;
    cout << fixed << setprecision(5) << ans;
    return 0;
}