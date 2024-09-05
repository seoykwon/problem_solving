#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

int N, M;
int field[201][201];
int visited[201][201];
struct node{
    int y;
    int x;
    int num;
};
int ydir[] = {-1, 0, 1, 0};
int xdir[] = {0, -1, 0, 1};
queue <node> first;

void bfs(int y, int x){
    queue <node> q;
    q.push({y, x, field[y][x]});
    visited[y][x] = 1;

    while(!q.empty()){
        node now = q.front();
        q.pop();
        first.push(now);

        for (int i = 0; i < 4; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
            if (visited[ny][nx]) continue;
            if (field[ny][nx] != field[y][x]) continue;

            visited[ny][nx] = 1;
            q.push({ny, nx, field[ny][nx]});
        }
    }
}

void dist(){
    while(!first.empty()){
        node now = first.front();
        first.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            first.push({ny, nx});

            if (field[ny][nx] != 0){
                cout << visited[ny][nx] - 2 << endl;
                return;
            }
        }
    }
}

int main(){
    // freopen("input.txt", "r", stdin);
    cin >> N >> M;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> field[i][j];
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++){
        int flag = 0;
        for (int j = 0; j < M; j++){
            if (field[i][j] != 0){
                bfs(i, j);
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }

    dist();
    return 0;
}

// ################ 강사님 코드 #########################
#include <iostream>
#include <queue>

using namespace std;

struct Pos {
    int x, y;
};

int n, m;
int MAP[100][100];
int visited[100][100];
queue<Pos> q;
queue<Pos> q2;
int start;

void bfs1() {
    while (!q.empty()) {
        Pos now = q.front();
        q.pop();
        visited[now.x][now.y] = 1;

        q2.push(now);

        int xdir[] = {0, 0, 1, -1};
        int ydir[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++){
            int nextx = now.x + xdir[i];
            int nexty = now.y + ydir[i];

            if (nextx < 0 || nexty < 0 || nextx >= n || nexty >= m) continue;

            if (visited[nextx][nexty] == 1) continue;

            if (MAP[nextx][nexty] == 0 || MAP[nextx][nexty] != start) continue;

            q.push({nextx, nexty});
        }
    }
}

int bfs2() {
    while (!q2.empty()) {
        Pos now = q2.front();
        q2.pop();

        int xdir[] = {0, 0, 1, -1};
        int ydir[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int nextx = now.x + xdir[i];
            int nexty = now.y + ydir[i];

            if (nextx < 0 || nexty < 0 || nextx >= n || nexty >= m)
                continue;

            if (visited[nextx][nexty] > 0)
                continue;

            if (MAP[nextx][nexty] == start)
                continue;

            if (MAP[nextx][nexty] != 0)
                return visited[now.x][now.y];

            visited[nextx][nexty] = visited[now.x][now.y] + 1;
            q2.push({nextx, nexty});
        }
    }

    return -1;
}

int main() {
    cin >> n >> m;

    start = 0;
    int found = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> MAP[i][j];

            if (MAP[i][j] != 0 && found == 0) {
                start = MAP[i][j];
                q.push({i, j});
                found = 1;
            }
        }
    }

    bfs1();
    int ans = bfs2();

    cout << ans-1 << endl;

    return 0;
}