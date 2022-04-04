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

int NextLevel(Tree* root, int level_now)
{
    Tree* t = root;
    int left = 0, right = 0;
    level_now++;
    if(t -> left)
    {
        t = t -> left;
        left = NextLevel(t, level_now);
        t = root;
    }
    if(t -> right)
    {
        t = t -> right;
        right = NextLevel(t, level_now);
    }
    if (left == 0 and right == 0)
    {
        return --level_now;
    }
    if(left > right)
    {
        return left;
    }
    return right;
}
void PrintValue(Tree* root, int level_now)
{
    const int str_len = 72;
    int left_num, right_num, rool = 72/(pow(2,level_now + 1)) + 5;
    Tree* t = root;
    for(int i = 0; i < rool; i++)
    {
        cout << " ";
    }
    if(t -> left)
    {
        t = t -> left;
        cout << t -> key;
    }
    else
    {
        cout << "pop";
    }
    t = root;
    for(int i = 0; i < rool; i++)
    {
        cout << "-";
    }
    if(t -> right)
    {
        t = t -> right;
        cout << t -> key;
    }
    else
    {
        cout << "pop";
    }
    // for(int i = 0; i < rool/6; i++)
    // {
    //     cout << " ";
    // }
}

int NextLevelPrint(Tree* root, int level_now, int level)
{
    int rool = 72/pow(2,level_now) + 4 ;
    Tree* t = root;
    level_now++;
    if (level_now == level)
    {
        if (t -> left or t -> right)
        {
            PrintValue(t, level_now);
        }
        else
        {
            for(int i = 0; i < rool-1; i++)
            {
                cout << " ";
            }
            cout << "!" ;
        }
        return 1;
    }
    else
    {
        if(t -> left)
        {
            t = t -> left;
            NextLevelPrint(t, level_now, level);
            t = root;
        }
        else
        {
            for(int i = 0; i < rool-1; i++)
            {
                cout << " ";
            }
            cout << "!" ;
        }
        if(t -> right)
        {
            t = t -> right;
            NextLevelPrint(t, level_now, level);
        }
    }
}

int GetLevel(Tree* root)
{
    int left = 0, right = 0;
    if (root -> left)
    {
        left = NextLevel(root -> left, 1);
    }
    if (root -> right)
    {
        right = NextLevel(root -> right, 1);
    }
    if (left > right)
    {
        return left;
    }
    else
    {
        return right;
    }
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
    int level = GetLevel(root);
    cout << level << endl;
    for (int i = 0; i < 35; i++)
    {
        cout << " ";
    }
    cout << root -> key << endl;
    for(int i = 1; i <= level; i++)
    {
        NextLevelPrint(root, 0, i);
        cout << endl;
    }
}

void AddValues(Tree *root, int n)
{
    Tree *t = root, *o;
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
    Tree *k = new Tree;
    k -> info = info;
    k -> key = key;
    if (key > o -> key)
    {
        o -> right = k;
    }
    else
    {
        o -> left = k;
    }
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
    while (!exit)
    {
        int n = 0;
        cout << "1 - Input values\n2 - Delete element\n3 - View tree" << endl;
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
            AddValues(root, n);
            break;
        case '3':
            // cout << GetLevel(root) << endl;
            View(root);
        default:
            break;
        }
        cin.ignore();
    }
}