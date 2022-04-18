#include <iostream>
#include <math.h>
using namespace std;
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

// Sin^2(x) - 3Cos(X);
double F(double x)
{
    // return pow(sin(x),2) - 3*cos(x);
    return 4*x - 7*sin(x);
}

double FindKeyCekLine(double x0, double h, double e)
{
    double y0,x1,de,yd;
    y0 = F(x0);
    yd = F(x0 - h);
    do
    {
        x1 = x0 - y0 * h / (y0 - yd);
        de = fabs(x0-x1);
        x0 = x1;
        yd = y0;
        y0 = F(x1);
    }   while (de > e);
    return x1;
}

double Fun_Del_2(double x0,double x1,double e)
{
    double x2,y0,y2;
    y0=F(x0);
    do
    {
        x2 = (x0 + x1) / 2;
        y2 = F(x2);
        if(y0 * y2 > 0)
        {
            x0 = x2;
            y0 = y2;
        }
        else x1 = x2;
    } while (fabs(x1 - x0) > e);
    return (x0 + x1) / 2;
  } 

void View(double a, double b, double h)
{
    int height = 20, width = 120, amount = (b - a) / h, n = 0, y_am;
    double delt = b - a, max, min, delt_y, per_y = (b - a) / height, per_x = (b - a) / width, buf,y;
   
    double *y_val = new double[height];
    double *x_val = new double[width];
    int i = 0;
    
    for(double k = a; k < b; k += per_y, i++)
    {
        cout << i << endl;
        buf = F(k);
        y_val[i] = buf;
        cout << y_val[i] << endl;
        if(buf > max)
        {
            max = buf;
        }
        if(buf < min)
        {
            min = buf;
        }
    }
    i = 0;
    for(double k = a; k < b; k += per_x, i++)
    {
        x_val[i] = F(k);
    }
    y = max;
    while (y > min)
    {
        for(int i = 0, k = 0; i < width; i++,k++)
        {
            if( k >= width)
            {
                k = 0;
            }
            if(x_val[k] > y - per_y / 2 and x_val[k] < y + per_y / 2)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        y -= per_y;
        cout << endl;
    } 

    // i = 1;

    // for(double k = a; k < b; k += per_y)
    // {
    //     buf = F(k);
    //     if(buf > max)
    //     {
    //         max = buf;
    //     }
    //     if(buf < min)
    //     {
    //         min = buf;
    //     }
    // }
    // buf = a;
    // while (max > min)
    // {
    //     for(int i = 0; i < width; i++)
    //     {
    //         y = F(buf);
    //         if(y > max - per_y / 2 and y < max + per_y / 2)
    //         {
    //             cout << "*";
    //         }
    //         else
    //         {
    //             cout << " ";
    //         }
    //         buf += per_x;
    //     }
    //     buf = a;
    //     max -= per_y;
    //     cout << endl;
    // } 
}

int main()
{
    bool exit = false;
    double a = 0, b = 0, h = 0.001, e = 0.005;;

    while (true)
    {
        cout << "-------------------------" << endl;
        cout << "1 - Input\n2 - View result\n3 - View graph\n4 - Exit" << endl;
        cout << "-------------------------" << endl;
        switch (_getch())
        {
        case '1':
            cout << "1 - Test\nelse - Ur input" << endl;
            if (_getch() == '1')
            {
                a = -7;
                b = 3;
                // a = -2;
                // b = 2;
            }
            else
            {
                while (!exit)
                {
                    cout << "Input a: " << endl;
                    cin >> a;
                    cout << "Input b: " << endl;
                    cin >> b;
                    if(a == b)
                    {
                        cout << "Error: a = b\t reinput a and b..." << endl;
                    }
                    else
                    {
                        exit = true;
                    }
                }
                exit = false;
                if(a > b)
                {
                    h = a;
                    a = b;
                    b = h;
                    h = 0.001;
                }
            }
            break;
        
        case '2':
            if(a == b)
            {
                cout << "At first do input!!!" << endl;
            }
            else
            {
                cout << "Method 1:\nRoots:" << endl;
                for(double k = a; k < b; k+=h)
                {
                    if(F(k) * F(k+h) < 0)
                    {
                        cout << FindKeyCekLine(k,h,e) << endl;
                    }
                }

                cout << "Method 2:\nRoots:" << endl;
                for(double k = a; k < b; k+=h)
                {
                    if(F(k) * F(k+h) < 0)
                    {
                        cout << Fun_Del_2(k,k+h,e) << endl;
                    }
                }
            }
            break;

        case '3':
            View(a,b,h);
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