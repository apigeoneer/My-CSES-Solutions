/**
 * 1≤n,m≤1000
 * 
 * Input:
 * 5 8
 * ########
 * #..#...#
 * ####.#.#
 * #..#...#
 * ########
 *
 * Output:
 * 3
 */
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<pair<int, int>>  moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool visited[1002][1002];
int rooms = 0;


/**
 * check if a cell is valid
 */
bool isValid(int x, int y){
    if(x<0 || x>=n || y<0 || y>=m)
        return false;
    else if(visited[x][y])
        return false;
    return true;
}

void dfs(int x, int y){
    visited[x][y] = true;
    for(pair<int, int> p: moves){
        int xadj = x + p.first;
        int yadj = y + p.second;

        if(isValid(xadj, yadj)){
            dfs(xadj, yadj);
        }
    }
}

void solve(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(!visited[i][j]){
                dfs(i, j);
                rooms++;
            }
        }
    }
}

int main()
{
    cin >> n >> m;

    int s, d;
    char x;

    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> x;
            if (x == '#'){
                visited[i][j] = true;
            }
            else{
                visited[i][j] = false;
            }
             
        }
    }

    solve();
    cout << rooms << endl;

    return 0;
}