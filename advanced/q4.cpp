#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

int T;
int N, M;
int hive[15][15] = {
    0,
};
bool used[15][15] = {
    false};
int ans = INT_MIN;

int yd_odd[] = {1, 0, -1, 0, -1, -1};
int xd_odd[] = {0, -1, 0, 1, -1, 1};

int yd_even[] = {1, 0, -1, 0, 1, 1};
int xd_even[] = {0, -1, 0, 1, -1, 1};

int tmp_calc = 0;

void dfs(int y, int x, int num)
{
    if (num == 4)
    {
        // cout << tmp_calc << endl;
        ans = max(tmp_calc, ans);
        return;
    }

    for (int i = 0; i < 6; i++)
    {
        int ny, nx;
        if (x % 2 == 0)
        {
            ny = y + yd_even[i];
            nx = x + xd_even[i];
        }
        else
        {
            ny = y + yd_odd[i];
            nx = x + xd_odd[i];
        }

        if (ny < 0 || nx < 0 || ny >= N || nx >= M || used[ny][nx])
            continue;

        used[ny][nx] = true;
        tmp_calc += hive[ny][nx];

        dfs(ny, nx, num + 1);

        used[ny][nx] = false;
        tmp_calc -= hive[ny][nx];
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        memset(hive, 0, sizeof(hive));
        memset(used, false, sizeof(used));
        // initialize ans
        ans = INT_MIN;
        // ans = 0;

        cin >> N >> M;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cin >> hive[i][j];
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                tmp_calc = hive[i][j];
                used[i][j] = true;
                dfs(i, j, 1);
                used[i][j] = false;
            }
        }

        cout << "#" << tc << " " << ans << endl;
    }
}

// I think you need to solve this with bfs, because the blocks need to be contiguous

// #include <iostream>
// #include <climits>
// #include <cstring>
// #include <queue>

// using namespace std;

// int T;
// int N, M;
// int hive[15][15] = {
//     0,
// };
// bool used[15][15] = {
//     false};
// int ans = INT_MIN;

// int yd_odd[] = {1, 0, -1, 0, -1, -1};
// int xd_odd[] = {0, -1, 0, 1, -1, 1};

// int yd_even[] = {1, 0, -1, 0, 1, 1};
// int xd_even[] = {0, -1, 0, 1, -1, 1};

// struct node
// {
//     int y;
//     int x;
//     int cnt;
//     int sum;
// };

// int tmp_calc = 0;

// void bfs(int y, int x)
// {
//     queue<node> q;
//     q.push({y, x, 1, hive[y][x]});
//     used[y][x] = true;

//     while (!q.empty())
//     {
//         node now = q.front();
//         q.pop();

//         if (now.cnt == 4)
//         {
//             ans = max(ans, now.sum);
//             continue;
//         }

//         for (int i = 0; i < 6; i++)
//         {
//             int ny, nx;
//             if (now.x % 2 == 0)
//             {
//                 ny = now.y + yd_even[i];
//                 nx = now.x + xd_even[i];
//             }
//             else
//             {
//                 ny = now.y + yd_odd[i];
//                 nx = now.x + xd_odd[i];
//             }

//             if (ny < 0 || nx < 0 || ny >= N || nx >= M || used[ny][nx])
//                 continue;

//             used[ny][nx] = true;
//             q.push({ny, nx, now.cnt + 1, now.sum + hive[ny][nx]});
//         }

//         // Backtrack the used state after exploring
//         for (int i = 0; i < 6; i++)
//         {
//             int ny, nx;
//             if (now.x % 2 == 0)
//             {
//                 ny = now.y + yd_even[i];
//                 nx = now.x + xd_even[i];
//             }
//             else
//             {
//                 ny = now.y + yd_odd[i];
//                 nx = now.x + xd_odd[i];
//             }

//             // Unmark the cell for future explorations
//             if (ny >= 0 && nx >= 0 && ny < N && nx < M)
//             {
//                 used[ny][nx] = false;
//             }
//         }
//     }
// }

// int main()
// {
//     freopen("input.txt", "r", stdin);

//     cin >> T;

//     for (int tc = 1; tc <= T; tc++)
//     {
//         memset(hive, 0, sizeof(hive));
//         memset(used, false, sizeof(used));
//         // initialize ans
//         ans = INT_MIN;
//         // ans = 0;

//         cin >> N >> M;

//         for (int i = 0; i < N; i++)
//         {
//             for (int j = 0; j < M; j++)
//             {
//                 cin >> hive[i][j];
//             }
//         }

//         for (int i = 0; i < N; i++)
//         {
//             for (int j = 0; j < M; j++)
//             {
//                 bfs(i, j);
//             }
//         }

//         cout << "#" << tc << " " << ans << endl;
//     }
// }