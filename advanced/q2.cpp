// #include <iostream>
// #include <queue>
// #include <cstring>

// using namespace std;

// int T;
// int N;
// int board[51][51] = {0};
// int visited[51][51] = {0};
// int sy, sx;
// int ans = 0;

// int yd[4] = {1, 0, -1, 0};
// int xd[4] = {0, -1, 0, 1};

// struct pos
// {
//     int y;
//     int x;
// };

// void calculate(int y, int x, int trial)
// {
//     if (trial == 4)
//     {
//         return;
//     }

//     if (board[y][x] == 1)
//     {
//         // cout << "eat jjol: " << y << " " << x << endl;
//         board[y][x] = 3;
//         ans++;
//     }

//     for (int i = 0; i < 4; i++)
//     {
//         bool can_j = false;

//         for (int j = 1; j < N; j++)
//         {
//             int ny = y + yd[i] * j;
//             int nx = x + xd[i] * j;

//             if (ny < 0 || nx < 0 || ny >= N || nx >= N)
//                 break;

//             if ((board[ny][nx] == 1 || board[ny][nx] == 3) && !can_j)
//             {
//                 can_j = true;
//                 continue;
//             }

//             if (can_j)
//             {
//                 // you cannot jump over 2 jjol at once:
//                 calculate(ny, nx, trial + 1);
//             }
//         }
//     }
// }

// int main()
// {
//     freopen("input.txt", "r", stdin);
//     cin >> T;

//     for (int i = 1; i <= T; i++)
//     {
//         cin >> N;

//         // need to reset the board and visited every time new test case is inputted
//         memset(board, 0, sizeof(board));
//         memset(visited, 0, sizeof(visited));
//         ans = 0;

//         for (int i = 0; i < N; i++)
//         {
//             for (int j = 0; j < N; j++)
//             {
//                 cin >> board[i][j];

//                 if (board[i][j] == 2)
//                 {
//                     sy = i;
//                     sx = j;
//                     board[i][j] = 0;
//                 }
//             }
//         }

//         calculate(sy, sx, 0);

//         cout << "#" << i << " " << ans << endl;
//     }
// }

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <vector>

#include <cstring>
using namespace std;

struct Node
{
    int y;
    int x;
};

int N;
int cnt;
int MAP[51][51];
int checked[51][51];
int ydir[] = {-1, 1, 0, 0};
int xdir[] = {0, 0, -1, 1};

void dfs(int y, int x, int move)
{
    // cout << '\n';
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         cout << MAP[i][j] << " ";
    //     }
    //     cout << '\n';
    // }

    // 3번 이동하면 종료
    if (move == 3)
    {
        return;
    }

    // 재귀 구성
    // 4방향으로 앞에 1 이 있다면 건너뛰고,
    // 먹을 수 있는게 있는지 확인
    for (int i = 0; i < 4; i++)
    {
        int dist = 1;
        int skipped = 0;
        while (true)
        {
            // i 방향으로 계속 확인
            int ny = y + ydir[i] * dist;
            int nx = x + xdir[i] * dist;
            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                break;

            // 1을 만나면 skipped++
            // skipped == 1 : 하나 건너뛸 발판을 찾았다
            // skipped == 2 : 하나를 건너뛰어서 먹을 수 있는 쫄이다.
            // skipped >= 3 : 못간다
            if (MAP[ny][nx] == 1)
                skipped++;

            // 1을 2개를 건너뛸수는 없으니 종료
            if (skipped >= 3)
                break;

            // 쫄이 있는 위치면서, 2번째 만나는 쫄이라면 ->애는 먹어치울수 있다.
            if (MAP[ny][nx] == 1 && skipped == 2)
            {
                // 이동
                MAP[ny][nx] = 2;
                MAP[y][x] = 0;
                // 중복 방지 -> 이미 먹었던 쫄이 아니라면 cnt++
                if (checked[ny][nx] != 1)
                {
                    checked[ny][nx] = 1;
                    cnt++;
                }
                dfs(ny, nx, move + 1);
                // 복구
                MAP[y][x] = 2;
                MAP[ny][nx] = 1;
            }

            // 만약 쫄이 없는 위치고, 하나의 쫄을 건너뛰면
            if (MAP[ny][nx] == 0 && skipped == 1)
            {
                // 그냥 이동
                MAP[ny][nx] = 2;
                MAP[y][x] = 0;
                dfs(ny, nx, move + 1);
                // 복구
                MAP[y][x] = 2;
                MAP[ny][nx] = 0;
            }
            // 한칸 더 가보기
            dist++;
        }
    }
}

int main()
{

    // freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        // reset
        int y = 0;
        int x = 0;
        cnt = 0;
        memset(MAP, 0, sizeof(MAP));
        memset(checked, 0, sizeof(checked));

        // input
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> MAP[i][j];
                if (MAP[i][j] == 2)
                {
                    y = i;
                    x = j;
                }
            }
        }

        dfs(y, x, 0);

        // output
        cout << "#" << tc << " " << cnt << '\n';
    }
}
