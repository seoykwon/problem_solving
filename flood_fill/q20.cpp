// #include <iostream>
// #include <queue>
// #include <cstring>
// #include <climits>
// using namespace std;

// int N;
// int field[6][6];
// int visitede[6][6];
// int visiteda[6][6];
// int ey, ex;
// int ay, ax;
// int ydir[] = {-1, 0, 1, 0, 0};
// int xdir[] = {0, -1, 0, 1, 0};
// int ans = INT_MAX;

// struct node
// {
//     int y;
//     int x;
// };

// void bfse(int y, int x)
// {
//     queue<node> q;
//     q.push({y, x});
//     visitede[y][x] = 0;

//     while (!q.empty())
//     {
//         node now = q.front();
//         q.pop();

//         for (int i = 0; i < 5; i++)
//         {
//             int ny = now.y + ydir[i];
//             int nx = now.x + xdir[i];

//             if (ny < 0 || nx < 0 || ny >= N || nx >= N)
//                 continue;
//             if (field[ny][nx])
//                 continue;
//             if (visitede[ny][nx] > visitede[now.y][now.x] + 1 || visitede[ny][nx] == -1)
//             {
//                 visitede[ny][nx] = visitede[now.y][now.x] + 1;
//                 q.push({ny, nx});
//             }
//         }
//     }
// }

// void bfsa(int y, int x)
// {
//     queue<node> q;
//     q.push({y, x});
//     visiteda[y][x] = 0;

//     while (!q.empty())
//     {
//         node now = q.front();
//         q.pop();

//         for (int i = 0; i < 5; i++)
//         {
//             int ny = now.y + ydir[i];
//             int nx = now.x + xdir[i];

//             if (ny < 0 || nx < 0 || ny >= N || nx >= N)
//                 continue;
//             if (field[ny][nx])
//                 continue;
//             if (visiteda[ny][nx] > visiteda[now.y][now.x] + 1 || visiteda[ny][nx] == -1)
//             {
//                 visiteda[ny][nx] = visiteda[now.y][now.x] + 1;
//                 q.push({ny, nx});
//             }
//         }
//     }
// }

// int main()
// {
//     freopen("input.txt", "r", stdin);
//     cin >> N;
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             char tmp;
//             cin >> tmp;

//             if (tmp == '_')
//             {
//                 field[i][j] = 0;
//             }
//             else if (tmp == '#')
//             {
//                 field[i][j] = 1;
//             }
//         }
//     }

//     memset(visitede, -1, sizeof(visitede));
//     memset(visiteda, -1, sizeof(visiteda));

//     cin >> ey >> ex >> ay >> ax;

//     bfse(ey, ex);

//     bfsa(ay, ax);

//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             if (visitede[i][j] == visiteda[i][j] && visitede[i][j] != -1 && visiteda[i][j] != -1)
//             {
//                 if (ans > visitede[i][j])
//                 {
//                     ans = visitede[i][j];
//                 }
//             }
//         }
//     }
//     // cout << endl;
//     // for (int i = 0; i < N; i++)
//     // {
//     //     for (int j = 0; j < N; j++)
//     //     {
//     //         cout << visitede[i][j] << " ";
//     //     }
//     //     cout << endl;
//     // }
//     // cout << endl;
//     // for (int i = 0; i < N; i++)
//     // {
//     //     for (int j = 0; j < N; j++)
//     //     {
//     //         cout << visiteda[i][j] << " ";
//     //     }
//     //     cout << endl;
//     // }

//     cout << ans << endl;

//     return 0;
// }

// 두 사람을 동시에 bfs로 돌려서 서로의 경로를 고려해야 함

#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

int N;
int field[6][6];
int visitede[6][6];
int visiteda[6][6];
int ey, ex;
int ay, ax;
int ydir[] = {-1, 0, 1, 0, 0}; // 상, 좌, 하, 우, 제자리
int xdir[] = {0, -1, 0, 1, 0}; // 상, 좌, 하, 우, 제자리
int ans = INT_MAX;

struct node
{
    int y;
    int x;
    int time; // 시간을 저장
};

void bfs()
{
    queue<node> qe, qa;
    qe.push({ey, ex, 0});
    qa.push({ay, ax, 0});
    memset(visitede, -1, sizeof(visitede));
    memset(visiteda, -1, sizeof(visiteda));
    visitede[ey][ex] = 0;
    visiteda[ay][ax] = 0;

    while (!qe.empty() || !qa.empty())
    {
        // 엘사의 BFS 처리
        if (!qe.empty())
        {
            node nowe = qe.front();
            qe.pop();
            for (int i = 0; i < 5; i++)
            {
                int nye = nowe.y + ydir[i];
                int nxe = nowe.x + xdir[i];

                if (nye < 0 || nxe < 0 || nye >= N || nxe >= N)
                    continue;
                if (field[nye][nxe] || visitede[nye][nxe] != -1)
                    continue;

                visitede[nye][nxe] = nowe.time + 1;
                qe.push({nye, nxe, nowe.time + 1});
            }
        }

        // 안나의 BFS 처리
        if (!qa.empty())
        {
            node nowa = qa.front();
            qa.pop();
            for (int i = 0; i < 5; i++)
            {
                int nya = nowa.y + ydir[i];
                int nxa = nowa.x + xdir[i];

                if (nya < 0 || nxa < 0 || nya >= N || nxa >= N)
                    continue;
                if (field[nya][nxa] || visiteda[nya][nxa] != -1)
                    continue;

                visiteda[nya][nxa] = nowa.time + 1;
                qa.push({nya, nxa, nowa.time + 1});
            }
        }

        // 두 사람이 동시에 같은 지점에 도착했는지 확인
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (visitede[i][j] != -1 && visiteda[i][j] != -1)
                {
                    ans = min(ans, max(visitede[i][j], visiteda[i][j]));
                }
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char tmp;
            cin >> tmp;

            if (tmp == '_')
            {
                field[i][j] = 0;
            }
            else if (tmp == '#')
            {
                field[i][j] = 1;
            }
        }
    }

    cin >> ey >> ex >> ay >> ax;

    bfs();

    cout << ans << endl;

    return 0;
}

// ############# 강사님 코드 ################
#include <iostream>
#include <queue>
using namespace std;

struct node
{
    int y, x;
};

int ydir[] = {0, 0, 1, -1};
int xdir[] = {1, -1, 0, 0};

string MAP[5];
int ey, ex, ay, ax;
int n;
int ans;

void bfs(int y, int x)
{
    queue<node> q;
    q.push({y, x});

    int visited[5][5] = {
        0,
    };
    visited[y][x] = 1;

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        if (now.y == ay && now.x == ax)
        {
            ans = visited[now.y][now.x] - 1;
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= n || nx >= n)
                continue;
            if (visited[ny][nx] > 0)
                continue;

            // 갈수 없는 곳 -> 빙하는 지나가지 못한다!
            if (MAP[ny][nx] == '#')
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }
}

int main()
{
    cin >> n;
    // map input
    for (int i = 0; i < n; i++)
        cin >> MAP[i];
    // elsa, anna input
    cin >> ey >> ex >> ay >> ax;
    // 안나 -> 엘사
    // 엘사 -> 안나까지의 최단 경로
    bfs(ey, ex);

    cout << (ans + 1) / 2;
}