#include<iostream>
#include <string.h>
using namespace std;


bool check = true;
int check_order = 0;


struct Node
{
    char key;
    struct Node* left, *right;
};


void checkGivenLevel(Node* root, int level, char LevelOrder[]);  
int height(Node* node); 
void checkLevelOrder(Node* root,int n ,char LevelOrder[]);

void reset()
{
    check = true;
    check_order = 0;
}


int search(char arr[],int start, int end, int value){
    for (int i = start; i <= end; i++) 
		if (arr[i] == value) 
			return i; 
	return -1; 
}

char *extract(char in[], char level[], int m, int n) 
{ 
	char *newlevel = new char[m], j = 0; 
	for (int i = 0; i < n; i++) 
		if (search(in, 0, m-1, level[i]) != -1) 
			newlevel[j] = level[i], j++;
	return newlevel; 
} 

Node* newNode(int key) { 
	Node *node = new Node; 
	node->key = key; 
	node->left = node->right = NULL; 
	return (node); 
} 


Node* buildTree(char in[], char level[], int inStrt, int inEnd, int n) { 
	if (inStrt > inEnd) 
		return NULL; 
	Node *root = newNode(level[0]); 
	if (inStrt == inEnd) 
		return root; 
	if (root==NULL)
	    return root;
	int inIndex = search(in, inStrt, inEnd, root->key); 
	char *llevel = extract(in, level, inIndex, n); 
	char *rlevel = extract(in + inIndex + 1, level, n-inIndex-1, n); 
	root->left = buildTree(in, llevel, inStrt, inIndex-1, n); 
	root->right = buildTree(in, rlevel, inIndex+1, inEnd, n); 
	delete [] llevel; 
	delete [] rlevel; 
	return root; 
} 

int height(Node* root){  
    if (root == NULL)  
        return 0;  
    else
    {  
        int lheight = height(root->left);  
        int rheight = height(root->right);  
        if (lheight > rheight)  
            return(lheight + 1);  
        else 
            return(rheight + 1);  
    }  
}

void checkLevelOrder(Node* root,int n ,char LevelOrder[])  
{   
    int h = height(root);  
    for (int i = 1; i <= h; i++)
        checkGivenLevel(root, i, LevelOrder);  
}  
  

void checkGivenLevel(Node* root, int level, char LevelOrder[])  
{   
    if (root == NULL)  
        return;  
    if (level == 1)
    {
        if (LevelOrder[check_order]==root->key)
        {
            check_order++;
            //cout << root->key ;
        }
        else
            check = false;
    }
    else if (level > 1)  
    {  
        checkGivenLevel(root->left, level-1,LevelOrder);  
        checkGivenLevel(root->right, level-1,LevelOrder);  
    }  
}  

void permutation(char* LevelOrder,char* Inorder,int n){
    bool flag = true;   
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n; j++)
        {
            if(Inorder[j]==LevelOrder[i])
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


bool solution(char* LevelOrder,char* InOrder){
    //cout << LevelOrder << endl;
    //cout << InOrder;
    int n = strlen(LevelOrder); 
    reset();
    //permutation(LevelOrder,InOrder,n);
    Node *root = buildTree(InOrder, LevelOrder, 0, n - 1, n);
    checkLevelOrder(root,n,LevelOrder);  
    if(!check) 
        return false;
        //cout<< "No";
    else
        return true;

    
}

int main(){
    int N,heap;
    cin >> heap;
    int* heap_array = new int[heap];
    for(int i =0; i<heap;i++){
        cin>>heap_array[i];
    }
    cin >> N;
    string* result = new string[N];

    char LevelOrder[1000], InOrder[1000];
    //cout << N << "\n";
    for(int i=0;i<N;i++){
        cin >> LevelOrder;
        cin >> InOrder;
        
        if(solution(LevelOrder, InOrder)==true){
            result[i] = "Yes";
        }else{
            result[i] = "No";
        }
    }

    for(int i=0;i<N;i++){
        cout << result[i] << endl;
    }

    return 0;
}