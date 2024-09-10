#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int field[101][101];
int visited[101][101][4];
int sy, sx, sd;
int ty, tx, td;

struct node
{
    int y;
    int x;
    int dir;
    int cnt;
};

// need to debug the case when there is 1, it is a wall and the mover cannot move towards that direction

// int dy[] = {-1, 0, 1, 0}; // 상, 우, 하, 좌
// int dx[] = {0, 1, 0, -1};
// // 한 지점에서 할 수 있는거:
// // 1. 왼쪽으로 돌기
// // (dir + 1 +4) %4
// int ny = ~
// int nx = ~
// visited push

// // 2. 오른쪽으로 돌기 <<얘들은 아래처럼 하드코딩하거나
// // (dir - 1 +4) %4
// int ny = ~
// int nx = ~
// visited push

// // 3. 1~3칸 진행
// for(int dist = 1; dist<=3; dist++){
// int ny = y+dy[dir] * dist;
// int nx = x+dx[dir] * dist;
// if(visited || field) break;
// }

int dir[4][3][5] = {
    // 0
    {// ydir, xdir, direction
     {0, 0, 0, 0, 0},
     {0, 0, 1, 2, 3},
     {2, 3, 0, 0, 0}},
    // 1
    {
        {0, 0, 0, 0, 0},
        {0, 0, -1, -2, -3},
        {3, 2, 1, 1, 1}},
    // 2
    {
        {0, 0, 1, 2, 3},
        {0, 0, 0, 0, 0},
        // {0, 0, 0, -1, -2}},
        {1, 0, 2, 2, 2}},
    // 3
    {
        {0, 0, -1, -2, -3},
        {0, 0, 0, 0, 0},
        // {0, 0, 0, -3, -2}}};
        {0, 1, 3, 3, 3}}};

int bfs(int y, int x, int d)
{
    queue<node> q;
    q.push({y, x, d, 0});
    visited[y][x][d] = 1;

    while (!q.empty())
    {
        node now = q.front();
        q.pop();
        int d = now.dir;

        if (now.y == ty && now.x == tx && now.dir == td)
        {
            return now.cnt;
        }

        // cout << "d " << d << endl;
        // cout << "now y and x " << now.y << " " << now.x << endl;

        for (int i = 0; i < 5; i++)
        {
            int ny = now.y + dir[d][0][i];
            int nx = now.x + dir[d][1][i];
            int nd = dir[d][2][i];

            // cout << "ny and nx " << ny << " " << nx << " " << nd << endl;

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;
            if (visited[ny][nx][nd])
                continue;
            if (field[ny][nx])
                break;

            visited[ny][nx][nd] = 1;
            q.push({ny, nx, nd, now.cnt + 1});
        }
    }
    return 0;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    memset(visited, 0, sizeof(visited));

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> field[i][j];
        }
    }

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < M; j++)
    //     {
    //         cout << field[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cin >> sy >> sx >> sd;
    cin >> ty >> tx >> td;

    sy--;
    sx--;
    sd--;
    ty--;
    tx--;
    td--;

    // cout << sy << " " << sx << " " << sd << endl;
    // cout << ty << " " << tx << " " << td << endl;

    int ans;
    ans = bfs(sy, sx, sd);

    cout << ans << endl;

    return 0;
}

// ################### 강사님 코드 ######################
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

using namespace std;

struct robot
{
    int y;   // y좌표
    int x;   // x좌표
    int di;  // 방향 (0 ~ 3)
    int cmd; // 커맨드 입력 횟수
};

int direction[4][2] = {
    // 방향배열
    {-1, 0}, // 북
    {0, 1},  // 동
    {1, 0},  // 남
    {0, -1}  // 서
};

int N;                    // 물류창고 세로 길이
int M;                    // 물류창고 가로 길이
int map[101][101];        // 장애물 and visited 입력
int visited[101][101][4]; //[y][x][di]
int y, x, di;             // 목표 좌표, 방향
queue<robot> q;

void commend(robot r)
{

    // 전진
    int ny, nx;

    for (int i = 1; i <= 3; i++)
    {
        ny = r.y + direction[r.di][0] * i;
        nx = r.x + direction[r.di][1] * i;
        if (ny < 0 || ny >= N || nx < 0 || nx >= M)
            break; // 범위를 벗어나면 전진불가
        if (map[ny][nx] == 1)
            break; // 장애물 만나면 전진 불가
        if (visited[ny][nx][r.di] == 1)
            continue; // 방문 장소 진입 불가
        visited[ny][nx][r.di] = 1;
        q.push({ny, nx, r.di, r.cmd + 1});
    }

    int ndi;

    // 우회전
    if (r.di == 3)
        ndi = 0;
    else
        ndi = r.di + 1;
    if (visited[r.y][r.x][ndi] != 1)
    { // 방문 장소 진입불가
        visited[r.y][r.x][ndi] = 1;
        q.push({r.y, r.x, ndi, r.cmd + 1});
    }

    // 좌회전
    if (r.di == 0)
        ndi = 3;
    else
        ndi = r.di - 1;
    if (visited[r.y][r.x][ndi] != 1)
    {
        visited[r.y][r.x][ndi] = 1;
        q.push({r.y, r.x, ndi, r.cmd + 1});
    }
}

int main()
{

    // freopen("input.txt", "r", stdin);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }

    // 시작좌표 입력
    int changeDi[5] = {0, 1, 3, 2, 0};

    cin >> y >> x >> di;
    y -= 1;
    x -= 1;
    di = changeDi[di];
    q.push({y, x, di, 0});

    // 도착좌표 입력
    cin >> y >> x >> di;
    y -= 1;
    x -= 1;
    di = changeDi[di];

    while (1)
    {
        robot r = q.front();
        q.pop();
        if (r.y == y && r.x == x && r.di == di)
        {
            cout << r.cmd;
            break;
        }

        commend(r);
        int de = 1;
    }
}