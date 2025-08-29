#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;


int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    rnd.setSeed(time(0)); 
    //if you want to reset tc every run file , just uncomment

    for (int t = 1; t <= 20; t++) {
        string tc = "testcase/" + to_string(t) + ".in";
        freopen(tc.c_str(), "w", stdout);
        //you gen code
        
            int ksize[] = {10,20,50,100,100,200,300,500,500,500,500,1000,1000,5000,10000,10000,10000,50000,50000,50000};
            int psize[] = {5,8,30,30,20,30,40,50,50,50,50,100,100,500,1000,1000,1000,5000,5000,5000};
            int hsize[] = {0,0,0,0,20,30,40,50,50,50,50,100,100,500,1000,1000,1000,5000,5000,5000};
            int nsize[] = {0,0,0,0,0,0,0,0,50,50,50,100,100,500,1000,1000,1000,5000,5000,5000};
            int numbersize[] = {5,8,10,20,20,50,60,100,50,50,50,100,100,500,1000,1000,1000,5000,5000,5000};
            int numbersizereal = numbersize[t-1];
            int k = ksize[t-1];
            int p = psize[t-1];
            int h = hsize[t-1];
            int n = nsize[t-1];
            vector<char>order;
            for(int i=0;i<k;i++){
                order.push_back('K');
            }
            for(int i=0;i<p;i++){
                order.push_back('P');
            }
            for(int i=0;i<h;i++){
                order.push_back('H');
            }
            for(int i=0;i<n;i++){
                order.push_back('N');
            }
            shuffle(order.begin(),order.end());
            vector<string>number;
            for(int i=0;i<numbersizereal;i++){
                number.push_back(rnd.next("[0-9]{6}"));
            }
            for(auto x:order){
                if(x=='K'){
                    cout<<x<<" "<<number[rnd.next(0,numbersizereal-1)]<<"\n";
                }
                else if(x=='P'){
                    cout<<x<<" "<<number[rnd.next(0,numbersizereal-1)]<<"\n";
                }
                else if(x=='H'){
                    cout<<x<<"\n";
                }
                else if(x=='N'){
                    cout<<x<<"\n";
                }
            }
            cout<<"E";
    }
    return 0;
}
