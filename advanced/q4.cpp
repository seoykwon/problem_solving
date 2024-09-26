#include <iostream>
#include <climits>
#include <cstring>
#include <algorithm>

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

    int ny = y;
    int nx = x;

    for (int i = 0; i < 6; i++)
    {
        // debugged #1: you need to use nx instead of x
        // you need to use the updated x.
        if (nx % 2 == 0)
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