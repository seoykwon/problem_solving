#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

char field[8][9];
struct node{
    int y;
    int x;
};
queue <node> q;
queue <node> first;
int ydir[] = {-1, 0, 1, 0};
int xdir[] = {0, -1, 0, 1};
int visited[8][9];

void bfs(int y, int x){
    queue <node> q;
    q.push({y, x});
    visited[y][x] = 1;

    while(!q.empty()){
        node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 8 || nx >= 9) continue;
            if (visited[ny][nx] || field[ny][nx] == '_') continue;

            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
}

void dist(){
    while(!first.empty()){
        // cout << "here" << endl;
        node now = first.front();
        first.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 8 || nx >= 9) continue;

            if (visited[ny][nx]) continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            if (field[ny][nx] == '#'){
                cout << visited[ny][nx] - 2 << endl;
                return;
            }
            first.push({ny, nx});
        }
    }
}

int main(){
    // freopen("input.txt", "r", stdin);
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 9; j++){
            cin >> field[i][j];
            visited[i][j] = 0;
        }
    }

    bfs(0, 8);

    // for (int i = 0; i < 8; i++){
    //     for (int j = 0; j < 9; j++){
    //         cout << visited[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 9; j++){
            if (field[i][j] == '#' && visited[i][j]){
                first.push({i, j});
            }
        }
    }
    
    dist();
    return 0;
}