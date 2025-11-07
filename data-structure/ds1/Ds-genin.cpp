#include <bits/stdc++.h>
using namespace std;

vector<string> events = {"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10","A11","A12","A13","A14","A15","A16","A17","A18","A19","A20","A21","A22","A23","A24","A25","A26","A27","A28","A29","A30","A31","A32","A33","A34","A35","A36","A37","A38","A39","A40","A41","A42","A43","A44","A45","A46","A47","A48","A49","A50","A51","A52","A53","A54","A55","A56","A57","A58","A59","A60","A61","A62","A63","A64","A65","A66","A67","A68","A69","A70","A71","A72","A73","A74","A75","A76","A77","A78","A79","A80","A81","A82","A83","A84","A85","A86","A87","A88","A89","A90","A91","A92","A93","A94","A95","A96","A97","A98","A99","A100"};
vector<string> names  = {"N1","N2","N3","N4","N5","N6","N7","N8","N9","N10","N11","N12","N13","N14","N15","N16","N17","N18","N19","N20","N21","N22","N23","N24","N25","N26","N27","N28","N29","N30","N31","N32","N33","N34","N35","N36","N37","N38","N39","N40","N41","N42","N43","N44","N45","N46","N47","N48","N49","N50","N51","N52","N53","N54","N55","N56","N57","N58","N59","N60","N61","N62","N63","N64","N65","N66","N67","N68","N69","N70","N71","N72","N73","N74","N75","N76","N77","N78","N79","N80","N81","N82","N83","N84","N85","N86","N87","N88","N89","N90","N91","N92","N93","N94","N95","N96","N97","N98","N99","N100"};


int main() {
    srand(time(NULL));
    for(int i=18; i<=20; i++) {
        ofstream fout;
        fout.open(to_string(i)+".in");
        int n = rand()%2000+500;
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
