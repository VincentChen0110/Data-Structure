#include <iostream>
#include <stdio.h>
#define INF 1000
#define max 26
using namespace std;

int graph[max][max];

void create_graph(int graph[max][max], int E)
{
    for(int i = 0; i<E ;i++)
    {
        char a,b;
        int w;
        cin >> a >> b >> w;
        graph[a-65][b-65] = w ;
    }
}

void print_path(int parent[], int j) 
{ 
    if (parent[j] == - 1) 
        return; 
    
    print_path(parent, parent[j]); 
    
    printf(" %c", j+65); 
} 
  
int print_solution(int dist[], int V, int parent[], int target, int source) 
{ 

    cout << dist[target-65]<<endl;
    printf("%c",source);
    print_path(parent, target-65); 
} 

int min_dist(int dist[], bool occupy[],int V) 
{ 
    int min = INF, index; 
  
    for (int i = 0; i < V; i++) 
        if (occupy[i] == false && dist[i] <= min) 
        {
            min = dist[i];
            index = i; 
        }
  
    return index; 
} 
 
void solve(int graph[max][max], int V,int target, int source) 
{ 
     
    int dist[V];  
    bool occupy[V]; 
    int parent[V]; 
    
    for (int i = 0; i < V; i++) 
    { 
        dist[i] = INF; 
        occupy[i] = false; 
    } 
    
    parent[source-65] = -1;  
    dist[source-65] = 0; 
    
    for (int i = 0; i < V - 1; i++) 
    { 
        int u = min_dist(dist, occupy, V); 
        occupy[u] = true; 
        for (int j = 0; j < V; j++) 
            if (!occupy[j] && graph[u][j] && dist[u]!=INF && dist[u] + graph[u][j] < dist[j]) 
            { 
                parent[j] = u; 
                dist[j] = dist[u] + graph[u][j]; 
            }  
    } 
    print_solution(dist, V, parent,target,source); 
} 
  
int main() 
{ 
    int V, E;
    cin >> V >> E;
    char source, target;
    cin >> source;
    cin >> target;
    create_graph(graph,E);
    solve(graph, V, target, source); 
} 