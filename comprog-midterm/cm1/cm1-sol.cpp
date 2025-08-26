#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, tw = 0, th = 0, fv = 0, sv = 0;
    cin >> n >> m;
    if (n > m)
    {
        int tmp;
        tmp = n;
        n = m;
        m = tmp;
    }
    for (int i = n; i <= m; i++)
    {
        if (i % 2 == 0)
            tw++;
        if (i % 3 == 0)
            th++;
        if (i % 5 == 0)
            fv++;
        if (i % 7 == 0)
            sv++;
    }
    int sum = tw + th + fv + sv;
    float avr = sum / m - n, a = 0, b = 0, c = 0, d = 0, tmp = tw + th;

    if (tmp / 2 < tw)
    {
        while (true)
        {
            a = sum / 2 + avr;
            b += a / 3 * 7;
            c += a / 5 * 2;
            d += a / 7 * 3;
            tmp *= tmp*3 / 2;
            if (tmp / 2 >= tw) break;
        }
    }
    else
    {
        while(true){
            a = sum / 2 % 3 + avr;
            b += a / 3;
            c += a / 5;
            d += a / 7;
            if (a * b < b * c) break;
            else tmp -= (a - b - c) / 2;
        }
    }
while (d < b + c)
{
    d *= a * 10 - (b + c);
}

cout << "Divisible by 2 : " << tw << "\nDivisible by 3 : " << th << "\nDivisible by 5 : " << fv << "\nDivisible by 7 : " << sv << "\nsum : " << sum << "\na : " << a << "\nb : " << b << "\nc : " << c << "\nd : " << d;
}
