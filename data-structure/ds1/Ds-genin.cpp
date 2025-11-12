#include <bits/stdc++.h>
using namespace std;

vector<string> events = {"Popsiam", "Coding", "Camp", "Metro", "Phonesiam", "Boardgame", "IOT", "ICT"};
vector<string> names  = {"Phone", "Knight", "Euro", "Wan", "Prame", "Nut", "A", "B"};


int main() {
    srand(time(NULL));
    for(int i=11; i<=20; i++) {
        ofstream fout;
        fout.open(to_string(i)+".in");
        long long n = (((1LL * rand() << 15) ^ rand())%10000000)+5;
        fout << n << "\n";

        for (int j = 1 ; j <= n ; j++)
        {
            int cmd = rand() % 5;
            string e = events[rand() % events.size()];
            string m = names[rand() % names.size()];
              if (cmd == 0) {
                fout << "ADDEVENT " << e << "\n";
            } 
            else if (cmd == 1) {
                fout << "REGISTER " << e << " " << m << "\n";
            } 
            else if (cmd == 2) {
                fout << "CANCEL " << e << " " << m << "\n";
            } 
            else if (cmd == 3) {
                fout << "SHOW " << e << "\n";
            } 
            else {
                fout << "UNDO\n";
            }
        }
    }
    return 0;
}
