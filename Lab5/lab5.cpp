#include <iostream>
using namespace std;
#include "math.h"
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

struct Tree
{
    int key;
    string info;
    Tree *left, *right;
};

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

Tree *CreateTree()
{
    int key;
    string info;
    Tree *root = new Tree;
    cout << "Input key: " << endl;
    cin >> key;
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
    cout << level << endl;
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
        // NextLevelPrint(root, 0, i);
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
    cin >> key;
    cout << "Input info: " << endl;
    cin >> info;
    while(t)
    {
        if (t -> key == key)
        {
            cout << "Bad key..." << endl;
            cout << "Input key: " << endl;
            cin >> key;
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

int main()
{
    Tree *root = nullptr;
    bool exit = false;
    int find_key;
    while (!exit)
    {
        int n = 0;
        cout << "1 - Input values\n2 - Delete\n3 - View tree\n4 - Find info" << endl;
        switch (_getch())
        {
        case '1':
            cout << "How many values u want to add?" << endl;
            cin >> n;
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
            }
            else
            {
                if (root)
                {
                    cout << "Input key: " << endl;
                    cin >> find_key;
                    root = RecDelByKey(root, find_key);
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
                View(root);
            }
            else
            {
                cout << "Tree is empty!!!" << endl;
            }
            break;

        case '4':
            cout << "Input key: " << endl;
            cin >> find_key;
            cout << GetInfo(root, find_key) << endl;
            cin.ignore();
            break;

        default:
            break;
        }
    }
}