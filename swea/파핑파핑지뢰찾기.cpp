#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <queue>

using namespace std;

int map[301][301];
int ans, N;
const int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dc[] = {0, 0, -1, 1, 1, -1, -1, 1};

void init()
{
    memset(map, 0, sizeof(map));
    // memset(visited, 0, sizeof(visited));
    ans = 0;
}

bool isZero(int r, int c)
{
    for (int i = 0; i < 8; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >= N || nc >= N)
            continue;
        if (map[nr][nc] == 1)
            return false;
    }
    return true;
}

void click(int r, int c)
{
    queue<pair<int, int>> q;
    q.push({r, c});
    map[r][c] = 0;

    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        map[curr.first][curr.second] = 0;

        for (int i = 0; i < 8; i++)
        {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];
            if (nr < 0 || nc < 0 || nr >= N || nc >= N || map[nr][nc] != 2)
                continue;
            map[nr][nc] = 0;
            if (isZero(nr, nc))
                q.push({nr, nc});
        }
    }
}

int solve()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] != 2)
                continue;
            if (isZero(i, j))
            {
                click(i, j);
                ans++;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] == 2)
                ans++;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("input.txt", "r", stdin);
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        init();

        cin >> N;
        cin.ignore();

        string line;
        for (int i = 0; i < N; i++)
        {
            getline(cin, line);

            stringstream st(line);
            for (int j = 0; j < N; j++)
            {
                char tmp;
                st >> tmp;

                map[i][j] = (tmp == '*') ? 1 : 2;
                // 1 = 지뢰 2 = 지뢰 아님
            }
        }
        ans = solve();
        cout << "#" << tc << " " << ans << "\n";
    }
}