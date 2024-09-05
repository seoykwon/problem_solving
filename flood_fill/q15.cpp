#include <iostream>
#include <queue>

using namespace std;

int N, M;
char board[51][51];
char res[51][51];
bool visited[51][51];
int sy, sx;
int ydir[] = {1, 1, 0,-1,-1,-1,0,1};
int xdir[] = {0,-1,-1,-1,0,1,1,1};

struct pos {
    int y;
    int x;
};

void bfs(int y, int x){
    queue <pos> q;

    if (board[y][x] == 'M'){
        // bomb exploded == game over
        res[y][x] = 'X';
        return;
    }
    else if (board[y][x] == 'E'){
        q.push({y, x});
        visited[y][x] = 1;
    }

    while(!q.empty()){
        pos now = q.front();
        q.pop();
        int bomb = 0;

        // check if there are bombs
        for (int i = 0; i < 8; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M || visited[ny][nx]) continue;
            // if (res[ny][nx] >= '0' && res[ny][nx] <= '9') continue;

            if (board[ny][nx] == 'M'){
                bomb++;
            }
            else {
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }

        if (bomb == 0){
            res[now.y][now.x] = 'B';
        }
        else {
            // cout << bomb << endl;
            res[now.y][now.x] = '0' + bomb;
        }
        
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> board[i][j];
            res[i][j] = board[i][j];
        }
    }

    cin >> sy >> sx;


    bfs(sy, sx);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cout << res[i][j];
        }
        cout << endl;
    }
}