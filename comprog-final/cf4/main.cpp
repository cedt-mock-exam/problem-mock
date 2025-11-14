/*
    Problem: main.cpp
    Author: Chawanwit Chitman
    Date: 25/09/2025
*/
#include <ios>
#include <iostream>

using namespace std;

int cal(int n) {
    if (n <= 1) 
        return 1;
    cal(n - 1);
    return n;
}

int main (int argc, const char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << cal(4);
    return 0;
}