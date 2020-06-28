//
//  main.cpp
//  DS0
//
//  Created by Vincent on 3/12/20.
//  Copyright © 2020 Vincent. All rights reserved.
//

 // Sample code to perform I/O:
 
#include<iostream>
using namespace std;


int max(int a, int b) { return (a > b)? a : b; }

int knapSack(int w, int wt[], int cost[], int n)
{
    
    
    if (n == 0 || w == 0)
        return 0;
    
    
    //if (wt[n-1] > w)
    if(wt[n]>w)
        return knapSack(w, wt, cost, n-1);
    
    //else return max( cost[n-1] + knapSack(w-wt[n-1], wt, cost, n-1),knapSack(w, wt, cost, n-1) );
    else return max( knapSack( w-wt[n],wt,cost,n-1 ) + cost[n], knapSack(w,wt,cost,n-1));
}
int main()
{
    int n = 0;
    int cost[n] ;
    int wt[n] ;
    int w ;
    cin >> n >> w;
    for(int i = n; i > 0; i--){
        cin >> cost[i] >> wt[i];
    }
    cout<<knapSack(w, wt, cost, n);
    return 0;
}  

