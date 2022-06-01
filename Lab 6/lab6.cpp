#include <iostream>
#include <math.h>
using namespace std;
#include "Source1.h"

// Sin^2(x) - 3Cos(X);
double F(double x)
{
    return pow(sin(x), 2) - 3 * cos(x);
    // return 4*x - 7*sin(x);
}

double FindKeyCekLine(double x0, double h, double e, int &it)
{
    double y0, x1, de, yd;
    y0 = F(x0);
    yd = F(x0 - h);
    do
    {
        it++;
        x1 = x0 - y0 * h / (y0 - yd);
        de = fabs(x0 - x1);
        x0 = x1;
        yd = y0;
        y0 = F(x1);
    } while (de > e);
    return x1;
}

double Fun_Del_2(double x0, double x1, double e, int &it)
{
    double x2, y0, y2;
    y0 = F(x0);
    do
    {
        it++;
        x2 = (x0 + x1) / 2;
        y2 = F(x2);
        if (y0 * y2 > 0)
        {
            x0 = x2;
            y0 = y2;
        }
        else
        {
            x1 = x2;
        }
    } while (fabs(x1 - x0) > e);
    return (x0 + x1) / 2;
}

int main()
{
    bool exit = false, input = false;
    double a = -7, b = 3, h = 0.001, e = 0.005, y;
    int it;

    while (true)
    {
        cout << "-------------------------" << endl;
        cout << "1 - Input\n2 - View result\n3 - View graph\n4 - Exit" << endl;
        cout << "-------------------------" << endl;
        switch (_getch())
        {
        case '1':
            input = true;
            cout << "\n1 - Test\nelse - Ur input" << endl;
            if (_getch() == '1')
            {
                a = -7;
                b = 3;
                h = 0.05;
                e = 0.005;
                // a = -2;
                // b = 2;
            }
            else
            {
                while (!exit)
                {
                    cout << "\nInput a: " << endl;
                    a = InputDouble("all");
                    cout << "\nInput b: " << endl;
                    b = InputDouble("all");
                    if (a == b)
                    {
                        cout << "\nError: a = b\t reinput a and b..." << endl;
                    }
                    else
                    {
                        exit = true;
                    }
                }
                exit = false;
                if (a > b)
                {
                    h = a;
                    a = b;
                    b = h;
                    cout << "\nSwaping a and b..." << endl;
                }
                while(true)
                {
                    while (true)
                    {
                        cout << "\nInput step: " << endl;
                        h = InputDouble("all");
                        if(h < 0)
                        {
                            h = fabs(h);
                            cout << "step = |step|" << endl;
                        }
                        if (h < 0.001 and h > 0.00001)
                        {
                            break;
                        }
                        cout << "\nstep is too big (step > 0.001) or too small (step < 0.00001)";
                    }
                    while (true)
                    {

                        cout << "\nInput e: " << endl;
                        e = InputDouble(">0");
                        if (e == 0)
                        {
                            cout << "\nbad e..." << endl;
                        }
                        else
                        {
                            if (e < 0.001 and e > 0.00001)
                            {
                                break;
                            }
                            cout << "\ne is too big (e > 0.001) or too small (e < 0.00001)";
                        }
                    }
                    if(e < h)
                    {
                        break;
                    }
                    cout << "e must be <h" << endl;
                }
                
            }
            break;

        case '2':
            if (!input)
            {
                cout << "\nAt first do input!!!" << endl;
            }
            else
            {
                cout << "\nMethod 1:\nRoots:" << endl;
                it = 0;
                for (double k = a; k < b; k += h)
                {
                    if (F(k) * F(k + h) < 0)
                    {
                        cout << FindKeyCekLine(k, h, e, it) << endl;
                    }
                }
                if(it == 0)
                {
                    cout << "no roots here..." << endl;
                }
                cout << "It: " << it << endl;
                it = 0;
                cout << "\nMethod 2:\nRoots:" << endl;
                for (double k = a; k < b; k += h)
                {
                    if (F(k) * F(k + h) < 0)
                    {
                        cout << Fun_Del_2(k, k + h, e, it) << endl;
                    }
                }
                if(it == 0)
                {
                    cout << "no roots here..." << endl;
                }
                cout << "It: " << it << endl;
            }
            break;

        case '3':
            if(input)
            {
                for(double k = a, y = (b - a) / 100; k < b; k+=y)
                {
                    system(("echo '" + to_string(k) + " " + to_string(F(k)) + "' >> points").c_str());
                }
                system("echo 'plot \"points\" with lines, 0' | gnuplot --persist ");
                system("rm 'points'");
            }
            else
            {
                cout << "\nAt first do input!!!" << endl;
            }
            break;

        case '4':
            cout << "\nHave a nice day!!!" << endl;
            return 0;

        default:
            cout << "\nBad input..." << endl;
            break;
        }
    }
    return 0;
}
