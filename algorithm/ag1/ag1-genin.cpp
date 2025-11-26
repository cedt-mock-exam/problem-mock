#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const string CHARSET = "ABCDEFGHIJKL";

string gen_unique(int len) {
  string s = CHARSET.substr(0, min(len, 8));
  shuffle(s.begin(), s.end());
  return s;
}

string gen_dupe(int len, int numDistinct) {
  if (numDistinct == 1) return string(len, rnd.any(CHARSET));
  numDistinct = min({numDistinct, len, 8});
  string chars = CHARSET.substr(0, numDistinct);
  shuffle(chars.begin(), chars.end());

  string result;
  for (int i = 0; i < numDistinct; i++) {
    int count = len / numDistinct + (i < len % numDistinct);
    result += string(count, chars[i]);
  }

  shuffle(result.begin(), result.end());
  return result;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  rnd.setSeed(101);

  for (int t = 1; t <= 20; t++) {
    freopen(("testcase/" + to_string(t) + ".in").c_str(), "w", stdout);

    string s;
    if (t <= 5) s = gen_unique(t);
    else if (t <= 10) s = gen_unique(rnd.next(6, 8));
    else if (t <= 12) s = gen_dupe(rnd.next(6, 10), 14 - t);
    else if (t <= 18) s = gen_dupe(rnd.next(11, 13), rnd.next(2, 4));
    else if (t <= 20) s = gen_dupe(rnd.next(11, 13), 1);

    cout << s << endl;
    fclose(stdout);
  }
  return 0;
}