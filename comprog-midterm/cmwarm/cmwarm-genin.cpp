#include <iostream>
#include <string>
#include "testlib.h"

using namespace std;

int randomSign(bool allowMinus) {
    return allowMinus ? rnd.next(0, 1) * 2 - 1 : 1;
}

const char* getCommandList(int testCase) {
    /*
        Define list of available COMMAND
        TestCase       1: "" (no command)
        TestCase  2 -  3: "1" (scaling)
        TestCase  4 -  5: "2" (pivot)
        TestCase  6 -  7: "3" (swap)
        TestCase       8: "1|2"
        TestCase       9: "1|3"
        TestCase      10: "2|3"
        TestCase 11 - 20: "1|2|3"
    */

    string list;
    switch (testCase)
    {
    case 1:
        list = "";
    case 2:
    case 3:
        list = "1";
    case 4:
    case 5:
        list = "2";
    case 6:
    case 7:
        list = "3";
    case 8:
        list = "1|2";
    case 9:
        list = "1|3";
    case 10:
        list = "2|3";
    default:
        list = "1|2|3";
    }

    const char* cstr = list.c_str();
    return cstr;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(time(0));

    int numTestCases[] = {1, 2, 2, 2, 3, 5, 5};
    /*
        Constraint:
            2 <= m, n <= 5
            0 <= elements <= 20
            1 <= k <= 10

        Case 0: 1 testCaseType  instance return (no command)
        Case 1: 2 testcases ONLY command = 1 (scaling) (2 - 3 commands)
        Case 2: 2 testcases ONLY command = 2 (pivot)   (2 - 3 commands)
        Case 3: 2 testcases ONLY command = 3 (swap)    (2 - 3 commands)
        Case 4: 3 testcases combination of   2 command types ( 3 - 5 commands)
    
        =======================================================

        Constraint:
            6 <= m, n <= 10
            0 <= |elements| <= 100
            1 <= |k| <= 20 OR

        Case 5: 5 testcases combination of all command types ( 6 - 10 commands)
        Case 6: 5 testcases combination of all command types (11 - 20 commands)
    */

    int M_MIN = 2, N_MIN = 2;
    int ELEMENT_MIN = 0;
    int K_MIN = 2;
    
    int M_MAX, N_MAX;
    int ELEMENT_MAX;
    int K_MAX;

    bool ALLOW_MINUS;

    int MIN_COMMANDS, MAX_COMMANDS;

    int testCase = 1;
    for (int testCaseType = 0; testCaseType < sizeof(numTestCases) / sizeof(numTestCases[0]); testCaseType++) {

        /*
            Define value of matrix size
            Case 0 - 4: 2 - 5
            Case 5 - 6: 6 - 10

            Define value of elements
            Case 0 - 4: 0 - 20  (ALLOW_MINUS: FALSE)
            Case 5 - 6: 0 - 100 (ALLOW_MINUS: TRUE)

            Define value of k
            Case 0 - 4: 1 - 10 (ALLOW_MINUS: FALSE)
            Case 5 - 6: 1 - 20 (ALLOW_MINUS: TRUE)
        */

        switch (testCaseType)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            M_MIN = 2; N_MIN = 2; M_MAX = 5; N_MAX = 5;
            ELEMENT_MIN = 0; ELEMENT_MAX = 20;
            K_MIN = 1; K_MAX = 10;
            ALLOW_MINUS = false;
            break;

        case 5:
        case 6:
            M_MIN = 6; N_MIN = 6; M_MAX = 10; N_MAX = 10;
            ELEMENT_MIN = 0; ELEMENT_MAX = 100;
            K_MIN = 1; K_MAX = 20;
            ALLOW_MINUS = true;
            break;

        default:
            break;
        }


        /*
            Define number of commands
            Case     0: 0
            Case 1 - 3: 2 - 3
            Case     4: 3 - 5
            Case     5: 6 - 10
            Case     6: 11 - 20
        */

        switch (testCaseType)
        {
        case 0:
            MIN_COMMANDS = 0, MAX_COMMANDS = 0;
            break;
        case 1:
        case 2:
        case 3:
            MIN_COMMANDS = 2, MAX_COMMANDS = 3;
            break;
        case 4:
            MIN_COMMANDS = 3, MAX_COMMANDS = 5;
            break;
        case 5:
            MIN_COMMANDS = 6, MAX_COMMANDS = 10;
            break;
        case 6:
            MIN_COMMANDS = 11, MAX_COMMANDS = 20;
            break;

        default:
            break;
        }

        for (int t = 0; t < numTestCases[testCaseType]; t++) {

            // Open .in testcase file
            string tc = "testcase/" + to_string(testCase) + ".in";
            freopen(tc.c_str(), "w", stdout);

            // Random Matrix Size
            int m = rnd.next(M_MIN, M_MAX);
            int n = rnd.next(N_MIN, N_MAX);
            cout << m << " " << n << "\n";

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << rnd.next(ELEMENT_MIN, ELEMENT_MAX) * randomSign(ALLOW_MINUS) << " ";
                }
                cout << "\n";
            }

            // Command Generation
            for (int c = MIN_COMMANDS; c <= MAX_COMMANDS; c++) {
                string command = rnd.next(getCommandList(testCaseType));
                cout << command << " ";

                switch (stoi(command))
                {
                case 1: // Scaling
                    cout << rnd.next(1, m) << " ";
                    cout << rnd.next(K_MIN, K_MAX) * randomSign(ALLOW_MINUS) << " ";
                    cout << "\n";
                    break;
                
                case 2: // Pivot
                    cout << rnd.next(1, m) << " ";
                    cout << rnd.next(1, m) << " ";
                    cout << rnd.next(K_MIN, K_MAX) * randomSign(ALLOW_MINUS) << " ";
                    cout << "\n";
                    break;
                
                case 3: // Swap
                    cout << rnd.next(1, m) << " ";
                    cout << rnd.next(1, m) << " ";
                    cout << "\n";
                    break;
                
                default:
                    break;
                }
            }

            cout << "-1";
            testCase++;

        }
    }
}
