#include <iostream>
//#include "Source1.h"
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

string InputStr(string message)
{
    int str_size, code;
    bool ok = true;
    string str;
    while (true)
    {
        cout <<  message << endl;
        cin >> str;
        str_size = str.length();
        for(int i = 0; i < str_size; i++)
        {
            code = int(str[i]);
            if(code > 126 or code < 33)
            {
                i = str_size;
                ok = false;
            }
        }
        if(ok)
        {
            return str;
        }
        else 
        {
            cout << "Bad string..." << endl;
            ok = true;
        }
    }
}

string FuncRec(uint32_t x, string x5)
{
    int y =16;
    int ost = x % y;
    string Lang = "ABCDIFGHIJKLMNOPQRSTUVWXYZ";
    if( x < y )
    {   
         if ( ost >= 10)
        {
            for (int i = 10; i < 27; i++)
            {
                if ( i == ost )
                {
                    x5 = Lang[i - 10] +  x5;
                    return x5; 
                }
            }
        }
        return to_string(x) + x5;
    }
    else
    {
        if ( ost >= 10)
        {
            for (int i = 10; i < 27; i++)
            {
                if ( i == ost )
                {
                    x5 = Lang[i - 10] +  x5;
                    return FuncRec(x / y, x5); 
                }
            }
        }
        x5 = to_string(ost) + x5;
        return FuncRec(x / y, x5);
    }
}

struct Stack
{
    string info, orig;
    Stack *next; 
};

