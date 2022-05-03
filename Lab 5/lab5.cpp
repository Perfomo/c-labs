#include <iostream>
using namespace std;
#include "Source1.h"
#include "math.h"

struct Tree
{
    int key;
    string info;
    Tree *left, *right;
};

void GoWay1(Tree* root)
{
    if(root)
    {
        GoWay1(root -> left);
        cout << root -> key << " ";
        GoWay1(root -> right);
    }
}

void GoWay2(Tree* root)
{
    if(root)
    {
        cout << root -> key << " ";
        GoWay2(root -> left);
        GoWay2(root -> right);
    }
}

void GoWay3(Tree* root)
{
    if(root)
    {
        GoWay3(root -> left);
        GoWay3(root -> right);
        cout << root -> key << " ";
    }
}

int Go2int(Tree* root, int *&arr, int n)
{
    if(!root)
    {
        return --n;
    }
    else
    {
        cout << root -> key << " ";
        arr[n] = root -> key;
        n = Go2int(root -> left, arr, ++n);
        n = Go2int(root -> right, arr, ++n);
        return n;
    }
}

void BalanceTree(Tree*& root,int level, int n, Tree** arr)
{
    if (n == level)
    { 
        *&root = nullptr;
        return;
    }
        else {
                int m = (n + level) / 2;
                root = arr[m];
                
                BalanceTree( *&root -> left, level, m, arr);
                BalanceTree( *&root -> right, m+1, n, arr);
        }

}

int Go2(Tree* root, Tree **&arr, int n)
{
    if(!root)
    {
        return --n;
    }
    else
    {
        cout << root -> key << " ";
        arr[n] = root;
        n = Go2(root -> left, arr, ++n);
        n = Go2(root -> right, arr, ++n);
        return n;
    }
}

Tree** SortArr(Tree **arr, int n)
{
    Tree* buf;
    bool exit = false;
    for(int i = 1; i < n; i++)
    {
        for(int k = n - 1; k != i - 1; k--)
        {
            if(arr[k] -> key < arr[k - 1] -> key)
            {
                buf = arr[k - 1];
                arr[k - 1] = arr[k];
                arr[k] = buf;
                exit = false;
            }
        }
        if (exit)
        {
            return arr;
        }
        exit = true;
    }
    return arr;
}

int GetLevel(Tree* root)
{
    if(!root)
    {
        return 0;
    }
    return max(GetLevel(root -> left), GetLevel(root -> right)) + 1;
}

void DeleteAll(Tree* root)
{
    if(root)
    {
        DeleteAll(root -> left);
        DeleteAll(root -> right);
        delete root;
    }
}

Tree* RecDelByKey(Tree* root, int key)
{
    Tree* del, *k;
    int key_ ;
    string str_;
    if(key > root -> key)
    {
        if (root -> right)
        {
            del = RecDelByKey(root -> right, key);
            root -> right = del;    
        }
        else 
        {
            cout << "Can't find this number on your tree..." << endl;
        }
        return root;
    }
    if(key < root -> key)
    {
        if (root -> left)
        {
            del = RecDelByKey(root -> left, key);
            root -> left = del;
        }
        else
        {
            cout << "Can't find this number on your tree..." << endl;
        }
        return root;
    }
    else
    {
        if(root -> left and root -> right)
        {
            del = root -> right;
            while (del -> left)
            {
                del = del -> left;
            }
            str_ = del -> info;
            key_ = del -> key;
            k = RecDelByKey(root, del -> key);
            root -> key = key_;
            root -> info = str_;
            return root;

        }
        if (root -> left)
        {
            del = root -> left;
            delete root;
            return del;
        }
        if (root -> right)
        {
            del = root -> right;
            delete root;
            return del;
        }
        delete root;
        return nullptr;
    }
}

