#include <iostream>
#include <string.h>
using namespace std;

bool check = true;
int check_order = 0;

struct Node
{
    char key;
    struct Node* left, *right;
};


void reset()
{
    check = true;
    check_order = 0;
}

int search(char arr[], int strt, int end, int value)
{
    for (int i = strt; i <= end; i++)
        if (arr[i] == value)
            return i;
    return -1;
}

Node* newNode(int key)
{
    Node *node = new Node;
    node->key = key;
    node->left = node->right = NULL;
    return (node);
}


Node* buildTree(char in[], char pre[], int start, int end)
{
    if (start > end)
        return NULL;
    
    static int preindex = 0;
    
    Node* root = newNode(pre[preindex++]);
    if(start == end )
        return root;
    int inIndex = search(in, start, end, root->key);
    root->left = buildTree(in, pre, start, inIndex-1);
    root->right = buildTree(in, pre, inIndex+1, end);
    
    return root;
}


void permutation(char* PreOrder,char* Inorder,int n){
    bool flag = true;
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n; j++)
        {
            if(Inorder[j]==PreOrder[i])
                if(flag)
                {
                    cout <<" "<< j;
                    flag = false;
                    
                }
                else
                {
                    cout << "-"<< j;
                }
            /*if(Inorder[i]==LevelOrder[j])
                inorder[i]= j;*/
        }
    }
}
void print_inorder(Node* root)
{
    if(root == NULL)
        return ;
    print_inorder(root->left);
    cout << root->key << " ";
    print_inorder(root->right);
}
void solution(char* PreOrder,char* InOrder){
    cout << PreOrder<<endl;
    cout << InOrder ;

    int n = strlen(PreOrder);
    //reset();
    permutation(PreOrder,InOrder,n);
    cout << " ";
    Node* root = buildTree(InOrder, PreOrder, 0, n - 1);
    print_inorder(root);
    /*if(!check)
        cout<< " No";
    else
        cout<< " Yes";*/
    cout << endl;
    
}
int main()
{
    int N;
    cin >> N;
    char PreOrder[1000], InOrder[1000];
    cout << N << "\n";
    while(N--)
    {
        cin >> PreOrder;
        cin >> InOrder;
        solution(PreOrder, InOrder);
    }
}
