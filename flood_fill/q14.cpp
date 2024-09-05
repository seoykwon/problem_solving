#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

int N;
int xs, ys, zs;
int xe, ye, ze;
char cube[101][101][101];
int visited[101][101][101];
int ydir[] = {1, 0, -1, 0, 0, 0};
int xdir[] = {0, -1, 0, 1, 0, 0};
int zdir[] = {0, 0, 0, 0, 1, -1};
struct pos{
    int y;
    int x;
    int z;
    int dist;
};

int bfs(int ys, int xs, int zs){
    queue <pos> q;
    q.push({ys, xs, zs, 0});
    visited[zs][ys][xs] = 1;

    while(!q.empty()){
        pos now = q.front();
        q.pop();

        if (now.y == ye && now.x == xe && now.z == ze){
            return now.dist;
        }

        for (int i = 0; i < 6; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];
            int nz = now.z + zdir[i];

            if (ny <= 0 || nx <= 0 || nz <= 0 || ny > N || nx > N || nz > N) continue;
            if (visited[nz][ny][nx] || cube[nz][ny][nx] == '1') continue;

            visited[nz][ny][nx] = visited[now.z][now.y][now.x] + 1;

            q.push({ny, nx, nz, now.dist + 1});
        }
    }
    return -1;
}

int main(){
    // freopen("input.txt", "r", stdin);

    cin >> N;
    cin >> xs >> ys >> zs;
    cin >> xe >> ye >> ze;

    for (int z = 1; z <= N; z++){
        for (int i = 1; i <= N; i++){
            for (int j = 1; j <= N; j++){
                cin >> cube[z][i][j];
                visited[z][i][j] = 0;
            }
        }
    }

    // for (int z = 1; z <= N; z++){
    //     for (int i = 1; i <= N; i++){
    //         for (int j = 1; j <= N; j++){
    //             cout << cube[z][i][j] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    int ans = bfs(ys, xs, zs);
    cout << ans << endl;
    return 0;
}