string GetInfo(Tree* root, int key)
{
    if(key == root -> key)
    {
        return root -> info;
    }
    if (key > root -> key)
    {
        if (root -> right)
        {
            return GetInfo(root -> right, key);
        }
        return "No element with this key...";
    }
    else
    {
        if (root -> left)
        {
            return GetInfo(root -> left, key);
        }
        return "No element with this key...";
    }
    return "exit with error...";
}

string GiveSpace(int level_now, int level)
{
    int line_here =  70 / pow(2 , level), del = level - level_now;
    string add = "", res = "";
    for (int i = 0; i < line_here; i++)
    {
        add += ' ';
    }
    add += ' ';
    if(del > 2)
    {
        del += del - 2;
    }
    for (int i = 1; i < del; i++)
    {
        res += add;
    }
    return res;
}

string PrintTree(Tree* root, int level_now, int level)
{
    int line_here =  70 / pow(2 , level), delt = level - level_now ;
    string left = "", right = "", add = "", res = "";

    if(delt == 0)
    {
        return to_string(root -> key);
    }
    else
    {
        if(delt > 1 and (!root -> left and !root -> right))
        {
            for (int i = 0; i < line_here - 1; i++)
            {
                add += ' ';
            }
            left = GiveSpace(level_now, level);
            right = GiveSpace(level_now, level);
            return left + add + right;
        }
        if(root -> left)
        {
            left = PrintTree(root -> left, level_now + 1, level);
        }
        else
        {
            if(delt > 1)
            {
                left = GiveSpace(level_now, level);
            }
            else
            {
                left = 'N';
            }
        }
        if(root -> right)
        {
            right = PrintTree(root -> right, level_now + 1, level);
        }
        else
        {
            if(delt > 1)
            {
                right = GiveSpace(level_now, level);
            }
            else
            {
                right = 'N';
            }
        }
        add = "";
        if(delt > 1)
        {
            if (level >= 5)
            {
                line_here += pow(2,(level - 5));
            }
            for (int i = 0; i < line_here  + 1; i++)
            {
                add += ' ';
            }
        }
        else
        {
            for (int i = 0; i < line_here - 1; i++)
            {
                add += '-';
            }
        }
        return left + add + right;
    }

}

void ViewTree(Tree* root)
{
    int preLine = 68, level = GetLevel(root);

    for(int i = 0; i <= level; i++)
    {
        preLine = preLine / 2 + 1;
        for(int k = 0; k < preLine; k++)
        {
            cout << " ";
        }
        cout << PrintTree(root, 0, i);
        cout << endl;
    }
}

string NextLevelPrintString(Tree* root, int level_now, int level)
{
    int line_here =  70 / pow(2 , level), delt = level - level_now ;
    string left = "", right = "", add = "";
    
    if(level_now == level - 1 )
    {
        for (int i = 0; i < line_here; i++)
        {
            add += '-';
        }
        if (root -> left)
        {
            left = to_string(root -> left -> key);
        }
        else
        {   
            left = "N";
        }
        if (root -> right)
        {
            right = to_string(root -> right -> key);
        }
        else
        {
            right = "N";
        }
        add = left + add + right;
        return add;
    }
    for (int i = 0; i < line_here - 2; i++)
    {
        add += ' ';
    } 
    if (delt % 2 != 0)
    {
        delt+=5;
    }
    if (root -> left)
    {
        left = NextLevelPrintString(root -> left, level_now + 1, level);
    }
    else
    {
        for (int i = 0; i <=  delt - 1; i++)
        {
            left += add;
        }
        left += ' ';
    }
    if (root -> right)
    {
        right = NextLevelPrintString(root -> right, level_now + 1, level);
    }
    else
    {
        for (int i = 0; i <  delt - 1; i++)
        {
            right += add;
        }
        right += ' ';
    }
    add = left + add + right;
    return add;
}

