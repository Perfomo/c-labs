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

Tree* WhatPref(int level_now, Tree* root, int& new_lev)
{
    int amount = level_now;
    Tree* t = root, *trash;
    while(level_now>0)
    {
        for (int i = 0; i < level_now; i++)
        {
            if (t -> left)
            {
                t = t -> left;
            }
            else
            {
                if ( t -> right and i != level_now-1)
                {
                    t = t -> right;
                }
                else
                {
                    if(trash -> right != t)
                    {
                        t =  trash -> right;
                        new_lev = level_now - 1;
                        return t;
                    }
                    else
                    {
                        i = level_now;
                    }
                }
            }
            trash = t;  
        }
        if ( level_now == 0)
        {
            new_lev = 0;
            return root;
        }
        level_now--;
    }
    new_lev = 0;
    return root;
}


int WhatLevel(Tree* root)
{
    Tree* t = root, *stop, *trash, *new_t;
    int level = 0, level_now = 0, kol = 0;
    while(kol < 2)
    {
        if (t -> left)
        {
            t = t -> left;
            ++level_now;
        }
        else
        {
            if ( t -> right)
            {
                t = t -> right;
                ++level_now;
            }
            else
            {
                stop = trash;
                level_now--;
                if(stop -> right and stop -> right != t)
                {
                    t = stop -> right;
                }
                else
                {
                    t = WhatPref(level_now, root, level_now);
                    if (t == root)
                    {
                        t = root -> right;
                        level_now++;
                        kol++;
                    }
                }
            }
        }
        trash = t;
        if ( level_now > level)
        {
            level = level_now;
        }
    }
    return level;
}


Tree* LastStop(Tree* root)
{
    Tree* t = root;
    while(t)
    {
        if (t -> left)
        {
            t = t -> left;
        }
    }
}

int RecSearch(int level_now, int level, Tree* root)
{
    Tree* t = root;

    for(int i = 0; i <= level_now; i++)
    {
        if(t -> left)
        {
            t = t -> left;
        }
        else
        {
            if(t -> right)
            {
                t = t -> right;
            }
            if(level_now == level)
            {
                return t -> key;
            }
        }
    }
    if(t->right)
    {
        t = t -> right;
        return RecSearch(level_now+1, level, root);
    }
    else
    {
        return RecSearch(level_now-1, level, root);
    }
     
}

int* FindOnLevel(Tree* root, int level)
{
    int ready = 0, level_of_view = 0, amount = pow(2,level), stop = 0;
    Tree* t = root;
    bool add = true;
    int* level_nums = new int(amount);
    // while (ready != amount)
    // {
        // for(int i = 0; i < level; i++)
        // {
        //     if(t -> left)
        //     {
        //         t = t -> left;
        //     }
        //     else
        //     {
        //         if(t -> right)
        //         {
        //             t = t -> right;
        //         }
        //         else
        //         {
        //             if(i == level - 1)
        //             {
        //                 level_nums[ready] = t -> key;
        //                 ready++;
        //             }
        //             else
        //             {
        //                 for (int i = 0; i <= amount; i++)
        //                 level_nums[i] = RecSearch(i, level, root);
        //             }
        //         }
        //     }
        // }      
    // }
    // for (int i = 0; i <= amount; i++)
    // {
    //     level_nums[i] = RecSearch(4, level, root);

    // }
    // return level_nums;
}

void view(Tree *root, int level)
{
    Tree *t = root, *left = root -> left, *right = root -> right;
    int line_size = 31, i = 0;
    int* mas = FindOnLevel(root, 4);
    while(i <= level)
    {
        cout<< mas[i] << endl;
    }
}

string rec_view(Tree *root)
{
    int line = 31;
    Tree* left = root -> left, *right = root -> right;
    string str1 = "", str2 = "";
    if(left)
    {
        str1 = rec_view(left);
    }
    if (right)
    {
        str2 = rec_view(right);
    }
    cout << str1 + str2 << endl;
    return "";
}

// void ur_view(Tree *root)
// {
//     string level;
//     int level;
//     Tree* left, *riht;

// }



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
            cout << WhatLevel(root) << endl;
        default:
            break;
        }
        cin.ignore();
    }
}