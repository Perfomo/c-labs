#include <iostream>
#include "Source1.h"
#include <string>
#include <math.h>
using namespace std;

string FuncRec(int x, int y, string x5)
{
    int ost = x % y;
    string Lang[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    if( x < y )
    {   
         if ( ost >= 10)
        {
            for (int i = 10; i < 27; i++)
            {
                if ( i == ost )
                {
                    x5 = " " + Lang[i - 10] + " " + x5;
                    return x5; 
                }
            }
        }
        return " " + to_string(x) + " " + x5;
    }
    else
    {
        if ( ost >= 10)
        {
            for (int i = 10; i < 27; i++)
            {
                if ( i == ost )
                {
                    x5 = Lang[i - 10] + " " + x5;
                    return FuncRec(x / y, y, x5); 
                }
            }
        }
        x5 = to_string(ost) + " " + x5;
        return FuncRec(x / y, y, x5);
    }
}

// string FuncRec(int x, int y, string x5)
// {
//     if( x < y )
//     {
//         return to_string(x) + " " + x5;
//     }
//     else
//     {
//         x5 = to_string( x % y) + " " + x5;
//         return FuncRec(x / y, y, x5);
//     }
// }

string NormFunc(int x, int y)
{
    string x5 ="";
    for (x; x > y; x /= y)
    {
        x5 = to_string( x % y) + " " + x5;
    }
    return to_string(x) + " " + x5;
}

int main()
{
    string x5 = "";

    cout<<"Input x(>0): " << endl;
    int x = InputInt(">0");

    cout << "Input system: " << endl;
    int y = InputInt(">0");

    cout << "RecFunc: " << FuncRec(x, y, x5) << endl;
    cout << "NormFunc: " << NormFunc(x, y, x5) << endl;
    
    return 0;
}