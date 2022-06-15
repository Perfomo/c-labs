#include <iostream>
#include "Source1.h"
using namespace std;

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
    int y = 16;
    int ost = x % y;
    string Lang = "ABCDEF";
    if( x < y )
    {   
        if ( ost >= 10)
        {
            for (int i = 10; i < 16; i++)
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
            for (int i = 10; i < 16; i++)
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

string Hash(string str, int &arr_pos, int size)
{
    const int str_size = str.length();

    string res = "";
    int res_len;
    uint32_t h = 3323198485;

    for (int i = 0;i < str_size; i++)
    {
        h ^= int(str[i]);
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    arr_pos = h % size;
    res = FuncRec(h, res);
    res_len = res.length();
    while (res_len < 8)
    {
        res = "0" + res;
        res_len++;
    }
    return res;
}

Stack** Create_arr(int size)
{
    Stack **table = new Stack*[size];
    for(int i = 0; i < size; i++)
    {
        table[i] = nullptr;
    }
    return table;
}

string Find_by_info(string str, Stack** table, int &arr_pos, int &stack_pos, int size)
{
    stack_pos = 0;
    cout << size << endl;
    string hstr = Hash(str, arr_pos, size);
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

string Find_by_pos(int arr_pos, int stack_pos, Stack** table, int size)
{
    if(arr_pos < 0 or arr_pos > size)
    {
        cout << "\nError... Bad arr position... must be [0," << size - 1 << "]" << endl;
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


void Clear(Stack**& table, int size)
{

    Stack *now, *prev;
    for(int i = 0; i < size; i++)
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
            cout << "\nCan't add this " << str << "->" << hstr << "\tThis word already in table or just collision :(" << endl;
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

void View(Stack **table, string rool, int size)
{
    Stack *now;
    cout << "\n-------" << endl;
    for(int i = 0; i < size; i++)
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

void Test(int amount, Stack **table, int size)
{
    string str_n = "", hstr;
    int  arr_pos = -1, col = 0, i = 0;
    cout << size <<endl;
    while(i < amount)
    {
        str_n = to_string(i);
        hstr = Hash(str_n, arr_pos, size);
        arr_pos = Add(str_n, hstr, arr_pos, table);
        if(arr_pos == -1)
        {
            col++;
        }
        i++;
    }
    cout << "\nCollisions: " << col << endl;
}

int InputSize()
{
    int size;
    while (true)
    {
        cout << "\nInput size of table: " <<endl;
        size = InputInt("all");
        if (size >= 5 and size <= 25)
        {
            break;
        }
        cout <<"\nsize must be bigger than 4 and less than 26 " << endl;
    }
    cin.ignore();
    return size;
}

int InputMax()
{
    int max;
    while (true)
    {
        cout << "\nInput max amount of words:" << endl;
        max = InputInt("all");
        if(max >= 10 and max <= 200)
        {
            break;
        }
        cout << "\nmax amount of words must be bigger than 9 and less than 201" << endl;
    }
    cin.ignore();
    return max;
}

int main()
{
    char ch;
    string str, hstr;
    bool ok  = false;
    int arr_pos = -1, stack_pos = -1, size, max, max_now = 0, new_max; 

    size = InputSize();

    max = InputMax();
    
    Stack **table = Create_arr(size);

    while (true)
    {
        cout << "-------------------------------" << endl;
        cout << "1 - Input\n2 - Find info\n3 - View tabl\n4 - Clear table\n5 - Exit\n6 - Test\n7 - new size and max words\n8 - new max words" << endl;
        switch (_getch())
        {
        case '1':
            if(max > max_now)
            {
                str = InputStr("\nInput ur string: ");
                cin.ignore();
                hstr = Hash(str, arr_pos, size);
                stack_pos = Add(str, hstr, arr_pos, table);
                if(stack_pos != -1)
                {
                    max_now++;
                    cout << "\nUr string ( " << str << " ) -> ( " << hstr << " ). " << "\nPosition in array = " << arr_pos << "\nPosition on stack = " << stack_pos << "\n" << endl;
                }
                arr_pos = -1;
                stack_pos = -1;
                ok = true;
            }
            else
            {
                cout << "\nMax amount of words: " << max << "\nUr amount of words now: " << max_now << endl;
            }
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
                hstr =  Find_by_pos(arr_pos, stack_pos, table, size);
                if(hstr != "")
                {
                    cout << "\nUr hash word is " << hstr << endl;
                }
            }
            else
            {
                str = InputStr("\nInput info: ");
                hstr = Find_by_info(str, table, arr_pos, stack_pos, size);
                if(hstr != "")
                {
                    cout << "\nUr hash word is " << hstr << "\narr position: " << arr_pos << "\nstack position: " << stack_pos << endl;
                }
            }
            cin.ignore();
            break;

        case '3':
            cout << "\n1 - Orig\n2 - Hash\nelse - All" << endl; 
            switch (_getch())
            {
            case '1':
                View(table, "", size);
                cout << "\nMax amount of words: " << max << "\nUr amount of words now: " << max_now << endl;
                break;
            
            case '2':
                View(table, "hash", size);
                cout << "\nMax amount of words: " << max << "\nUr amount of words now: " << max_now << endl;
                break;
            
            default:
                View(table, "", size);
                View(table, "hash", size);
                cout << "\nMax amount of words: " << max << "\nUr amount of words now: " << max_now << endl;
                break;
            }
            break;

        case '4':
            if(!ok)
            {
                cout << "\nInput at first..." << endl;
                break;
            }
            cout << "\nAll info will be deleted!!!\n\n1 - ok\nelse - no" << endl;
            if(_getch() == '1')
            {
                Clear(table, size);
                cout << "\nDeleted..." << endl;
                table = Create_arr(size);
                ok = false;
                max_now = 0;
            }
            break;

        case '5':
            cout << "\nHave a nice day!!!" << endl;
            Clear(table, size);
            return 0;

        case '6':
            if(ok)
            {
                cout << "\nAll info will be deleted!!!\n\n1 - ok\nelse - no" << endl;
                if(_getch() == '1')
                {
                    Clear(table, size);
                    cout << "\nDeleted..." << endl;
                    table = Create_arr(size);
                }
                else
                {
                    break;
                }
            }
            
            cout << "\nHow many it? " << endl;
            arr_pos = InputInt(">0");
            cin.ignore();

            max_now = arr_pos;
            Test(arr_pos, table, size);
            ok = true;
            
            break;
        
        case '7':
            if(ok)
            {
                cout << "\nAll info will be deleted!!!\n\n1 - ok\nelse - no" << endl;
                if(_getch() == '1')
                {
                    Clear(table, size);
                    cout << "\nDeleted..." << endl;
                }
                else
                {
                    break;
                }
            }
            size = InputSize();

            max = InputMax();

            table = Create_arr(size);
            max_now = 0;
            ok = false;
            break;
        
        case '8':
            if(max == 200)
            {
                cout << "U can't create max bigger...\nUr max is 200" << endl;
                cout << "U can create new table only...\tpress (7)" << endl; 
                break;
            }
            while (true)
            {
                new_max = InputMax();
                if(new_max > max)
                {
                    max = new_max;
                    break;
                }
                cout << "\nNew max must be bigger than old" << endl;
            }
            break;
            
        default:
            cout << "\nBad input..." << endl;
            break;
        }
    }
    return 1;
}