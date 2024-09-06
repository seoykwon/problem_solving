#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

int N;
int xs, ys, zs;
int xe, ye, ze;
char cube[102][102][102];
int visited[102][102][102];
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
    visited[zs][xs][ys] = 1;

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
            if (visited[nz][nx][ny] || cube[nz][nx][ny] == '1') continue;

            visited[nz][nx][ny] = visited[now.z][now.x][now.y] + 1;

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

// z, y, x 순서가 정해진 것이 아님
// 문제마다 다르고 이 문제의 경우는 z, x, y 였기 때문에 이 순서 문제로 모든 테케 정답을 맞추지 못 한 것이였다.

// ################### friend code #############################
// #include <iostream>
// #include <queue>
// using namespace std;
// const int dy[] = {-1,1,0,0,0,0};
// const int dx[] = {0,0,-1,1,0,0};
// const int dz[] = {0,0,0,0,-1,1};

// int N;
// int board[102][102][102];
// queue<pair<int, pair<int, int>>> q; // {z, {y, x}};

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);

//     freopen("input.txt", "r", stdin);
//     cin >> N;
//     for (int i = 0; i <= N + 1; i++){
//         for (int j = 0; j <= N + 1; j++){
//             for (int k = 0; k <= N + 1; k++){
//                 board[i][j][k] = 1;
//             }
//         }
//     }

//     int xs, ys, zs;
//     int xe, ye, ze;
//     cin >> xs >> ys >> zs;
//     cin >> xe >> ye >> ze;

//     for (int i = 1; i <= N; i++){
//         for (int j = 1; j <= N; j++){
//             for (int k = 1; k <= N; k++){
//                 char c;
//                 cin >> c;
//                 board[i][j][k] = c - '0';
//             }
//         }
//     }
//     q.push({zs, {ys, xs}});
//     board[zs][xs][ys] = 1;

//     while (!q.empty()){
//         int y = q.front().second.first;
//         int x = q.front().second.second;
//         int z = q.front().first;
//         int cur = board[z][x][y];
//         q.pop();

//         for (int dir = 0; dir < 6; dir++) {
//             int ny = y + dy[dir];
//             int nx = x + dx[dir];
//             int nz = z + dz[dir];
//             if (board[nz][nx][ny]) continue;
// if(nz==ze &&ny==ye &&nx==xe ){
//     cout<<cur;
//     return 0;
// }
//             board[nz][nx][ny] = cur + 1;
//             q.push({nz, {ny, nx}});
//         }
//     }

//     // if (board[ze][xe][ye]) cout << board[ze][xe][ye];
//     // else
//      cout << -1;

//     return 0;
// }