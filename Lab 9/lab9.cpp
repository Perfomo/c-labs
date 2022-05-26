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

void Clear(Stack **table)
{

    Stack *now, *prev;
    for(int i = 0; i < 8; i++)
    {
        if(table[i])
        {
            prev = now = table[i];
            while (prev)
            {
                now = prev -> next;
                prev -> next = nullptr;
                delete prev;
                prev = now;
            }
        }
        // delete table[i];
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
    cout << "-------" << endl;
}

using namespace std;

int main()
{
    const int tabl_height = 8;

    Stack **table = new Stack*[8];
    string str, hstr;
    int arr_pos = -1, stack_pos = -1; 
    while (true)
    {
        cout << "-------------------------------" << endl;
        cout << "1 - Input\n2 - Find info\n3 - View tabl\n4 - Clear table\n5 - Exit\n6 - Test" << endl;
        switch (_getch())
        {
        case '1':
            cout << "\nInput ur string: " << endl;
            cin >> str;
            cin.ignore();
            hstr = Hash(str, arr_pos);
            stack_pos = Add(str, hstr, arr_pos, table);
            if(stack_pos != -1)
            {
                cout << "\nUr string ( " << str << " ) -> ( " << hstr << " ). " << "\nPosition in array = " << arr_pos << "\nPosition on stack = " << stack_pos << "\n" << endl;
            }
            arr_pos = -1;
            stack_pos = -1;
            break;
        
        case '2':

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
            cout << "All info will be deleted!!!\n1 - ok\nelse - no" << endl;
            if(_getch() == '1')
            {
                Clear(table);
                cout << "\nDeleted..." << endl;
                Stack **table = new Stack*[8];
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