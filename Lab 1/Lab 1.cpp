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

    cout << "Input x: " << endl;
    x = InputDouble("all");

    cout << "Input n: " << endl;
    n = InputInt(">0");

    cout << "Normal loop: " << endl;
    cout <<  NormFunc(x, n) << endl;

    cout << "Recursive result: " << endl;
    cout << RecFunc(x, n) << endl;

    return 1;
}