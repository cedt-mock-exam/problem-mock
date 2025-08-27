#include <iostream>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;

    int A[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }

    int command;
    while (cin >> command)
    {
        if (command == -1)
        {
            break;
        }

        if (command == 1)
        {
            int r1, k;
            cin >> r1 >> k;

            r1--;

            for (int j = 0; j < n; j++)
            {
                A[r1][j] *= k;
            }
        }

        else if (command == 2)
        {
            int r1, r2, k;
            cin >> r1 >> r2 >> k;

            r1--;
            r2--;

            for (int j = 0; j < n; j++)
            {
                A[r1][j] += (A[r2][j] * k);
            }
        }

        else if (command == 3)
        {
            int r1, r2;
            cin >> r1 >> r2;

            r1--;
            r2--;

            for (int j = 0; j < n; j++)
            {
                swap(A[r1][j], A[r2][j]);
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}
