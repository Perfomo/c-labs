#include <iostream>
#include "Source1.h"
using namespace std;


double RecFunc(double x, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        if (n % 2 == 0)
        {
            double x1 = RecFunc(x, n/2);
            return x1 * x1;
        }
        else
        {
            return x * RecFunc(x, n-1);
        }
    }
}

double NormFunc(double x, int n)
{
    double z = 1;
    for (int t = 0; t < n; t++)
    {
        z*=x;
    }

    return z;
}

int main()
{
    double x;
    int n;
    while(true)
    {
        cout << "----------------------------" << endl;
        cout << "1 - Input\nElse - exit" << endl;
        if(_getch() == '1')
        {
            cout << "\nInput x: " << endl;
            x = InputDouble("all");

            cout << "\nInput n: " << endl;
            n = InputInt(">0");

            cout << "\nNormal loop: " << endl;
            cout <<  NormFunc(x, n) << endl;

            cout << "\nRecursive result: " << endl;
            cout << RecFunc(x, n) << endl;
            cin.ignore();
        }
        else
        {
            break;
        }
    }
    cout << "\nHave a nice day!!!" << endl;
    return 0;
}