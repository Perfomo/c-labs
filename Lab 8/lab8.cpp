#include <iostream>
using namespace std;
#include <math.h>
#include "Source1.h"

typedef double (*F_type)(double, double, int);

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

double Simps (double a, double b, int m)
{
    double s = 0, h, x;
    h = (b - a) / m;
    x = a;
    for(int i = 1; i <= m; i++)
    {
        s += F(x) + 4 * F(x + h / 2) + F(x + h);
        x += h;
    }
    return s * h / 6;
}


double Eps(F_type F, double a, double b, double e, int &it)
{
    double i1, i2;
    int m = 2;
    i1 = F(a, b, m);
    m = 4;
    i2 = F(a, b, m);
    while(abs(i1 - i2) >= e)
    {
        i1 = i2;
        i2 = F(a, b, m *= 2);
        it++;
    }
    return i2;
}

int InputM()
{
    int m;
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
    cin.ignore();
    return m;
}

double InputEps()
{
    double e;
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
    return e;
}

int main()
{
    double a = 0, b = 0, h, e = 0, result;
    int m = 0, it;
    bool exit;
    while (true)
    {
        cout << "-----------------------" << endl;
        cout << "1 - Input a and b\n2 - Input e\n3 - input m\n4 - Result\n5 - Exit" << endl;
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
            e = InputEps();
            break;

        case '3':
            m = InputM();
            break;

        case '4':
            if(a == b)
            {
                cout << "At first input a and b..." << endl;
                break;
            }
            exit = false;
            while(!exit)
            {
                cout << "-----------------------" << endl;
                cout << "1 - Middles method\n2 - Simpson method\n3 - eps\n4 - all methods\n5 - exit from this menu" << endl;

                switch (_getch())
                {
                case '1':
                    if(m == 0)
                    {
                        cout << "\nAt first input m: " << endl;
                        m = InputM();
                    }
                    cout << "\nValues:\na - " << a << "\nb - " << b << "\nm - " << m << endl;
                    cout << "\nMiddles method: " << endl;
                    result = Mid(a, b, m);
                    cout << "Result: " << result << endl;
                    break;

                case '2':
                    if(m == 0)
                    {
                        cout << "\nAt first input m: " << endl;
                        m = InputM();
                    }
                    cout << "\nValues:\na - " << a << "\nb - " << b << "\nm - " << m << endl;
                    cout << "\nSimps method: " << endl;
                    result = Simps(a, b, m);
                    cout << "Result: " << result << endl;
                    break;

                case '3':
                    if(e == 0)
                    {
                        cout << "\nAt first input Eps: " << endl;
                        e = InputEps();
                    }
                    cout << "\nValues:\na - " << a << "\nb - " << b << "\neps - " << e << endl;
                    cout << "\nEps Mid method: " << endl;
                    it = 1;
                    result = Eps(Mid, a, b, e, it);
                    cout << "\nResult: " << result << endl;
                    cout << "Eps it: " << it << endl; 

                    cout << "\nEps Simps method: " << endl;
                    it = 1;
                    result = Eps(Simps, a, b, e, it);
                    cout << "\nResult: " << result << endl;
                    cout << "Eps it: " << it << endl; 
                    break;
                
                case '4':
                    if(m == 0)
                    {
                        cout << "\nInput m: " << endl;
                        m = InputM();
                    }
                    if(e == 0)
                    {
                        cout << "\nInput Eps: " << endl;
                        e = InputEps();
                    }
                    cout << "\nValues:\na - " << a << "\nb - " << b << "\nm - " << m << "\neps - "<< e << endl;
                    cout << "\nMiddles method: " << endl;
                    result = Mid(a, b, m);
                    cout << "Result: " << result << endl;

                    cout << "\nSimps method: " << endl;
                    result = Simps(a, b, m);
                    cout << "Result: " << result << endl;

                    cout << "\nEps Mid method: " << endl;
                    it = 1;
                    result = Eps(Mid, a, b, e, it);
                    cout << "Result: " << result << endl;
                    cout << "Eps it: " << it << endl; 

                    cout << "\nEps Simp method: " << endl;
                    it = 1;
                    result = Eps(Simps, a, b, e, it);
                    cout << "\nResult: " << result << endl;
                    cout << "Eps it: " << it << endl; 
                    break;

                case '5':
                    exit = true;
                    break;

                default:
                    cout << "Bad input..." << endl;
                    break;
                }
            }
            break;

        case '5':
            cout << "\nHave a nice day!!!" << endl;
            return 0;
        
        default:
            cout << "\nBad input..." << endl;
            break;
        }
    }
    
    return 1;
}