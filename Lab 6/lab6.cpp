#include <iostream>
#include <math.h>
using namespace std;
#include "Source1.h"

#include <termios.h>
#include <unistd.h>

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
        // cout << '*' << endl;
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
        // cout << '*' << endl;
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
            cout << "1 - Test\nelse - Ur input" << endl;
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
                    cout << "Input a: " << endl;
                    a = InputDouble("all");
                    cout << "Input b: " << endl;
                    b = InputDouble("all");
                    if (a == b)
                    {
                        cout << "Error: a = b\t reinput a and b..." << endl;
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
                }
                while (true)
                {
                    cout << "Input step: " << endl;
                    h = InputDouble("all");
                    h = fabs(h);
                    if (h < (b - a) / 100)
                    {
                        break;
                    }
                    cout << "h is too big or too small\n";
                }
                while (true)
                {

                    cout << "Input e : " << endl;
                    e = InputDouble(">0");
                    if (e == 0)
                    {
                        cout << "bad e..." << endl;
                    }
                    else
                    {
                        if (e < 0.1 && h / 10)
                        {
                            break;
                        }
                        cout << "e is too big or too small\n";
                    }
                }
            }
            break;

        case '2':
            if (!input)
            {
                cout << "At first do input!!!" << endl;
            }
            else
            {
                cout << "Method 1:\nRoots:" << endl;
                it = 0;
                for (double k = a; k < b; k += h)
                {
                    if (F(k) * F(k + h) < 0)
                    {
                        cout << FindKeyCekLine(k, h, e, it) << endl;
                    }
                }
                cout << "It: " << it << endl;
                it = 0;
                cout << "Method 2:\nRoots:" << endl;
                for (double k = a; k < b; k += h)
                {
                    if (F(k) * F(k + h) < 0)
                    {
                        cout << Fun_Del_2(k, k + h, e, it) << endl;
                    }
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
                // View1(a, b, h);
                // cout << "-------------------------------------------------------------------------------------------" << endl;
                // View2(a, b, h);
            }
            else
            {
                cout << "At first do input!!!" << endl;
            }
            break;

        case '4':
            cout << "Have a nice day!!!" << endl;
            return 0;

        default:
            cout << "Bad input..." << endl;
            break;
        }
    }
    return 0;
}


// void View2(double a, double b, double h)
// {
//     int height = 30, width = 120;
//     double max, min, delt_y, per_y = (b - a) / height, per_x = (b - a) / width, buf, y;

//     double *x_val = new double[width];
//     int i = 0;

//     for (double k = a; k < b; k += per_y, i++)
//     {
//         buf = F(k);
//         if (buf > max)
//         {
//             max = buf;
//         }
//         if (buf < min)
//         {
//             min = buf;
//         }
//     }
//     i = 0;
//     for (double k = a; k < b; k += per_x, i++)
//     {
//         x_val[i] = F(k);
//     }
//     y = max;
//     min -= per_y;
//     do
//     {
//         if (y > -1 * per_y and y < per_y)
//         {
//             cout << 0;
//         }
//         else
//         {
//             cout << " ";
//         }
//         for (int i = 0, k = 0; i < width; i++, k++)
//         {
//             if (k >= width)
//             {
//                 k = 0;
//             }
//             if (x_val[k] > y - per_y / 2 && x_val[k] < y + per_y / 2)
//             {
//                 cout << "*";
//             }
//             else
//             {
//                 cout << " ";
//             }
//         }
//         y -= per_y;
//         cout << "|" << endl;
//     } while (y >= min);
//     delete[] x_val;
// }

// void View1(double a, double b, double h)
// {
//     int height = 30, width = 120, n = 0;
//     double max, min, per_y = (b - a) / height, per_x = (b - a) / width, buf, y;

//     double *x_val = new double[width], delt_m, per_m;
//     int i = 0;

//     // cout << per_y << "  " << per_x << endl;

//     for (double k = a; k < b; k += per_y, i++)
//     {
//         // cout << i << endl;
//         buf = F(k);

//         if (buf > max)
//         {
//             max = buf;
//         }
//         if (buf < min)
//         {
//             min = buf;
//         }
//     }
//     delt_m = max - min;
//     per_m = delt_m / height;
//     i = 0;
//     for (double k = a; k < b; k += per_x, i++)
//     {
//         x_val[i] = F(k);
//     }
//     n = 0;
//     y = max;
//     while (a < b)
//     {
//         if (y > -1 * per_y and y < per_y)
//         {
//             cout << 0;
//         }
//         else
//         {
//             cout << " ";
//         }
//         for (int i = 0, k = 0; i < width; i++, k++)
//         {
//             if (k >= width)
//             {
//                 k = 0;
//             }
//             if (x_val[k] > y - per_y / 2 and x_val[k] < y + per_y / 2)
//             {
//                 cout << "*";
//             }
//             else
//             {
//                 cout << " ";
//             }
//         }
//         a += per_y;
//         y -= per_m;
//         n++;
//         cout << "|" << endl;
//     }
//     delete[] x_val;
// }