string Hash(string str, int &arr_pos)
{
    const int hstr_size = 8;
    const int str_size = str.length();

    string res = "";
    uint32_t h = 3323198485ul;

    for (int i = 0;i < str_size; i++)
    {
        h ^= int(str[i]);
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    arr_pos = h % 8;
    return FuncRec(h, res);
}

Stack** Create_arr()
{
    Stack **table = new Stack*[8];
    for(int i = 0; i < 8; i++)
    {
        table[i] = nullptr;
    }
    return table;
}

string Find_by_info(string str, Stack** table, int &arr_pos, int &stack_pos)
{
    stack_pos = 0;
    string hstr = Hash(str, arr_pos);
    Stack *now = table[arr_pos];
    if(now)
    {
        stack_pos++;
        now = now -> next;
    }
    else
    {
         cout << "\n404 not found..." << endl;
        return "";
    }
    while (now)
    {
        if(hstr == now -> info)
        {
            return hstr;
        }
        now = now -> next;
        stack_pos++;
    }
    cout << "\n404 not found..." << endl;
    return "";
}

string Find_by_pos(int arr_pos, int stack_pos, Stack** table)
{
    if(arr_pos < 0 or arr_pos > 8)
    {
        cout << "\nError... Bad arr position... must be [0,8]" << endl;
        return "";
    }
    Stack *now = table[arr_pos];
    int i = 0;
    while(now and i != stack_pos)
    {
        now = now -> next;
        i++;
    }
    if(i != stack_pos)
    {
        cout << "\nError... Bad stack position... (Arr line is null or last info so far from this position)"<< endl;
        return "";
    }    
    return now -> info;
}


void Clear(Stack**& table)
{

    Stack *now, *prev;
    for(int i = 0; i < 8; i++)
    {
        if(table[i])
        {
            prev = table[i];
            now = table[i] -> next;
            table[i] -> next = nullptr;
            delete prev;
            prev = now;
            while(prev)
            {
                now = prev -> next;
                prev -> next = nullptr;
                delete prev;
                prev = now;
            }
        }
        table[i] = nullptr;
    }
    delete[] table;
}

int Add(string str, string hstr, int arr_pos,  Stack **table)
{
    int stack_pos = 0; 
    Stack *now, *prev;

    prev = now = table[arr_pos];
    while (now)
    {
        prev = now;
        stack_pos++;
        now = now -> next;
    }
    if (prev == now)
    {
        stack_pos = 1; 
        table[arr_pos] = new Stack;
        Stack* add = new Stack;
        add -> info = hstr;
        add -> next = nullptr;
        add -> orig = str;
        table[arr_pos] -> next = add;
    }
    else
    {
        if(prev -> info == hstr)
        {
            cout << "\nCan't add this info... This word already in table or just collision :(" << endl;
            return -1;
        }
        Stack* add = new Stack;
        add -> info = hstr;
        add -> next = nullptr;
        add -> orig = str;
        prev -> next = add;
    }
    return stack_pos;
}

void View(Stack **table, string rool)
{
    Stack *now;
    cout << "\n-------" << endl;
    for(int i = 0; i < 8; i++)
    {
        now = table[i];
        if(!now)
        {
            cout << "null" << endl;
        }
        else
        {
            cout << i;
            now = now -> next;
            if(rool == "hash")
                while (now)
                {
                    cout << " <- " << now -> info;
                    now = now -> next;
                }
            else
            {
                while (now)
                {
                    cout << " <- " << now -> orig;
                    now = now -> next;
                }
            }
            cout << endl;
        }
    }
    cout << "-------\n" << endl;
}

using namespace std;

int main()
{
    const int tabl_height = 8;

    Stack **table = Create_arr();
    string str, hstr;
    bool ok  = false;
    int arr_pos = -1, stack_pos = -1; 
    while (true)
    {
        cout << "-------------------------------" << endl;
        cout << "1 - Input\n2 - Find info\n3 - View tabl\n4 - Clear table\n5 - Exit\n6 - Test" << endl;
        switch (_getch())
        {
        case '1':
            str = InputStr("\nInput ur string: ");
            cin.ignore();
            hstr = Hash(str, arr_pos);
            stack_pos = Add(str, hstr, arr_pos, table);
            if(stack_pos != -1)
            {
                cout << "\nUr string ( " << str << " ) -> ( " << hstr << " ). " << "\nPosition in array = " << arr_pos << "\nPosition on stack = " << stack_pos << "\n" << endl;
            }
            arr_pos = -1;
            stack_pos = -1;
            ok = true;
            break;
        
        case '2':
            if(!ok)
            {
                cout << "\nInput at first..." << endl;
                break;
            }
            cout << "\n1 - Find by position\nElse - Find by info" << endl;
            if(_getch() == '1')
            {
                cout << "\nInput arr position:" << endl;
                cin >> arr_pos;
                cout << "\nInput stack position:" << endl;
                cin >> stack_pos;
                hstr =  Find_by_pos(arr_pos, stack_pos, table);
                if(hstr != "")
                {
                    cout << "\nUr hash word is " << hstr << endl;
                }
            }
            else
            {
                str = InputStr("\nInput info: ");
                hstr = Find_by_info(str, table, arr_pos, stack_pos);
                if(hstr != "")
                {
                    cout << "Ur hash word is " << hstr << "\narr position: " << arr_pos << "\nstack position: " << stack_pos << endl;
                }
            }
            cin.ignore();
            break;

        case '3':
            cout << "\n1 - Orig\n2 - Hash\nelse - All" << endl; 
            switch (_getch())
            {
            case '1':
                View(table, "");
                break;
            
            case '2':
                View(table, "hash");
                break;
            
            default:
                View(table, "");
                View(table, "hash");
                break;
            }
            break;

        case '4':
            if(!ok)
            {
                cout << "Input at first..." << endl;
                break;
            }
            cout << "All info will be deleted!!!\n1 - ok\nelse - no" << endl;
            if(_getch() == '1')
            {
                Clear(table);
                cout << "\nDeleted..." << endl;
                table = Create_arr();
            }
            break;

        case '5':
            cout << "\nHave a nice day!!!" << endl;
            Clear(table);
            return 0;

        case '6':

            break;

        default:
            cout << "\nBad input..." << endl;
            break;
        }
    }
    return 1;
}