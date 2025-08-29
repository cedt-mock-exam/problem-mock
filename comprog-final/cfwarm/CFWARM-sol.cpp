#include<bits/stdc++.h>
using namespace std;
map<string,int>lottery;

int main(){
    string most;
    int mostcount = 0;
    int howmany = 0;
    while(1){
        char m;
        cin>>m;
        if(m=='E'){
            break;
        }
        else if(m=='K'){
            string number;
            cin>>number;
            if(lottery[number]==0){
                howmany++;
            }
            lottery[number]++;
            if(lottery[number]>mostcount){
                mostcount = lottery[number];
                most = number;
            }
        }
        else if(m=='P'){
            string number;
            cin>>number;
            cout<<lottery[number]<<"\n";
        }
        else if(m=='H'){
            cout<<most<<"\n";
        }
        else if(m=='N'){
            cout<<howmany<<"\n";
        }
    }
}