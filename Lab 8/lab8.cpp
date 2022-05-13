#include <iostream>
using namespace std;
#include <math.h>
#include "Source1.h"


double F(double x)
{
    return pow(sin(x),2) - 3 * cos(x);
}

double Mid(double a, double b, int m)
{
    double result = 0, h = (b - a) / m;
  
    for(int i = 0; i < m; i++)
    {
        result += F(a + h * (i + 0.5));
    }
    return result * h;
}

double Eps(double a, double b, double e)
{
    double i1, i2;
    int m = 2;
    i1 = Mid(a, b, m);
    m = 4;
    i2 = Mid(a, b, m);
    while(abs(i1 - i2) >= e)
    {
        i1 = i2;
        i2 = Mid(a, b, m *= 2);
    }
    return i2;
}

int main()
{
    double a, b, h, e, result;
    int m;
    while (true)
    {
        cout << "-----------------------" << endl;
        cout << "1 - Input a and b\n2 - Result\n3 - Exit" << endl;
        switch (_getch())
        {
        case '1':
            cout << "-----------------------" << endl;
            cout << "1 - Test\nelse - Ur input" << endl;
            if(_getch() == '1')
            {
                a = 1;
                b = 7;
            }
            else
            {
                while (true)
                {
                    cout << "Input a: "<< endl;
                    a = InputDouble("all");

                    cout << "Input b: " << endl;
                    b = InputDouble("all");

                    if(a != b)
                    {
                        break;
                    }
                    cout << "Bad input... (a = b)" << endl;
                }

                if(a > b)
                {
                    cout << "Swaping a and b ..." << endl;
                    h = a;
                    a = b;
                    b = h;
                }
            }
            break;

        case '2':
            
            while (true)
            {
                cout << "\nInput m: " << endl;
                m = InputInt("all");
                if (m >= 20)
                {
                    break;
                }
                cout << "m must be more than 20..." << endl;
            }

            while (true)
            {
                cout << "\nInput e: " << endl;
                e = InputDouble("all");
                if (e < 0.5 and e > 0.000001)
                {
                    break;
                }
                cout << "e to small or too big... Must be (0.000001, 0.5)" << endl;
            }

            cout << "\nMiddles method: " << endl;
            result = Mid(a, b, m);
            cout << "Result: " << result << endl;
            
            cout << "\nEps method: " << endl;
            result = Eps(a, b, e);
            cout << "Result: " << result << endl;            

            break;

        case '3':
            cout << "\nHave a nice day!!!" << endl;
            return 0;
        
        default:
            cout << "\nBad input..." << endl;
            break;
        }
    }
    
    return 1;
}