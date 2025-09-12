#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

set<string> destroyedCities;
// A set containing the destroyed cities.

map<string,int> cityStrength;
// A map with key as the city name, and the mapped value as the strength of corresponding city.

map<string,vector<string>> adjacentCities;
// A map with key as the city name, and the mapped value as vector of strings which are its adjacent cities.

void burn(string cityName,string previousCityName,int firePower){
    /* You are ALLOWED to edit this function only. And "You" must implement this function from scratch.
    This function simulates the behavior of the inferno. Inferno means flame.

    1. The inferno starts at the city named [cityName] with the burning power of [firePower]
    2. Burning process.
         - Check if the inferno is strong enough to destroys the city.
         - If it is, 
            - The city will be destroyed. Therefore include it as one of destroyed cities.
            - The inferno will spread to "ALL" of adjacent cities with the decreased power, except the one where the fire came from "previousCityName".
            - The process will be repeated for all spread cities.
         - If it isn't
            - The inferno will be contained and extinguished in that city.

    Let the world burns as you solve this problem.
    */
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