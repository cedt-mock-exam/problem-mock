#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

const int MIN_LEN = 2;
const int MAX_LEN = 8;
const string CHARSET = "ABCDEFGH";

string generateUnique(int len) {
    string chars = CHARSET; 
    if (len > (int)chars.size()) len = (int)chars.size();
    shuffle(chars.begin(), chars.end());
    return chars.substr(0, len);
}

string generateWithRepeats(int len) {
    string s = "";
    for (int i = 0; i < len; i++)
        s += CHARSET[rnd.next(0, (int)CHARSET.size() - 1)];

    if (len >= 2 && (int)set<char>(s.begin(), s.end()).size() == len) {
        s[len - 1] = s[len - 2];
    } else if (len >= 2 && (int)set<char>(s.begin(), s.end()).size() == 1) {
    } else if (len >= 2 && (int)set<char>(s.begin(), s.end()).size() == len) {
         s[len - 1] = s[len - 2];
    }
    
    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    for (int t = 1; t <= 20; t++) {
        string tc = "testcase/" + to_string(t) + ".in";
        freopen(tc.c_str(), "w", stdout);

        ll temp = rnd.next(123456);
        for (int i = 1; i < temp; i++) {
            rnd.next(i);
            rnd.next(i, i);
        }

        int len;
        string s;
        bool unique_chars;

        if (t >= 1 && t <= 5) {
            len = max(MIN_LEN, t);
            unique_chars = true;
        } else if (t >= 6 && t <= 9) {
            if (t == 6) len = 6;
            else if (t == 7) len = 7;
            else len = 8;
            unique_chars = true;
        } else if (t == 10) {
            len = MAX_LEN;
            unique_chars = true;
        } else if (t >= 11 && t <= 15) {
            len = max(MIN_LEN, t - 10);
            unique_chars = false;
        } else if (t >= 16 && t <= 19) {
            if (t == 16) len = 6;
            else if (t == 17) len = 7;
            else len = 8;
            unique_chars = false;
        } else {
            len = MAX_LEN;
            unique_chars = false;
        }
        
        if (unique_chars) {
            s = generateUnique(len);
        } else {
            s = generateWithRepeats(len);
        }

        cout << s << endl;
        
        fclose(stdout);
    }
    return 0;
}