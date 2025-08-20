#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(), (x).end()

int main() 
{
    int n,k;
    cin >> n >> k;
    int cake[n];
    for(int i=0;i<n;i++) {
        cin >> cake[i];
    }
    int max_length = 0;
    int max_sum = 0;
    int ans_cake[n];
    for(int i=0;i<n;i++) {
        ans_cake[i] = -1;
    }
    for(int i=0;i<n;i++) {
        int current_cake[n];
        for(int j=0;j<n;j++) {
            current_cake[j] = -1;
        }
        int new_cake_length = 0;
        int new_sum = 0;
        for(int j=i;j<n;j++) {
            if(new_cake_length == k) break;

            if(cake[j] <= cake[i]) {
                new_sum += cake[j];
                current_cake[new_cake_length] = cake[j];
                new_cake_length++;
            }
            else break;
        }
        if(new_sum > max_sum) {
            max_length = new_cake_length;
            for(int j=0;j<new_cake_length;j++) {
                ans_cake[j] = current_cake[j];
            }
            max_sum = new_sum;
        }
        else if(new_sum == max_sum && new_cake_length >= max_length) {
            bool change = (new_cake_length > max_length);
            for(int j=0;j<new_cake_length;j++) {
                if(change) break;

                if(ans_cake[j] == current_cake[j]) {
                    continue;
                }
                else if(ans_cake[j] > current_cake[j]) {
                    break;
                }
                else {
                    change = true;
                    break;
                }
            }
            if(change) {
                for(int j=0;j<new_cake_length;j++) {
                    ans_cake[j] = current_cake[j];
                }
                max_length = new_cake_length;
            }
        }
    }
    cout << max_sum << endl;
    for(int i=0;i<max_length;i++) {
        cout << ans_cake[i] << ' ';
    }
}
