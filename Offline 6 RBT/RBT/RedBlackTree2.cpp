
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include<bits/stdc++.h>

#define RED 1
#define BLACK 0
#define INF 99999
#define Println(s) cout<<s<<endl;

using namespace std;

struct Node
{
    int item;
    int color;
    Node *left, *right, *p;

    Node(int item)
    {
        this->item = item;
        this->color = RED;
        left = right = p = NULL;
    }
};

class RedBlackTree
{
    Node *root;
    Node *Tnil;
protected:
    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void rbInsertFixup(Node *z);
    void inorderTraverse(Node *x);
    void postorderTraverse(Node *x);
    void preorderTraverse(Node *x);
    void levelorderTraverse(Node *x);
    void preorder_parenthesis(Node *x);
    void transplant(Node *u, Node *v);
    Node *search(int item);
    void rbDeleteFixup(Node *x);
    Node *treeMin(Node *x);
public:
    RedBlackTree()
    {
        Tnil = new Node(INF);
        Tnil->color = BLACK;
        root = Tnil;
    }
    void Insert(int item);
    void Delete(int item);
    bool Find(int item);

    void inorder(){
        inorderTraverse(root);
    }
    void postorder(){
        postorderTraverse(root);
    }
    void preorder(){
        preorderTraverse(root);
    }
    void levelorder(){
        levelorderTraverse(root);
    }
    void print_parenthesis_format(){
        preorder_parenthesis(root);
        cout<<endl;
    }
};

bool RedBlackTree::Find(int item)
{
    Node *x = search(item);
    if (x == Tnil) return false;
    else return true;
}

void RedBlackTree::leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if(y->left != Tnil)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if(x->p == Tnil)
    {
        root = y;
    }
    else if(x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

void RedBlackTree::rightRotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if(y->right != Tnil)
    {
        y->right->p = x;
    }
    y->p = x->p ;
    if(x->p == Tnil)
    {
        root = y;
    }
    else if(x->p->right == x)
    {
        x->p->right = y;
    }
    else
    {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;
}

void RedBlackTree::Insert(int item)
{
    Node *z = new Node(item);
    Node *x = root;
    Node *y = Tnil;

    while(x != Tnil )
    {
        y=x;
        if(z->item < x->item)
        {
            x = x->left;
        }
        else x = x->right;
    }
    z->p = y;
    if( y == Tnil)
    {
        root = z;
    }
    else if(z->item< y->item)
    {
        y->left = z;
    }
    else y->right = z;
    z->left = Tnil;
    z->right = Tnil;

    rbInsertFixup(z);
}

void RedBlackTree::rbInsertFixup(Node *z)
{
    Node *y;
    while(z->p->color == RED)
    {
        if(z->p == z->p->p->left)
        {
            y = z->p->p->right;
            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    leftRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(z->p->p);
            }
        }
        else
        {
            y = z->p->p->left;
            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z = z->p;
                    rightRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(z->p->p);
            }
        }
    }
    root ->color = BLACK;
}

void RedBlackTree::transplant(Node* u, Node* v)
{
    if(u->p == Tnil)
        this->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else u->p->right = v;
    v->p = u->p;

}

Node *RedBlackTree::treeMin(Node* x)
{
    while(x->left != Tnil)x = x->left;
    return x ;
}

Node *RedBlackTree::search(int item)
{
    Node *x;
    x = root;
    while(x->item != item && x != Tnil)
    {
        if(item > x->item)
            x = x->right;
        else
            x = x->left;
    }

    return x;

}

void RedBlackTree::Delete(int item)
{
    Node *z = search(item);
    Node *y = z;
    Node *x;
    int y_original_color = y->color;
    if (z->left == Tnil)
    {
        x = z->right;
        transplant(z,z->right);
    }
    else if (z->right == Tnil)
    {
        x = z->left;
        transplant(z,z->left);
    }
    else
    {
        y = treeMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->p == z)
        {
            x->p = y;
        }
        else
        {
            transplant(y,y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if(y_original_color == BLACK)
        rbDeleteFixup(x);
}

void RedBlackTree::rbDeleteFixup(Node* x)
{
    Node *w;
    while (x != root && x->color == BLACK) {
        if(x == x->p->left)
        {
            w = x->p->right;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                leftRotate(x->p);
                w = x->p->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->p);
                x = root;
            }
        }
        else
        {
            w = x->p->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                rightRotate(x->p);
                w = x->p->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->p);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::inorderTraverse(Node* x)
{
    if(x == Tnil)return;
    inorderTraverse(x->left);
    cout<<x->item<<"(";
    if(x->color == RED)
        cout<<"Red) ";
    else cout<<"Black) ";
    if(x->left == Tnil)
    {
        cout<<" left= NULL";
    }
    else
    {
        cout<<" left= "<<x->left->item;
    }
    if(x->right == Tnil)
    {
        cout<<" right=NULL";
    }
    else
    {
        cout<<" right= "<<x->right->item;
    }
    cout<<endl;
    inorderTraverse(x->right);
}

void RedBlackTree::postorderTraverse(Node* x)
{
    if(x == Tnil)return;
    postorderTraverse(x->left);
    postorderTraverse(x->right);
    cout<<x->item<<"(";
    if(x->color == RED)
        cout<<"Red) ";
    else cout<<"Black) ";
}

void RedBlackTree::preorderTraverse(Node* x)
{
    if(x == Tnil)return;
    cout<<x->item<<"(";
    if(x->color == RED)
        cout<<"Red) ";
    else cout<<"Black) ";
    if(x->left == Tnil)
    {
        cout<<" left= NULL";
    }
    else
    {
        cout<<" left= "<<x->left->item;
    }
    if(x->right == Tnil)
    {
        cout<<" right=NULL";
    }
    else
    {
        cout<<" right= "<<x->right->item;
    }
    cout<<endl;
    preorderTraverse(x->left);
    preorderTraverse(x->right);
}

void RedBlackTree::preorder_parenthesis(Node *x)
{
    if(x == Tnil)return;
    cout<<x->item<<":";
    if(x->color == RED)
        cout<<"r";
    else cout<<"b";

    if (x->left == Tnil && x->right == Tnil)
    {
        return;
    }
    cout<<"(";
    preorder_parenthesis(x->left);
    cout<<")";
    cout<<"(";
    preorder_parenthesis(x->right);
    cout<<")";
}

void RedBlackTree::levelorderTraverse(Node* x)
{
    if (x == Tnil)
            return;

        std::queue<Node *> q;
        q.push(x);

        while (!q.empty())
        {
            Node *temp = q.front();
            cout << temp->item << "  ";
            q.pop();

            if (temp->left != Tnil)
                q.push(temp->left);

            if (temp->right != Tnil)
                q.push(temp->right);
        }
}

int main()
{
    RedBlackTree rb;
    ifstream myfile("input3.txt");

    int num;
    char cmd;
    if(myfile.is_open())
    {
        while(myfile>>cmd>>num)
        {
            if (cmd == 'F')
            {
                if(rb.Find(num)) { Println("True"); }
                else {Println("False");}
            }
            else if (cmd == 'I')
            {
                rb.Insert(num);
                rb.print_parenthesis_format();
            }
            else if (cmd == 'D')
            {
                rb.Delete(num);
                rb.print_parenthesis_format();
            }
            else
            {
                Println("Unrecognizable Command!");
            }
        }

    }
    else Println("unable to open file");
}
