#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MAX_PUZZLE 10
#define MAX 10
typedef struct _puzzle{
    int puzzle_matrix[MAX_PUZZLE][MAX_PUZZLE];
    int row,col;
}puzzle;

int matrix[MAX][MAX];
int m_col, m_row;
int num_of_puzzle;
int ans[MAX][MAX];
int origin[MAX][MAX];
bool check = false;

puzzle* puzzle_list;

puzzle create_puzzle(int x,int y){
    char temp;
    puzzle new_puzzle;
    
    new_puzzle.row = y;
    new_puzzle.col = x;
    for(int i=0; i<y; i++){
        for(int j =0; j<x; j++){
            temp = getchar();
            new_puzzle.puzzle_matrix[i][j]= (temp =='O')? 1 :0;
        }
        getchar();
    }
    return new_puzzle;
}

puzzle rotate_puzzle(puzzle origin){
    puzzle new_puzzle;
    
    new_puzzle.col = origin.row;
    new_puzzle.row = origin.col;
    
    for(int i=0;i<origin.row;i++){
        for(int j=0;j<origin.col;j++){
            new_puzzle.puzzle_matrix[j][new_puzzle.col-1-i] = origin.puzzle_matrix[i][j];
        }
    }
    
    
    return new_puzzle;
    
}
puzzle flip_puzzle(puzzle origin){
    puzzle new_puzzle;
    
    new_puzzle.col = origin.col;
    new_puzzle.row = origin.row;
    for(int i=0; i<origin.row;i++){
        for(int j =0; j<origin.col; j++){
            new_puzzle.puzzle_matrix[i][j] = origin.puzzle_matrix[i][origin.col-1-j];
        }
    }
    return new_puzzle;
}

void reset(){
    for (int i=0;i<m_row;i++){
        for(int j=0;j<m_col;j++){
            matrix[i][j] = 0;
        }
    }
    check = false;
}

void input_map(){
    char temp;
    for (int i=0;i<m_row;i++){
        for(int j=0;j<m_col;j++){
            temp = getchar();
            matrix[i][j] = (temp=='O')?1:0;
            
        }
        getchar();
    }
    
}

bool valid(puzzle P, int x, int y){
    if(x+P.row > m_row || y +P.col> m_col)
        return false;
    for(int i=0; i<P.row;i++){
        for(int j=0; j<P.col;j++){
            if(P.puzzle_matrix[i][j]!=0 && matrix[x+i][y+j] !=0 )
                return false;
        }
    }
    return true;
}

void fill_puzzle(puzzle P, int x, int y, int index){
    for(int i =0; i<P.row;i++){
        for(int j=0; j<P.col; j++){
            if(P.puzzle_matrix[i][j])
                matrix[x+i][y+j] = index+1;
        }
    }
}
void remove_puzzle(puzzle P, int x, int y){
    for(int i =0; i<P.row;i++){
        for(int j=0; j<P.col; j++){
            if(P.puzzle_matrix[i][j])
                matrix[x+i][y+j] = 0;
        }
    }
}
void show_matrix(){
    cout << "\n";
    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_col;j++){
            cout << matrix[i][j];
        }
        printf("\n");
    }
}
void check_matrix(){
    bool check1 = true;
    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_col;j++){
            if (matrix[i][j]==0)
                check1 = false;
        }
    }
    if(check1 == true)
        for(int i=0;i<m_row;i++){
             for(int j=0;j<m_col;j++){
                ans[i][j] = matrix[i][j];
             }
        }
}
void solve(int index){
    if(check || index == num_of_puzzle){
        check = true;
        for(int i=0;i<m_row;i++){
            for(int j=0;j<m_col;j++){
                ans[i][j] = matrix[i][j];
            }
        }
        return ;
    }
    puzzle cur_puzzle = puzzle_list[index];
    for(int i=0; i<m_row; i++){
        for(int j=0; j< m_col; j++){
            for(int k =0; k<4; k++){
                for(int m=0; m<2; m++){
                    if(valid(cur_puzzle,i,j)){
                        fill_puzzle(cur_puzzle,i,j,index);
                        solve(index+1);
                        remove_puzzle(cur_puzzle,i,j);
                        
                    }
                    cur_puzzle = flip_puzzle(cur_puzzle);
                }
                cur_puzzle = rotate_puzzle(cur_puzzle);
            }
        }
    }
}
void print_ans(){
    for(int i=0; i<m_row; i++){
        for(int j = 0; j< m_col; j++){
             if (ans[i][j] == origin[i][j])
                cout << 0;
             else
                cout << ans[i][j];
             }
             cout << "\n";
        }
}
void save_origin(){
    for(int i=0; i<m_row; i++){
        for(int j = 0; j< m_col; j++){
             origin[i][j] = matrix[i][j];
        }
    }
}

int main()
{
    int x,y;
    cin >> num_of_puzzle;
    puzzle_list = (puzzle*)malloc(num_of_puzzle* sizeof(puzzle));
    for(int i=0; i<num_of_puzzle;i++){
        cin >> x >> y;
        getchar();
        puzzle_list[i]= create_puzzle(x,y);
    }
    int N;
    cin >> N;
    while(N--){
        cin >> m_col >> m_row ;
        getchar();
        reset();
        input_map();
        save_origin();
        //show_matrix();
        solve(0);
        (check)?cout<<"Yes\n":cout << "No\n";
        if (check==true)
            print_ans();
    }
    return 0;
}
