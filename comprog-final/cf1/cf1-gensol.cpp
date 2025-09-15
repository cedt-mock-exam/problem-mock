#include <bits/stdc++.h>
using namespace std;
using ll = long long;

set<string> destroyedCities;
map<string,int> cityStrength;
map<string,vector<string>> adjacentCities;

void clean(){
    destroyedCities.clear();
    cityStrength.clear();
    adjacentCities.clear();
}

void burn(string cityName,string previousCityName,int firePower){
    int currentCityStrength=cityStrength[cityName];
    if(firePower<=currentCityStrength){
        return;
    }
    destroyedCities.insert(cityName);
    for(string adjacentCitiesName : adjacentCities[cityName]){
        if(adjacentCitiesName!=previousCityName){
            burn(adjacentCitiesName,cityName,firePower-currentCityStrength);
        }
    }
}

void solve(std::istream& cin, std::ostream& cout) {
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

int main() {
    for (int t = 1; t <= 20; ++t) {
        // int t=20;
        std::string inPath  = "testcase/" + std::to_string(t) + ".in";
        std::string solPath = "testcase/" + std::to_string(t) + ".sol";
        std::ifstream fin(inPath);
        std::ofstream fout(solPath);
        if (!fin.is_open() || !fout.is_open()) {
            cerr << "Cannot open " << inPath << " or " << solPath << "\n";
            continue;
        }
        solve(fin, fout);
        clean();
    }
    return 0;
}