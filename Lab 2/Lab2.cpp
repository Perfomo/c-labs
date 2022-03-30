// #include "Source1.h"
#include <iostream>

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

struct Stack
{
    int num;
    Stack* next_struck;
}*top;


Stack* InStack(int struck_num, Stack* top)
{
    Stack* new_struck = new Stack;

    new_struck -> num = struck_num;
    new_struck -> next_struck = top;

    return new_struck;
}

int RecView(Stack* top)
{
    cout << top -> num << "\t";
    if (!top->next_struck)
    {
        cout << endl;
        return 0;
    }
    RecView(top->next_struck);
}

void ViewStuck(Stack* next_struck)
{
    Stack* new_top = next_struck;
    while (new_top)
    {
        cout << new_top -> num << "\t";
        new_top = new_top -> next_struck;
    }
    cout<<endl;
}

void Del_All(Stack** top)
{
    Stack* t;
    while (*top)
    {
        t = *top;
        *top = (*top) ->next_struck;
        delete t;
    }
}
Stack* Del_Max(Stack*top)
{
    Stack* p = top, *t = top->next_struck;
    int max = top->num;
    while (t)
    {
        if(max < t->num)
            max = t->num;
        t = t ->next_struck;
    }
    t = top->next_struck; 
    while (t)
    {
        if(t->num == max) {
            p->next_struck = t->next_struck;
            delete t;
            t = p->next_struck;
        } 
        else{
            p = t;
            t = t->next_struck;
        }
    }
    if(top->num == max) {
            t = top;
            top = top->next_struck;
            delete t;
        } 
    return top;
}


Stack* N13_2(Stack* top)
{
    Stack* t = top, **p, *k = top -> next_struck, *last_top = top;
    int max_value = top -> num;
    while(top)
    {
        if (top -> num > max_value)
        {
            max_value = top -> num;
        }
        top = top -> next_struck;
    }
    top = t;
    while (top)
    {
        if (top -> num == max_value)
        {
            if (top == last_top)
            {
                last_top = k;
            }
            p = &top;
            delete *p;
            top = k;
            if (t)
            {
                t -> next_struck = top;
            }
            if (k)
            {
                k = k -> next_struck;
            }
            else
            {   
                top = last_top;
                return top;
            }
        }
        else
        {
            if (t != top)
            {
                t = t -> next_struck;
            }
            top = top -> next_struck;
            if (k)
            {
                k = k -> next_struck;
            }
        }
    }
    return last_top;
}

int main()
{
    Stack* top = nullptr;
    bool ok = false;
    int x, n;
    while (!ok)
    {
        cout << "--------------------\n1 - add \n2 - delete all\n3 - view all\n4 - find max value\n5 - exit\n" << "Input what u want to do: " << endl;
        switch (_getch())
        {
            case '1':
                cout << "How many numbers u want to add?" << endl;
                // n = InputInt(">0");
                cin >> n;
                for (int l = 0; l < n; l++)
                {
                    cout << "Input number: " << endl;
                    // int x = InputInt("all");
                    cin >> x;
                    top = InStack(x, top);

                }
                break;
            
            case '2':

                cout << "Are u sure to delete all?\n"<< "1 - yes\nelse - no" << endl;

                if (_getch() == '1')
                {
                    Del_All(&top);
                }
                
                break;
            
            case '3':

                if (!top)
                {
                    cout << "Stack is empty!!! Add numbers..." << endl;
                    break;
                }

                ViewStuck(top);
                cout << "--" << endl;
                RecView(top);
                break;
            case '4':
                if (!top)
                {
                    cout << "Stack is empty!!! Add numbers..." << endl;
                    break;
                }
                // top = N13_2(top);
                top = Del_Max(top);
                break;

            case '5':

                cout << "Have a nice day!!! " << endl;
                ok = true;
                return 0;

            default:

                cout << "Bad input( Try again... " << endl;
                break;
        }
    }
}

/*
int N13(Stack* top, int n)
{
    Stack* t = top, **p = &top, *k = top -> next_struck;
    int max_value = top -> num, ammount = n;
    for (int i = 1; i < n; i++)
    {
        top = top -> next_struck;
        if (top -> num > max_value)
        {
            max_value = top -> num;
        }
    }
    top = t;
    for (int i = 0; i < n; i++)
    {
        
        if (top -> num == max_value)
        {   
            p = &top;
            delete *p;
            ammount--;
            
            top = k;
            
            t -> next_struck = top;
            if (i == n-1)
            {
                return ammount;
            }
            if (i != n-2)
            {
                k = k -> next_struck;
            }
            n--;
        }
        top = top -> next_struck;
        if (k)
        {
            k = k -> next_struck;
        }
        if (i!=0)
        {
            t = t -> next_struck;
        }
    }
    cout << max_value << endl;

    return ammount;
}
// p = &top;
// l = *p;
// delete l;
*/