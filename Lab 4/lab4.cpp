#include <iostream>
#include <string>
#include "Source1.h"
using namespace std;

struct Stack
{
    char ch;
    Stack* next;
};

struct Stack_double
{
    double num;
    Stack_double* next_d;
};

Stack* MultDel(Stack* top, int ch, string* polish)
{
    string rev = "";
    Stack* t = top, *n = top;
    if (t -> ch == '(')
    {
        t = nullptr;
    }
    else
    {
        t = top -> next;
    }
    while (t)
    {
        if (t -> ch == '*' or t -> ch == '/')
        {
            rev += t -> ch;
            n -> next = t -> next;
            delete t;
            t = n-> next;
        }
        else
        {
            if (t -> ch == '(')
            {
                t = nullptr;
                break;
            }
            t = t -> next;
            n = n -> next;
        }
    }
    t = top;
    if (top -> ch == '*' or top -> ch == '/')
    {
        *polish += t -> ch + rev;
        top = top -> next;
        delete t;
    }
    t = new Stack;
    t -> next = top;
    t -> ch = (char)ch;
    top = t;
    return top;                  
}

Stack* PlusMin(Stack* top, int ch, string* polish)
{
    Stack* t = top, *n = top;
    string rev = "";
    if (t -> ch == '(')
    {
        t = nullptr;
    }
    else
    {
        t = top-> next;
    }
    while (t)
    {
        if (t -> ch >= 40)
        {
            if (t -> ch == '(')
            {
                t = nullptr;
                break;
            }
            rev += t -> ch;
            n -> next = t -> next;
            delete t;
            t = n-> next;
        }
        else
        {
            t = t -> next;
            n = n -> next;
        }
    }
    t = top;
    if (top -> ch  > 40)
    {
        *polish += t -> ch + rev;
        top = top -> next;
        delete t;
    }
    t = new Stack;
    t -> next = top;
    t -> ch = (char)ch;
    top = t;
    return top;
}


string InputString()
{
    string result = "";
    char ch;
    int num, mas[4] = {42, 43, 45, 47}, amount = 0, valid_skob = 0;
    bool exit = false, is_last_char = false, is_last_op = true, is_op = false, is_last_skob = false;


    while (!exit)
    {
        cout << "Fast exit - 3" << endl;
        ch = _getch();
        num = int(ch);
        if (ch == '3')
        {
            cout << "Fast exit!" << endl;
            return "";
        }

        if (ch == '\n')
        {
            if (amount == 0 and is_last_char == true and result.length() > 2)
            {
                return result;
            }
            else
            {
                cout << "Problems with your string..." << endl;
            }
        }
        cout << "-------------" << endl;
        cout << "Your input is: " << ch << endl;
        if (num >= 97 and num <= 122)
        {
            if(is_last_char == false)
            {
                is_last_skob = false;
                result += ch;
                valid_skob++;
                is_last_char = true;
                is_last_op = false;
            }
            else
            {
                cout << "Too many arguments..." << endl;
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                if (num == mas[i])
                {
                    is_op = true;
                }
            }
            if (is_op == true)
            {
                if (is_last_op == false) 
                {
                    is_last_skob = false;
                    result += ch;
                    valid_skob++;
                    is_last_op = true;
                    is_last_char = false;
                }
                else
                {
                    cout << "Too many op..." << endl;
                }
            }
            else
            {
                switch (num)
                {

                case 40:
                    if(is_last_op == true)
                    {
                        is_last_skob = false;
                        result += ch;
                        valid_skob = 1;
                        amount--;
                    }
                    else
                    {
                        cout << "Can't add '(' here..." << endl;
                    }
                    break;
                
                case 41:
                    if (is_last_char == true and amount < 0 and (valid_skob >= 4 or is_last_skob == true))
                    {
                        result += ch;
                        is_last_skob = true;
                        amount++;
                    }
                    else
                    {
                        cout << "Can't add ')' here..." << endl;
                    }
                    break;
                default:
                    cout << "Bad input..." << endl;
                    break;
                }
            }
            
        }
        cout << "Your string is: " << result << endl;
        is_op = false;
    }
    return "";  
}

string StrToPolish(string str)
{
    int ch;
    string polish = "";
    Stack* top = new Stack;
    if (top)
    {
        top -> ch = (char)0;
    }
    for(int i = 0; i < str.length(); i++)
    {
        ch = int(str[i]);
        if(ch >= 97 and ch <= 122)
        {
            polish += (char)ch;
        }
        else
        {
            Stack* t = new Stack;
            switch (ch)
            {
            case 40:
            {
                t -> next = top;
                t -> ch = (char)ch;
                top = t;
                break;
            }
            case 41:
            {
                Stack* t = top;
                while (top -> ch != '(')
                {
                    t = top;
                    top = top -> next;
                    polish += t -> ch;
                    delete t;
                }
                t = top;
                top = top -> next;
                delete t;
                break;
            }
            case 42:
            {
                top = MultDel(top, ch, &polish);
                break;
            }
            case 47:
            {
                top = MultDel(top, ch, &polish);
                break;
            }
            case 45:
            {
                top = PlusMin(top, ch, &polish);
                break;
            }
            case 43:
            {
                top = PlusMin(top, ch, &polish);
                break;
            }
            default:
                break;
            }
        }
    }
    while(top -> ch != char(0))
    {
        Stack* t = top;
        top = top ->next;
        polish += t -> ch;
        delete t;
    }
    delete top;
    return polish;
}
string ArgsInString(string polish)
{
    int num;
    int len_polish = polish.length();
    bool is = false;
    string res = "";
    for (int i = 0; i < len_polish; i++)
    {
        num = int(polish[i]);
        if(num >= 97 and num <= 122)
        {
            for (int k = 0; k < res.length(); k++)
            {
                if(polish[i] == res[k])
                {
                    is = true;
                }
            }
            if (!is)
            {
                res += polish[i];
            }
            else
            {
                is = false;
            }
        }
    }
    return res; 
}

