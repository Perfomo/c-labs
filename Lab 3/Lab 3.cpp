#include <iostream>
#include "Source1.h"
using namespace std;

struct Stack
{
    int num;
    Stack* next, *prev;
};

Stack* Del_Max(Stack*top, Stack*& end)
{
    Stack* p = top, *t = top->next;
    int max = top->num;
    if (top == end)
    {
        delete top;
        end=top=nullptr;
        return top;
    }
    while (t)
    {
        if(max < t->num)
        {
            max = t->num;
        }
        t = t ->next;
    }
    
    t = top -> next;
    while (t!=end)
    {
        if(t -> num == max)
        {
            p->next = t->next;
            t->next->prev = p;
            delete t;
            t = p->next;
        }
        else
        {
            t = t->next;
            p = p->next;    
        }
    }
    if(end -> num == max)
    {
        t = end;
        end = end -> prev;
        end -> next = nullptr;
        delete t;
    }
    if(top -> num == max)
    {
        if(top == end)
        {
            delete top;
            return top = nullptr;
        }
        else
        {
        t = top;
        top = top -> next;
        top -> prev = nullptr;
        delete t;
        }   
    }
    return top;
}

Stack* Add_beg(Stack* top, int amount, Stack*& end)
{
    int n;
    if (!top)
    {
        Stack* t = new Stack;
        cout << "Input number: " << endl;
        n = InputInt("all");
        t -> num = n;
        t -> next = top; 
        t -> prev = nullptr;
        end = t;
        top = t;
        amount--;
    }
    for (int i = 0; i < amount; i++)
    {
        Stack* t = new Stack;
        cout << "Input number: " << endl;
        n = InputInt("all");
        t -> num = n;
        t -> next = top; 
        top -> prev = t;
        top = t;
    }
    top -> prev = nullptr;
    cin.ignore();
    return top;
}

Stack* Add_end(Stack* end, int amount)
{
    int n;
    for(int i = 0; i < amount; i++)
    {
        Stack* t = new Stack;
        cout << "Input number: " << endl;
        n = InputInt("all");
        end -> next = t;
        t -> prev = end;
        t -> next = nullptr;
        t -> num = n;
        end = t;
    }
    cin.ignore();
    return end;
}

void View_front(Stack* top)
{
    while (top)
    {
        cout << "\t" << top -> num;
        top = top -> next;
    }
    cout << endl;
}
void View_end(Stack* end)
{
    while (end)
    {
        cout << "\t" << end -> num;
        end = end -> prev;
    }
    cout << endl;
}

void Del_all(Stack* top)
{
    Stack* t = new Stack; 
    while (top)
    {
        t = top;
        top = top -> next;
        delete t;
    }
}
Stack* Rec_del_front(Stack*& top, int amount, Stack*& end)
{
    if (!top)
    {
        end = nullptr;
        return top = nullptr;
    }
    if (amount != 0)
    {   Stack* t = top;
        top = top->next;
        delete t;
        Rec_del_front(top, --amount, end);
    }
    else 
    {
        if (top == end)
        {
            top -> next = top -> prev = nullptr;
            return top;
        }
        else
        {
            top -> prev = nullptr;
            return top;
        }
    }
}
Stack* Rec_del_end(Stack*& top, int amount, Stack*& end)
{
    if (!end)
    {
        top = nullptr;
        return end = nullptr;
    }
    if (amount != 0)
    {   Stack* t = end;
        end = end->prev;
        delete t;
        Rec_del_end(top, --amount, end);
    }
    else 
    {
        if (end == top)
        {
            end -> next = end -> prev = nullptr;
            return end;
        }
        else
        {
            end -> next = nullptr;
            return end;
        }
    }
}

int main()
{
    char ch;
    int amount = 0, pos = 0;
    bool ok = false;
    Stack *top = nullptr, *end = nullptr;
    while (!ok)
    {
        cout << "------------\n" <<"What u want to do?\n1 - Add\n2 - Del\n3 - View\n4 - Del max\n5 - Exit\n------------" << endl;
        switch (_getch())
        {
            case '1':
                cout << "How many numbers u want to add?" << endl;
                amount = InputInt(">0");
                cin.ignore();
                cout << "Were u want to add?\n1 - in the beg\n2 - in the end" << endl;
                switch (_getch())
                {
                    case '1':
                        top = Add_beg(top, amount, *&end);
                        break;
                
                    case '2':
                        if(!end)
                        {
                            top = Add_beg(top, amount, *&end);
                        }
                        else
                        {
                            end = Add_end(end, amount);
                        }
                        break;

                    default:
                        cout << "Bad input..." << endl;
                        break;
                }
            break;

            case '2':
            if (!top)
                {
                    cout << "Stack is empty!!! Add numbers..." << endl;
                    break;
                }
                cout << "1 - Delete n from the beg\n2 - Delete all\n3 - Delete n from the end" << endl;
                switch (_getch())
                {
                    case '1':
                        cout << "How many n u want to del?: "<< endl;
                        amount = InputInt(">0");
                        cin.ignore();
                        top = Rec_del_front(*&top, amount, *&end);
                        cout << "Deleted" << endl;
                        break;

                    case '2':
                        Del_all(top);
                        top = end = nullptr;
                        cout << "Deleted" << endl;
                        break;
                    
                    case '3':
                        cout << "How many n u want to del?: "<< endl;
                        amount = InputInt(">0");
                        cin.ignore();
                        end = Rec_del_end(*&top, amount, *&end);
                        cout << "Deleted" << endl;
                        break;
                    default:
                        cout << "Bad input..." << endl;
                        break;
                }
            break;

            case '3':
                if (!top)
                {
                    cout << "Stack is empty!!! Add numbers..." << endl;
                }
                else 
                {
                    cout << "From the beg: ";
                    View_front(top);
                    cout << endl;
                    cout << "From the end:";
                    View_end(end);
                    cout << endl;
                }
                break;

            case '4':
                if (!top)
                {
                    cout << "Stack is empty!!! Add numbers..." << endl;
                }
                else 
                {
                    top = Del_Max(top, *&end);
                }
                break;

            case '5':
                cout << "Have a nice day!!!" << endl;
                ok = true;
                break;

        default:

            cout << "Bad input!!! Try again..." << endl;
            break;
        }
    }
    

    return 0;
}