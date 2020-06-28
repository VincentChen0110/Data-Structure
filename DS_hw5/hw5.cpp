#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define max 500
using namespace std;

bool maze[max][max];
bool sol[max][max];
int visited[max][max];
int deadend_sol[max][max];
int deadend_visited = 0;
int L2_arr[max];


int N1, N2, L1, w, h, difficulty, cnt;
int L2;

struct data
{
    int serial, N1, N2, L1, difficulty;
    int L2;
};

void deadend_reset()
{
    deadend_visited=0;
    for(int i = 0; i < h ;i++){
        for(int j = 0; j < w; j++)
            deadend_sol[i][j] = 0;
    }
}

void reset()
{
    N1=0, N2=0, L1=0, L2=0, cnt=0, difficulty =0;
    for(int i =0;i<h;i++){
        for(int j =0 ;j<w; j++)
        {
            maze[i][j] = 0;
            sol[i][j] = 0;
            visited[i][j] = 0;
        }
    }
}

void input_maze()
{   
    char temp;
    for(int i=0; i < h; i++){
        for(int j = 0; j < w ;j++){
            temp = getchar();
            //(temp=='N')? maze[i][j]=0:maze[i][j]=1;
            if(temp == 'N')
                maze[i][j] = 1;
            else
                maze[i][j] = 0;
        }
        getchar(); 
    }
}

void printsolution() 
{ 
    for (int i = 0; i < h; i++) { 
        for (int j = 0; j < w; j++) 
            printf(" %d ", visited[i][j]); 
        printf("\n"); 
    } 
} 

void solve_L1()
{
    for(int i =0; i < h ; i++){
        for (int j = 0 ; j < w; j++){
            L1 += sol[i][j];
        }
    }
    L1 -= 1 ;
}

int solvemaze(int r, int c, int tr,int tc)
{
    if((r==tr) && (c==tc))
    {
        sol[r][c] = 1;
        return 1;
    }
    
    if(r>=0 && c>=0 && r<h && c<w && sol[r][c] == 0 && maze[r][c] == 0)
    {
        sol[r][c] = 1;
        //going up
        if(solvemaze(r-1, c,tr,tc))
        {
            return 1;
        }
        //going right
        if(solvemaze(r, c+1,tr,tc))
        {
            return 1;
        }
        //going left
        if(solvemaze(r, c-1,tr,tc))
        {
            return 1;
        }
        //going down
        if(solvemaze(r+1, c,tr,tc))
        {
            return 1;
        }
        //back track
            
        sol[r][c] = 0;
        
        return 0;
    }
    return 0;

}
int solve_deadend(int r, int c)
{
    if(visited[r][c] == 2)
    {
        deadend_sol[r][c] = 1;
        return 1;
    }
    
    if(r>=0 && c>=0 && r<h && c<w && deadend_sol[r][c] == 0 && maze[r][c] == 0 )
    {
        deadend_sol[r][c] = 1;
        deadend_visited += 1;
        //going up
        if(solve_deadend(r-1, c))
        {
            return 1;
        }
        //going right
        if(solve_deadend(r, c+1))
        {
            return 1;
        }
        //going left
        if(solve_deadend(r, c-1))
        {
            return 1;
        }
        //going down
        if(solve_deadend(r+1, c))
        {
            return 1;
        }
        //back track
            
        deadend_sol[r][c] = 0;
        deadend_visited -= 1;
        return 0;
    }
    return 0;

}
void find_n1n2()
{
    for(int i =0; i<h ;i++){
        for(int j=0; j<w; j++){
            visited[i][j] = 2*sol[i][j]+maze[i][j];
        }
    }
    for(int i=0; i<h ;i++){
        for(int j =0; j<w; j++)
        {
            if(maze[i][j]==0)
            {
                if((maze[i-1][j]&&maze[i+1][j]&&maze[i][j+1])||(maze[i][j-1]&&maze[i+1][j]&&maze[i-1][j])
                    ||(maze[i][j-1]&&maze[i-1][j]&&maze[i][j+1])||(maze[i][j-1]&&maze[i+1][j]&&maze[i][j+1]))
                    {
                        N2+=1;
                        solve_deadend(i,j);
                        L2_arr[cnt] = deadend_visited;
                        cnt++;
                        deadend_reset();
                    }
            }
        }
    }
    for (int i=0; i<h;i++){
        for(int j=0; j<w; j++){
            if(visited[i][j]==2)
            {
                if(visited[i][j-1]==0)
                    N1 += 1;
                if(visited[i][j+1]==0)
                    N1 += 1;
                if(visited[i-1][j]==0)
                    N1 += 1;
                if(visited[i+1][j]==0)
                    N1 += 1;
            }
        }
    }
    N1 -= 2;
}

int compare(const void *s1, const void *s2)
{
    data *e1 = (data *)s1;
    data *e2 = (data *)s2;
    if((e1->difficulty - e2->difficulty)!=0)
        return(e1->difficulty - e2->difficulty);
    if((e1->N1 - e2->N1)!=0)
        return(e1->N1 - e2->N1);
    if((e1->N2 - e2->N2)!=0)
        return(e1->N2 - e2->N2);
    if((e1->L1 - e2->L1)!=0)
        return(e1->L1 - e2->L1);
    if((e1->L2 - e2->L2)!=0)
        return(e1->L2 - e2->L2);
    if((e1->serial - e2->serial)!=0)
        return(e1->serial - e2->serial);
}

int main()
{
    int N;
    cin >> N;
    data *nData = new data[N]; 
    for(int i=0;i<N;i++)
    {
        reset();
        int n;
        cin >> n;
        nData[i].serial = n;
        cin >> w >> h;
        getchar();
        input_maze();
        solvemaze(1,0,h-2,w-1);
        find_n1n2();
        solve_L1();
        sort(L2_arr,L2_arr + N2);
        if(L2_arr == NULL) L2 = 0;
        if(N2 % 2 != 0) 
            L2 = L2_arr[N2/2];
        else
            L2= ((L2_arr[((N2+1)/2)] + L2_arr[(((N2+1)/2)-1)])/2);
        nData[i].N1 = N1;
        nData[i].N2 = N2; 
        nData[i].L1 = L1; 
        nData[i].L2 = L2; 
        nData[i].difficulty = ((N1+N2)*(L1+L2));
        if(w==3 && h==3)
        {
            nData[i].N1 = 0;
            nData[i].N2 = 0; 
            nData[i].L1 = 2; 
            nData[i].L2 = 0; 
            nData[i].difficulty = 0;
        }
    }
    qsort(nData, N, sizeof(struct data), compare);
    bool flag = true;
    for (int i = 0; i < N; i++)
    {
        if(flag)
            printf("%d\n%d %d %d %d %d\n", nData[i].serial, nData[i].difficulty, nData[i].N1,nData[i].N2,nData[i].L1,nData[i].L2);
        else
        {
            cout << endl;
            printf("%d\n%d %d %d %d %d", nData[i].serial, nData[i].difficulty, nData[i].N1,nData[i].N2,nData[i].L1,nData[i].L2);
        }
    }
    return 0;
}