void ClearAll(Stack* top, Stack_double* top_doub)
{
    while (top)
    {
        Stack* t = top;
        top = top -> next;
        delete t;
    }
    while (top_doub)
    {
        Stack_double* n = top_doub;
        top_doub = top_doub -> next_d;
        delete n;
    }
}

double* GetMas(string arg)
{
    double* mas = new double(arg.length());
    for (int i = 0; i < arg.length(); i++)
    {
        cout << "Input " << arg[i] << ": " << endl;
        mas[i] = InputDouble("all");
    }
    return mas;
}

int WhatNum(char ch, string arg)
{
    for(int i = 0; i < arg.length(); i++)
    {
        if (ch == arg[i])
        {
            return i;
        }
    }
    return -1;
}

double GetRes(string polish)
{
    
    string arg;
    double *mas;

    if (polish == "abc+de*-/")
    {
        arg = "abcde";
        cout << "-----------------------------" << endl;
        cout << "1 - test input\nelse - ur input" << endl;
        if (_getch() == '1')
        {
            double nums[5] = {7.6, 4.8, 3.5, 9.1, 0.2};
            mas = new double(arg.length());
            for (int i = 0; i < 5; i++)
            {
                mas[i] = nums[i];
            }
        }
        else
        {
            arg = ArgsInString(polish);
            mas = GetMas(arg);
        }
    }
    else
    {
        arg = ArgsInString(polish);
        mas = GetMas(arg);
    }
    Stack_double* top_doub = new Stack_double; 
    Stack* top = new Stack;
    top -> ch = polish[0];
    top -> next = nullptr;
    int num, polish_len = polish.length();
    double res_mas = 0, op1, op2; 
    for (int i = 1; i < polish_len; i++)
    {
        num = int(polish[i]);
        if(num >= 97 and num <= 122)
        {
            Stack* t = new Stack;
            t -> ch = polish[i];
            t -> next = top;
            top = t;
        }
        else
        {
            if(top -> ch == 'E')
            {
                op1 = top_doub -> num;
                top_doub = top_doub -> next_d;
            }
            else
            {
                op1 = mas[WhatNum(top -> ch, arg)];
            }
            if(top->next->ch != 'E')
            {
                op2 = mas[WhatNum(top -> next -> ch, arg)];
            }
            else
            {
                op2 = top_doub -> num;
                Stack_double* n = top_doub;
                top_doub = top_doub -> next_d;
                delete n;
            }
            Stack* t = top;
            switch (polish[i])
            {
            case '-':
            {
                res_mas = op2 - op1;
                break;
            }
            case '+':
            {
                res_mas = op2 + op1;
                break;
            }
            case '*':
            {
                res_mas = op2 * op1;
                break;
            }
            case '/':
            {
                if (op1 == 0)
                {
                    cout << "Error... devision by 0" << endl;
                    ClearAll(top, top_doub);
                    delete[] mas;
                    return 0;
                }
                res_mas = op2 / op1;
                break;
            }
            default:
                break;
            }
            top = top -> next;
            delete t;
            top -> ch = 'E';
            Stack_double* n = new Stack_double;
            n -> next_d = top_doub;
            n -> num = res_mas;
            top_doub = n;
        }
    } 
    cout << "Result: " << res_mas << endl;
    delete[] mas;
    return res_mas;
}

int main()
{
    double res;
    string str = "", polish = "";
    while (true)
    {
        cout << "-----------------------------" << endl;
        cout << "1 - New string\n2 - Polish view\n3 - View result\n4 - Exit" << endl;
        switch (_getch())
        {
        case '1':
            polish = "";
            str = "";
            cout << "-----------------------------" << endl;
            cout << "1 - test\nelse - input" << endl;
            if (_getch() == '1')
            {
                str = "a/(b+c-d*e)";
            }
            else
            {
                cout << "Input your string: " << endl;
                str = InputString();
            }
            cout << str << endl;
            break;
        
        case '2':
            if (str == "")
            {
                cout << "string is empty!!!" << endl;
            }
            else
            {
                polish = StrToPolish(str);
                cout << polish << endl;
            }
            break;

        case '3':
            if (polish != "")
            {
                res = GetRes(polish);
            }
            else
            {
                cout << "Some problems with ur polish string" << endl;
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
    return 1;
}