#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

set<string> destroyedCities;
map<string,int> cityStrength;
map<string,vector<string>> adjacentCities;

void burn(string currentCityName,string previousCityName,int firePower){
    int currentCityStrength=cityStrength[currentCityName];
    if(firePower<=currentCityStrength){
        return;
    }
    destroyedCities.insert(currentCityName);
    for(string adjacentCitiesName : adjacentCities[currentCityName]){
        if(adjacentCitiesName!=previousCityName){
            burn(adjacentCitiesName,currentCityName,firePower-currentCityStrength);
        }
    }
}
int main(){
    int N,S,K,P;
    string C,c,I;
    cin >> N;
    for(int i=0;i<N;i++){
        cin >> C >> S >> K;
        cityStrength[C]=S;
        for(int j=0;j<K;j++){
            cin >> c;
            adjacentCities[C].push_back(c);
        }
    }
    cin >> I >> P;
    burn(I,"",P);
    set<string>::iterator it;
    cout << destroyedCities.size() << endl;
    for(it=destroyedCities.begin();it!=destroyedCities.end();it++){
        cout << *it << endl;
    }
}