string GetLine(Tree* root, int level)
{
    int line_here = 70 / pow(2, level);
    string left = "", right = "", add = "";
    
    if (level == 1)
    {
        for (int i = 0; i < line_here; i++)
        {
            add += '-';
        }
        if (root -> left)
        {
            left = to_string(root -> left -> key);
        }
        else
        {   
            left = "N";
        }
        if (root -> right)
        {
            right = to_string(root -> right -> key);
        }
        else
        {
            right = "N";
        }
        add = left + add + right;
        return add;
    }
    for (int i = 0; i < line_here; i++)
    {
        add += ' ';
    }
    if (root -> left)
    {
        left = NextLevelPrintString(root -> left, 1, level);
    }
    else
    {   
        left = "N";
    }
    if (root -> right)
    {
        right = NextLevelPrintString(root -> right, 1, level);
    }
    else
    {
        right = "N";
    }
    add = left + add + right;
    return add;
}

void ViewHor (Tree *root,  int level)
{
    if (root)
    {
        ViewHor( root -> right , level + 1);  
        for (int i = 0; i < level; ++i ) 
        {
            cout << "    ";
        }
        cout << root -> key << endl;
        ViewHor( root -> left , level + 1);   
    }
}

Tree *CreateTree()
{
    int key;
    string info;
    Tree *root = new Tree;
    cout << "Input key: " << endl;
    key = InputInt("all");
    cout << "Input info: " << endl;
    cin >> info;
    root->info = info;
    root->key = key;
    root -> left = nullptr;
    root -> right = nullptr;
    return root;
}

void View(Tree* root)
{
    Tree* t = root;
    int level = GetLevel(root), rool = 35;
    for (int i = 0; i < 35; i++)
    {
        cout << " ";
    }
    cout << root -> key << endl;
    
    for(int i = 1; i <= level; i++)
    {
        rool = rool / 2 + 1;
        for(int k = 0; k < rool; k++)
        {
            cout << " ";
        }
        cout << GetLine(root, i);
        cout << endl;
        
    }
}

void AddValues(Tree *root, int n)
{
    Tree *t = root, *o;
    Tree *k = new Tree;
    int key;
    string info;
    cout << "Input key: " << endl;
    key = InputInt("all");
    cout << "Input info: " << endl;
    cin >> info;
    while(t)
    {
        if (t -> key == key)
        {
            cout << "Bad key..." << endl;
            cout << "Input key: " << endl;
            key = InputInt("all");
            t = root;
            cin.ignore();
        }
        else
        {
            if( key > t -> key)
            { 
                o = t;
                t = t -> right; 
            }
            else
            {
                o = t;
                t = t -> left; 
            }
        }
    }
    if( key > o -> key)
    { 
        o -> right = k; 
    }
    else
    {
        o -> left = k; 
    }
    k -> info = info;
    k -> key = key;
    k -> left = nullptr;
    k -> right = nullptr;
    n--;
    if (n != 0)
    {
        AddValues(root, n);
    }    
}

Tree** WorkMemTree(Tree** arr, int new_mem, int last_mem)
{
    Tree* *buf = new Tree*[new_mem];
    for (int i = 0; i < last_mem; i++)
    {
        buf[i] = arr[i];
        arr[i] = nullptr;
        delete arr[i];
    }
    delete[] arr;
    return buf;
}
int* WorkMemint(int* arr, int new_mem, int last_mem)
{
    int *buf = new int[new_mem];
    for (int i = 0; i < last_mem; i++)
    {
        buf[i] = arr[i];
    }
    delete[] arr;
    return buf;
}

