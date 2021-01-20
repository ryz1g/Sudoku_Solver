#include<iostream>
#include<cmath>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

//Function to check whether a state of Sudoku is valid
int isValidSudoku(const vector<vector<char>> &A) {
    unordered_map<char,int> mp;
    for(vector<char> s:A) {
        for(int i=0;i<9;i++) {
            if(s[i]=='.') continue;
            if(mp.count(s[i])!=0) {
                //cout<<"A|";
                return 0;
            }
            mp[s[i]]++;
        }
        mp.clear();
    }
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            if(A[j][i]=='.') continue;
            if(mp.count(A[j][i])!=0) {
                //cout<<"B|";
                return 0;
            }
            mp[A[j][i]]++;
        }
        mp.clear();
    }
    vector<vector<int>> vv={{0,0},{0,3},{0,6},{3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};
    for(auto v:vv) {
        for(int i=v[0];i<v[0]+3;i++) {
            for(int j=v[1];j<v[1]+3;j++) {
                if(A[i][j]=='.') continue;
                if(mp.count(A[i][j])!=0) {
                    //cout<<"C|";
                    return 0;
                }
                mp[A[i][j]]++;
            }
        }
        mp.clear();
    }
    return 1;
}

//Recursive function
void recur(vector<vector<int>> &sp, int depth, int blank, vector<vector<char>> A, vector<vector<char>> &ans) {
    if(!ans.empty()) return;
    if(depth==blank) {
        ans=A;
        return;
    }
    else if(depth<blank) {
        int c1=sp[depth][0];int c2=sp[depth][1];
        for(int i=1;i<=9;i++) {
            A[c1][c2]=(char)('0'+i);
            if(isValidSudoku(A)==0) continue;
            recur(sp, depth+1, blank, A, ans);
        }
    }
}

//Function to be called for solving a Sudoku state
void solveSudoku(vector<vector<char> > &A) {
    int blank=0;
    vector<vector<int>> sp;
    vector<vector<char>> ans;
    for(int j=0;j<9;j++) {
        for(int i=0;i<9;i++) {
            if(A[j][i]=='.') {
                blank++;
                sp.push_back({j,i});
            }
        }
    }
    recur(sp, 0, blank, A, ans);
    A=ans;
}

int main() {
    //Give inputs row wise, use . char in place of blanks
    /* Example                          
        5 3  |  7  |                    
        6    |1 9 5|   
          9 8|     |  6 
        -----------------
        8    |  6  |    3
        4    |8   3|    1
        7    |  2  |    6
        -----------------
          6  |     |2 8  
             |4 1 9|    5
             |  8  |  7 9 
        Will be inputted as
    */
    vector<vector<char>> A={{'5','3','.','.','7','.','.','.','.'}, 
                            {'6','.','.','1','9','5','.','.','.'}, 
                            {'.','9','8','.','.','.','.','6','.'}, 
                            {'8','.','.','.','6','.','.','.','3'}, 
                            {'4','.','.','8','.','3','.','.','1'}, 
                            {'7','.','.','.','2','.','.','.','6'}, 
                            {'.','6','.','.','.','.','2','8','.'}, 
                            {'.','.','.','4','1','9','.','.','5'}, 
                            {'.','.','.','.','8','.','.','7','9'}};
    solveSudoku(A);
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            cout<<A[i][j]<<" ";
            if(j==2 || j==5) cout<<"| ";
        }
        cout <<endl;
        if(i==2 || i==5) cout<<"---------------------"<<endl;
    }
    return 0;
}
