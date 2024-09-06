#include<iostream>
#include<queue>
using namespace std;

int N, M;
int field[501][501];
int blossom[501][501];
int sy, sx;
struct Node{
    int y;
    int x;
};
int yd[] = {-1, 0, 1, 0};
int xd[] = {0, -1, 0, 1};

void bfs(int y, int x){
    queue <Node> q;
    q.push({y, x});
    blossom[y][x] = 1;

    while(!q.empty()){
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + yd[i];
            int nx = now.x + xd[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
            if (blossom[ny][nx]) continue;

            blossom[ny][nx] = blossom[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }
}

int main(){
    cin >> N >> M;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> field[i][j];
            blossom[i][j] = 0;
        }
    }

    cin >> sy >> sx;

    bfs(sy, sx);
}