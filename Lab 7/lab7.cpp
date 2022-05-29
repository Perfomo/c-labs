using namespace std;
#include <iostream>
#include <iomanip>
#include <math.h>
#include "Source1.h"

//Sin^2(x) + 3Cos(x)

string str_n(double x)
{
    string x_str = to_string(x);
    int size = 12, x_size = x_str.length();
    while(size > x_size)
    {
        x_str += " ";
        ++x_size;
    }
    return x_str;
}

double F(double x)
{
    return pow(sin(x),2) + 3 * cos(x);
    // return 4 * x - 7 * sin(x);
}

double Lagr(double *arr_x, double x, int m, double *arr_y)
{
    int i, k;
    double e, y = 0;
    for(k = 0; k < m; k++)
    {
        e=1.;
        for(i = 0; i < m; i++)
        {
            if (i != k)
            {
                e *= ((x - arr_x[i]) / (arr_x[k] - arr_x[i]));
            }
        }
        y += e * arr_y[k];
    }
    return y;
}

double Newton(double x, int n, double* arr_x, double* arr_y)
{
    double sum = arr_y[0];
    for(int i = 1; i < n; ++i)
    {
        
        double F = 0;
        for(int j = 0; j <= i; ++j)
        {
            double den = 1;
            for(int k = 0; k <= i; ++k)
            {
                if (k != j) 
                {
                    den *= (arr_x[j] - arr_x[k]);
                }
            }
            F += arr_y[j] / den;
        }
        
        for(int k = 0; k < i; ++k)
        {
            F *= (x - arr_x[k]);
        }
        sum += F;
    }
    return sum;
}


int main()
{
    double a, b, h, h1, *arr_x, *arr_y, *arr_y_l, *arr_y_n, x, y, Lagr_error = 0, Newt_error = 0, Lagr_delt, Newt_delt;
    int m, n;
    bool input = false, exit1 = false;
    while (true)
    {
        cout << "---------------------------" << endl;
        cout << "1 - Input values\n2 - result\n3 - Exit" << endl;
        switch (_getch())
        {
        case '1':
            input = true;
            cout << "\n1 - Test\nelse - Your input" << endl;
            if(_getch() == '1')
            {
                a = -7;
                b = 10;
                m = 5;
                n = 11;
                cout << "\nTest values a = -7, b = 10, m = 5, n = 11"<< endl;
            }
            else
            {
                while (true)
                {
                    cout << "\nInput a: " << endl;
                    a = InputDouble("all");
                
                    cout << "\nInput b: " << endl;
                    b = InputDouble("all");
                    if(a != b)
                    {
                        break;
                    }
                    cout << "\nError a = b..." << endl;
                }
            
                if(a > b)
                {
                    cout << "\nSwaping a and b..." << endl;
                    h = a;
                    a = b;
                    b = h;
                }
                
                while (!exit1)
                {

                    while(!exit1)
                    {
                        cout << "\nInput m: " << endl;
                        m = InputDouble(">0");
                        if ( m >= 5)
                        {
                            break;
                        }
                        cout << "\nm must be >= 5" << endl;
                    }

                    while(!exit1)
                    {
                        cout << "\nInput n: " << endl;
                        n = InputDouble(">0");
                        if ( n > m)
                        {
                            exit1 = true;
                            break;
                        }
                        cout << "\nBad input... n <= m \t Reinput pls" << endl;
                    }
                }
                exit1 = false;
            }
    
            h = (b - a) / (m - 1);
            h1 = (b - a) / (n - 1);
            break;

        case '2':
            if(input)
            {
                arr_x = new double[m + 1];
                arr_y = new double[m + 1];
                x = a;
                cout << "\nBefore: " << endl;
                cout << "---------------------------" << endl;
                cout << "|     x      |     y      |" << endl;
                cout << "---------------------------" << endl;
                for(int i = 0; i < m; i++)
                {
                    arr_x[i] = x;
                    arr_y[i] = F(x);
                    system(("echo '" + to_string(x) + " " + to_string(arr_y[i]) + "' >> points_before").c_str());
                    cout << "|" << setw(12) << x << "|" << setw(12) << arr_y[i] << "|" << endl;
                    x += h;
                }
                cout << "---------------------------" << endl;
                cout << endl;

                x = a;
                arr_y_l = new double[n + 1];
                arr_y_n = new double[n + 1];
                cout << "\nAfter: " << endl;
                cout << "-------------------------------------------------------------------------------" << endl;
                cout << "|     x      |     y      |    y Lagr  |  |y - yl|  |    y Newt  |  |y - yn|  |" << endl;
                cout << "-------------------------------------------------------------------------------" << endl;
                for(int i = 0; i < n; i++, x += h1)
                {   
                    arr_y_l[i] = Lagr(arr_x, x, m, arr_y);
                    arr_y_n[i] = Newton(x, m, arr_x, arr_y);
                    y = F(x);

                    Lagr_delt = abs(y - arr_y_l[i]);
                    Newt_delt = abs(y - arr_y_n[i]);

                    if(Lagr_error < Lagr_delt)
                    {
                        Lagr_error = Lagr_delt;
                    }
                    if(Newt_error < Newt_delt)
                    {
                        Newt_error = Newt_delt;
                    }

                    cout << "|" << setw(12) << x << "|" << setw(12) << y << "|" << setw(12) << arr_y_l[i] << "|" << setw(12) << Lagr_delt << "|" << setw(12) << arr_y_n[i] << "|" << setw(12) << Newt_delt << "|" << endl;

                    system(("echo '" + to_string(x) + " " + to_string(arr_y_l[i]) + "' >> points_after_l").c_str());
                    system(("echo '" + to_string(x) + " " + to_string(arr_y_n[i]) + "' >> points_after_n").c_str());
                }
                cout << "-------------------------------------------------------------------------------" << endl;
                cout << "\nThe error of Lagr method: " << Lagr_error << endl;
                cout << "\nThe error of Newt method: " << Newt_error << endl;

                Lagr_error = 0, Newt_error = 0, Lagr_delt = 0, Newt_delt = 0;
                system("echo 'plot \"points_after_l\" with lines, \"points_before\"  with lines, \"points_after_n\" ' | gnuplot --persist ");
                system("rm 'points_after_l'");
                system("rm 'points_after_n'");
                system("rm 'points_before'");
                delete[] arr_x;
                delete[] arr_y;
                delete[] arr_y_l;
                delete[] arr_y_n;
            }
            else
            {
                cout << "\nInput at first!!!" << endl;
            }
            break;

        case '3':
            cout << "\nHave a nice day!" << endl;
            return 0;

        default:
            cout << "\nError, bad input!" << endl;
            break;
        }
    }
    return 1;
}





// double Method_Newt(double* x, double* y, double xt, int m) {
//     int i, k = 1;
//     double N, p = 1, * d;
//     d = new double[m + 1];
//     for (i = 1; i <= m; i++) {
//         d[i] = y[i - 1];
//     }
//     N = y[0];
//     for (k - 1; k <= m - 1; k++) {
//         for (i = 1; i < m - k; i++) {
//             d[i] = (d[i] - d[i + 1]) / (x[i - 1] - x[i - 1 + k]);
//         }
//         p *= (xt - x[k - 1]);
//         N += p * d[1];
//     }
//     delete[] d;
//     return N;
// }