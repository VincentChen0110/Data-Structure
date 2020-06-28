#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define max 100
using namespace std;

bool maze[max][max];



int N1, N3, N4, w, h, difficulty, cnt;


struct data
{
    int serial, N1, N3, N4, difficulty;
};

void reset()
{
    N1=0, N3=0, N4=0, difficulty =0;
    for(int i =0;i<h;i++){
        for(int j =0 ;j<w; j++)
        {
            maze[i][j] = 0;
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




void find_n1n2()
{
    for(int i=0; i<h ;i++){
        for(int j =0; j<w; j++)
        {
            if(maze[i][j]==0)
            {
                if((maze[i-1][j]&&maze[i+1][j]&&maze[i][j+1])||(maze[i][j-1]&&maze[i+1][j]&&maze[i-1][j])
                    ||(maze[i][j-1]&&maze[i-1][j]&&maze[i][j+1])||(maze[i][j-1]&&maze[i+1][j]&&maze[i][j+1]))
                    {
                        N1+=1;
                    }
                if(maze[i-1][j]||maze[i+1][j]||maze[i][j+1]||maze[i][j-1])
                {
                    if((!maze[i-1][j]&&!maze[i+1][j]&&!maze[i][j+1])||(!maze[i][j-1]&&!maze[i+1][j]&&!maze[i-1][j])
                    ||(!maze[i][j-1]&&!maze[i-1][j]&&!maze[i][j+1])||(!maze[i][j-1]&&!maze[i+1][j]&&!maze[i][j+1]))
                        {
                            N3+=1;
                        }   
                }
                if(!maze[i-1][j]&&!maze[i+1][j]&&!maze[i][j+1]&&!maze[i][j-1])
                {
                    N4+=1;
                }    
            }
        }
    }
}

int compare(const void *s1, const void *s2)
{
    data *e1 = (data *)s1;
    data *e2 = (data *)s2;
    if((e1->difficulty - e2->difficulty)!=0)
        return(e1->difficulty - e2->difficulty);
    if((e1->N4 - e2->N4)!=0)
        return(e1->N4 - e2->N4);
    if((e1->N3 - e2->N3)!=0)
        return(e1->N3 - e2->N3);
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
        //solvemaze(1,0,h-2,w-1);
        find_n1n2();
        nData[i].N1 = N1;
        nData[i].N3 = N3; 
        nData[i].N4 = N4; 
        nData[i].difficulty = (N1+N3+N4);
        /*if(w==3 && h==3)
        {
            nData[i].N1 = 0;
            nData[i].N2 = 0; 
            nData[i].L1 = 2; 
            nData[i].L2 = 0; 
            nData[i].difficulty = 0;
        }*/
    }
    qsort(nData, N, sizeof(struct data), compare);
    bool flag = true;
    for (int i = N-1; i >=0; i--)
    {
        if(flag)
        {
            //printf("%d: %d %d %d %d %d\n", nData[i].serial, nData[i].difficulty, nData[i].N4,nData[i].N3,nData[i].N1);
            cout <<nData[i].serial<<": "<<nData[i].difficulty<<" "<<nData[i].N4<<" "<<nData[i].N3<<" "<<nData[i].N1<<endl;
        }
        else
        {
            cout << endl;
            //printf("%d: %d %d %d %d %d", nData[i].serial, nData[i].difficulty, nData[i].N4,nData[i].N3,nData[i].N1);
            cout <<nData[i].serial<<": "<<nData[i].difficulty<<" "<<nData[i].N4<<" "<<nData[i].N3<<" "<<nData[i].N1;
        }
    }
    return 0;
}



