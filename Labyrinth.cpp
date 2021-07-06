/**
 * 1≤n,m≤1000
 *
 * Input:
 * 5 8
 * ########
 * #.A#...#
 * #.##.#B#
 * #......#
 * ########
 *
 * Output:
 * YES
 * 9
 * LDDRRRRRU
 */

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int n, m;
char grid[1002][1002];
vector<vector<int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool visited[1002][1002];
queue<pair<int, int>> q;
map<pair<int, int>, pair<int, int>> parent;

vector<pair<int, int>> path;
string path_;
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

/**
 * simple bfs on a grid
 */
void bfs(int si, int sj){
    visited[si][sj] = true;
    q.push({si, sj});

    while(q.size()){
        // current cell
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if(grid[x][y] == 'B')
            break;

        for(vector<int> p: moves){
            // adjacent cell
            int xadj = x + p[0];
            int yadj = y + p[1];

            if(isValid(xadj, yadj)){
                parent[{xadj, yadj}] = {x, y};
                q.push({xadj, yadj});
            }
            visited[xadj][yadj] = true;
        }

    }
}

/**
 * - find path from B to A by retracing parent &
 * - using this, find path from A to B as LRUD
 */
void findPath(int ei, int ej, int si, int sj){

    while(1){
        // adds to the end
        path.push_back({ei, ej});

        // breaks after A is included in path
        if(si==ei && sj==ej)
            break;

        int currei = ei;
        int currej = ej;
        ei = parent[{currei, currej}].first;
        ej = parent[{currei, currej}].second;
    }

    // from A to B
    reverse(path.begin(), path.end());

    for(int i=0; i<path.size()-1; i++){
        pair<int, int> curr = path[i];
        pair<int, int> next = path[i+1];

        if(curr.second == next.second){
            if(curr.first < next.first)
                path_ += "D";
            else
                path_ += "U";
        }
        else{
            if(curr.second < next.second)
                path_ += "R";
            else
                path_ += "L";
        }
    }

}

/**
 * - call bfs from A,
 * - print if there is a way b/e A & B &
 * - print the path & path length (if present)
 */
void solve(int si, int sj, int ei, int ej){

    bfs(si, sj);

    if(visited[ei][ej]){
        cout << "YES" << endl;

        findPath(ei, ej, si, sj);
        
        cout << path_.length() << endl;
        cout << path_ << endl;
    }
    else
        cout << "NO" << endl;

}

/**
 * - take i/p => n, m, grid[][]
 * - store indices of start & end cells &
 * - mark cells visited.
 */
int main()
{
    cin >> n >> m;

    int si, sj, ei, ej;
    char x;

    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> x;
            grid[i][j] = x;
            if (x == 'A'){
                si = i; sj = j;
            }
            else if (x == 'B'){
                ei = i; ej = j;
            }
            else if (x == '#')
                visited[i][j] = true;
            else
                visited[i][j] = false;
            
        }
    }

    solve(si, sj, ei, ej);

    return 0;
}