int main()
{
    Tree *root = nullptr, **arr;
    bool exit = false;
    double ave = 0;
    int find_key, amount_keys = 0, n13_res = 0, *arr_i = nullptr, last_mem = 0, level;
    while (!exit)
    {
        int n = 0;
        cout << "---------------------------" << endl;
        cout << "1 - Input values\n2 - Delete\n3 - View tree\n4 - Find info\n5 - Balance tree\n6 - n13\n7 - Exit" << endl;
        cout << "---------------------------" << endl;
        switch (_getch())
        {
        case '1':
            cout << "How many values u want to add?" << endl;
            n = InputInt(">0");
            amount_keys += n;
            if (!root)
            {
                root = CreateTree();
                n--;
            }
            if (n > 0)
            {
                AddValues(root, n);
            }
            cin.ignore();
            break;

        case '2':
            cout << "1 - Delete all\nelse - Delete by key" << endl;
            if(_getch() == '1')
            {
                DeleteAll(root);
                root = nullptr;
                amount_keys = 0;
            }
            else
            {
                if (root)
                {
                    cout << "Input key: " << endl;
                    find_key = InputInt("all");
                    root = RecDelByKey(root, find_key);
                    amount_keys--;
                    cin.ignore();
                }
                else
                {
                    cout << "Tree is empty!!!" << endl;
                }
            }
            break;

        case '3':
            if (root)
            {
                level = GetLevel(root);
                cout << "=======================" << endl;
                cout << "1 - Vertical tree\nelse - Horizontal tree\n";
                if ((_getch() == '1'))
                {
                    cout << "Ur level tree is: " << level << endl;
                    cout << "Func 1:\n";
                    View(root);
                    cout << "Func 2:\n";
                    ViewTree(root);
                }
                else
                {
                    cout << "Ur level tree is: " << level << endl;
                    ViewHor(root, level);
                }
                cout << "\nLeft-Root-Right: ";
                GoWay1(root);
                cout << endl;
                cout << "Root-Left-Right: ";
                GoWay2(root);
                cout << endl;
                cout << "Left-Right-Root: ";
                GoWay3(root);
                cout << endl;
            }
            else
            {
                cout << "Tree is empty!!!" << endl;
            }
            break;

        case '4':
            if(root)
            {
                cout << "Input key: " << endl;
                find_key = InputInt("all");
                cout << GetInfo(root, find_key) << endl;
                cin.ignore();
            }
            else
            {
                cout << "Tree is empty!!!" << endl;
            }
            break;

        case '5':
            if (root)
            {
                if(last_mem == 0)
                {
                    arr = new Tree*[amount_keys];
                    arr_i = new int[amount_keys];
                    last_mem = amount_keys;
                }
                if(amount_keys > last_mem)
                {
                    arr = WorkMemTree(arr, amount_keys, last_mem);
                }
                Go2(root, *&arr, 0);
                cout << endl;
                arr = SortArr(arr, amount_keys);
                BalanceTree(*&root, 0, amount_keys, arr);
                last_mem = amount_keys;
            }
            else
            {
                cout << "Tree is empty!!!" << endl;
            }
            break;

        case '6':
            if(root)
            {
                if(last_mem == 0)
                {
                    arr_i = new int[amount_keys];
                    arr = new Tree*[amount_keys];
                    last_mem = amount_keys;
                }
                if(amount_keys > last_mem)
                {
                    arr_i = WorkMemint(arr_i, amount_keys, last_mem);
                }
                Go2int(root, *&arr_i, 0);
                cout << endl;
                for(int i = 0; i < amount_keys; i++)
                {
                    ave += arr_i[i];
                }
                ave /= (double)amount_keys;
                cout << "Ave is: "  << ave << endl;
                n13_res = arr_i[0];
                for(int i = 0; i < amount_keys; i++)
                {
                    if (abs(abs(arr_i[i]) - ave) < abs(abs(n13_res) - ave) )
                    {
                        n13_res = arr_i[i];
                    }
                }
                cout << "Ur result: " << n13_res << endl;
                ave = n13_res = 0;
            }
            else
            {
                cout << "Tree is empty!!!" << endl;
            }
            break;

        case '7':
            cout << "Have a nice day!"<< endl;
            exit = true;
            // All mem will be cleared after program's end.
            break;
            
        default:
            cout << "Bad input..." << endl;
            break;
        }
    }
}