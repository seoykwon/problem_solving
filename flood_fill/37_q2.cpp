#include <iostream>
#include <queue>
using namespace std;

int N, M;
int MAP[1001][1001];
int y, x;
int visited[1001][1001];
int maxN = 0;

struct Node
{
    int y;
    int x;
};

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }
    cin >> y >> x;
}

int check()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (visited[i][j] > maxN)
            {
                maxN = visited[i][j];
            }
            if (visited[i][j] == 0)
            {
                return -1;
            }
        }
    }
    return maxN;
}

int bfs(int sy, int sx)
{
    queue<Node> q;
    q.push({sy, sx});
    visited[sy][sx] = 1;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        int ans = check();
        if (ans != -1)
            return ans;

        int ydir[] = {-1, 0, 1, 0};
        int xdir[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;

            if (visited[ny][nx])
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    input();

    cout << bfs(y, x) - 1;
}