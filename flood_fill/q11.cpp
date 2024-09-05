#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

int N;
char field[21][21];
int visited[21][21];
int sy, sx;
int fy, fx;
struct Node{
    int y;
    int x;
};
vector <Node> extinguisher;
int ydir[] = {-1, 0, 1, 0};
int xdir[] = {0, -1, 0, 1};

int bfs(int y, int x){
    queue <Node> q;
    q.push({y, x});
    memset(visited, 0, sizeof(visited));
    visited[y][x] = 1;

    while(!q.empty()){
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if (visited[ny][nx]) continue;
            if (field[ny][nx] == '#') continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;

            // the fire fighter cannot go through fire without extinguisher
            if (ny == fy && nx == fx) continue;
            // i did not push new positions into the queue, and had to debug this
            q.push({ny, nx});
        }
    }

    if (visited[sy][sx] == 0 || visited[fy][fx] == 0){
        return -1;
    }

    return (visited[sy][sx] - 1) + (visited[fy][fx] - 1);
}

int main(){
    // freopen("input.txt", "r", stdin);
    cin >> N;

    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> field[i][j];

            if (field[i][j] == '$'){
                fy = i;
                fx = j;
            }
            else if (field[i][j] == 'A'){
                extinguisher.push_back({i, j});
            }
        }
    }
    cin >> sy >> sx;

    int ans = INT_MAX;

    for(int i = 0; i < extinguisher.size(); i++){
        Node now = extinguisher[i];
        int ret = bfs(now.y, now.x);

        ans = min(ans, ret);
    }

    cout << ans << endl;
    return 0;
}