#include<bits/stdc++.h>
using namespace std;
vector<string> ans;
map<int,bool> used;
string word;

void permu(int n,string t){
    if(n==0){
        ans.push_back(t);
        return;
    }
    for(int i=0;i<word.size();i++){
        if(i!=0 && word[i]==word[i-1] &&!used[i-1]){
            continue;
        }
        if(!used[i]){
            used[i]=1;
            permu(n-1,t+word[i]);
            used[i]=0;
        }
    }
    return;

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>word;
    sort(word.begin(), word.end());
    for(int i=0;i<word.size();i++){
        used[i]=0;
    }
    permu(word.size(),"");
    cout<<ans.size()<<"\n";
    for(auto it:ans) cout<<it<<"\n";
}