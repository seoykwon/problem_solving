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
            // else {
            //     visited[ny][nx] = true;
            //     q.push({ny, nx});
            // }
        }

        if (bomb == 0){
            res[now.y][now.x] = 'B';
            for (int i = 0; i < 8; i++){
                int ny = now.y + ydir[i];
                int nx = now.x + xdir[i];

                if (ny < 0 || nx < 0 || ny >= N || nx >= M || visited[ny][nx]) continue;
                // if (res[ny][nx] >= '0' && res[ny][nx] <= '9') continue;

                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
        else {
            // cout << bomb << endl;
            visited[now.y][now.x] = true;
            res[now.y][now.x] = '0' + bomb;
        }
        
    }
}

int main(){
    // freopen("input.txt", "r", stdin);
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

// ########## 강사님 코드 ###############
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int r, c;
    char type;
};

int H, W;
char MAP[50][50];
char result[50][50];
int X, Y;
void input() {
    cin >> H >> W;
    for (int r = 0; r < H; r++){
        cin >> MAP[r];
    }
    cin >> X >> Y;
}

int dr[] = { -1,-1,-1,0,0,1,1,1 };
int dc[] = { -1,0,1,-1,1,-1,0,1 };

void change(Node now) {
    if (MAP[now.r][now.c] == 'M'){
        MAP[now.r][now.c] = 'X';
        return;
    }

    int cnt = 0;
    for (int t = 0; t < 8; t++){
        int nr = now.r + dr[t];
        int nc = now.c + dc[t];
        if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue;
        if (MAP[nr][nc] == 'M'){
            cnt++;
        }
    }
    MAP[now.r][now.c] = cnt + '0';
    if (MAP[now.r][now.c] == '0') MAP[now.r][now.c] = 'B';
}

void bfs(int r, int c){
    queue<Node> qu;
    int visited[50][50] = {0};
    qu.push({r, c, MAP[r][c]});
    visited[r][c] = 1;

    while (!qu.empty()) {
        Node now = qu.front(); qu.pop();
        change(now);
        if (MAP[now.r][now.c] == 'X') break;
        if (MAP[now.r][now.c] != 'B') continue;

        for (int t = 0; t < 8; t++) {
            int nr = now.r + dr[t];
            int nc = now.c + dc[t];

            if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue;
            if (visited[nr][nc] == 1) continue;

            visited[nr][nc] = 1;
            qu.push({nr, nc});
        }
    }
}

int main(){
    input();
    bfs(X, Y);
    for (int r = 0; r < H; r++){
        for (int c = 0; c < W; c++){
            cout << MAP[r][c];
        }
        cout << endl;
    }
    return 0;
}