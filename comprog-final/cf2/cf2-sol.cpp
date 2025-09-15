#include<bits/stdc++.h>
using namespace std;
int main(){
    int x,n;
    cin>>x>>n;
    pair<string,int> novel[n];
    int min = INT_MAX;
    for(int i=0;i<n;i++){
        string name;
        int num,canbuy,change=x;
        bool limit=0;
        cin>>name>>num;
        for(int j=1;j<=num;j++){
            int book;
            cin>>book;
            if(book<=change&&!limit){
                change-=book;
                if(j==num) canbuy = num;
            }
            else if(!limit){
                limit=1;
                canbuy = j-1;
            }
        }

        if(canbuy==0) num = -1;//cant buy anything 
        else num -= canbuy;

        novel[i]={name,num};

        if(num<min&&num!=-1){
            min=num;
        }
    }

    bool havesome = false;
    for(int i=0;i<n;i++){
        if(novel[i].second==min){
            cout<<novel[i].first<<"\n";
            havesome = true;
        }
    }
    if(!havesome){
        cout<<"FIND SOMETHING FREE";
    }
}