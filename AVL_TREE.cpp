#include<iostream>
using namespace std;

class node
{
    public:
    int value;
    node* left;
    node* right;
    int height;
};

int GetHight(node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->height;
};

node* CreatNode(int value)
{
    node* root = new node();
    root->value = value;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;
    return root;
};

int GetBalance(node* n)
{
    if (n == NULL)
    {
        return 0;
    }
    return GetHight(n->left) - GetHight(n->right);
};

int max(int a , int b)
{
    return a > b ? a : b;
}

node* RightRotate(node* root)
{
    node* x = root->left;
    node* t2 = x->right;

    x->right = root;
    root->left = t2; 
    
    x->height = max(GetHight(x->right) , GetHight(x->left));
    root->height = max(GetHight(root->right) , GetHight(root->left));
    
    return x;
};

node* LeftRotate(node* root)
{
    node* y = root->right;
    node* t2 = y->left;

    y->left = root;
    root->right = t2;
    
    y->height = max(GetHight(y->right) , GetHight(y->left));
    root->height = max(GetHight(root->right) , GetHight(root->left));

    return y;
}

node* insert(node* root , int value)
{
    if(root == NULL)
    {
        return (CreatNode(value));
    }
    else if(value < root->value)
    {
        root->left = insert(root->left , value);
        return root;
    }
    else if(value > root->value)
    {
      root->right = insert(root->right , value);
      return root;
    }

    root->height = 1 + max(GetHight(root->left) , GetHight(root->right));

    int BalanceFactor = GetBalance(root);

    if (BalanceFactor > 1 && value < root->left->value)
    {
        return RightRotate(root);
    }
    else if (BalanceFactor < -1 && value > root->left->value)
    {
        return LeftRotate(root);
    }
    else if (BalanceFactor > 1 && value > root->left->value)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    else if (BalanceFactor < -1 && value < root->right->value)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
};

void PreOrder(node* root)
{
    if (root == NULL)
    {
      return;
    }

    cout << root->value << " | " << endl;

    PreOrder(root->left);
    PreOrder(root->right);
}

int main()
{
    node* root = NULL;
    root = insert(root , 21);
    root = insert(root , 22);
    root = insert(root , 23);
    root = insert(root , 24);
    root = insert(root , 25);

    PreOrder(root);

}
