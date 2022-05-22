#include "Source1.h"
#include <iostream>

using namespace std;

struct Stack
{
    int num;
    Stack* next_struck;
};


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
        cout << "--------------------\n1 - Add \n2 - Delete all\n3 - View all\n4 - Del max value\n5 - Exit\n"<< endl;
        switch (_getch())
        {
            case '1':
                cout << "How many numbers u want to add?" << endl;
                n = InputInt(">0");
                for (int l = 0; l < n; l++)
                {
                    cout << "Input number: " << endl;
                    int x = InputInt("all");
                    top = InStack(x, top);

                }
                cin.ignore();
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
                cout << "\nRec view: " << endl;
                RecView(top);
                break;
            case '4':
                if (!top)
                {
                    cout << "Stack is empty!!! Add numbers..." << endl;
                    break;
                }
                top = Del_Max(top);
                cout << "Deleted" << endl;
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
