using namespace std;
#include <iostream>
#include <math.h>

#include <termios.h>
#include <unistd.h>
int _getch(void)
{
	struct termios oldattr, newattr;
	int ch;

	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}
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
    double a, b, h, h1, *arr_x, *arr_y, *arr_y_l, *arr_y_n, x, y;
    int m, n;
    while (true)
    {
        cout << "1 - Input values\n2 - result\n3 - Exit" << endl;
        switch (_getch())
        {
        case '1':
            cout << "1 - Test\nelse - Your input" << endl;
            if(_getch() == '1')
            {
                a = -7;
                b = 10;
                m = 5;
                n = 11;
            }
            else
            {
                cout << "Input a: " << endl;
                cin >> a;

                cout << "Input b: " << endl;
                cin >> b;

                if(a > b)
                {
                    cout << "Swaping a and b..." << endl;
                    h = a;
                    a = b;
                    b = a;
                }
                
                while (true)
                {
                    cout << "Input m: " << endl;
                    cin >> m;

                    cout << "Input n: " << endl;
                    cin >> n;
                    
                    if(n > m)
                    {
                        break;
                    }

                    cout << "Bad input... n <= m \t Reinput pls" << endl;
                }
            }

            h = (b - a) / (m - 1);
            h1 = (b - a) / (n - 1);
            break;

        case '2':
            
            arr_x = new double[m + 1];
            arr_y = new double[m + 1];
            x = a;
            cout << "\nBefore: " << endl;
            cout << "---------------------------" << endl;
            cout << "|x           |y           |" << endl;
            for(int i = 0; i < m; i++)
            {
                arr_x[i] = x;
                arr_y[i] = F(x);
                system(("echo '" + to_string(x) + " " + to_string(arr_y[i]) + "' >> points_before").c_str());
                cout << "|" << str_n(x) << "|" << str_n(arr_y[i]) << "|" << endl;
                x += h;
            }
            cout << "---------------------------" << endl;
            cout << endl;

            x = a;
            arr_y_l = new double[n + 1];
            arr_y_n = new double[n + 1];
            cout << "\nAfter: " << endl;
            cout << "----------------------------------------" << endl;
            cout << "|x           |y - Lagr    |y - Newt    |" << endl;
            for(int i = 0; i < n; i++, x += h1)
            {   
                arr_y_l[i] = Lagr(arr_x, x, m, arr_y);
                arr_y_n[i] = Newton(x, m, arr_x, arr_y);
                cout << "|" << str_n(x) << "|" << str_n(arr_y_l[i]) << "|" << str_n(arr_y_n[i]) << "|" << endl;
                system(("echo '" + to_string(x) + " " + to_string(arr_y_l[i]) + "' >> points_after_l").c_str());
                system(("echo '" + to_string(x) + " " + to_string(arr_y_n[i]) + "' >> points_after_n").c_str());
            }
            cout << "----------------------------------------" << endl;
            system("echo 'plot \"points_after_l\" with lines, \"points_before\"  with lines, \"points_after_n\" ' | gnuplot --persist ");
            system("rm 'points_after_l'");
            system("rm 'points_after_n'");
            system("rm 'points_before'");
            delete[] arr_x;
            delete[] arr_y;
            delete[] arr_y_l;
            delete[] arr_y_n;
            break;

        case '3':
            cout << "Have a nice day!" << endl;
            return 0;

        default:
            cout << "Error, bad input!" << endl;
            break;
        }
    }
    return 1;
}