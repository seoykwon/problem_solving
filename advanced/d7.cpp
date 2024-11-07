#include <iostream>
#include <queue>

using namespace std;

int field[51][51] = {
    0,
};
// snow = 2
// gem = 3
int sy, sx;
int gy, gx;

int lr[2][2] = {{0, -1}, {0, 1}};
int ud[2][2] = {{-1, 0}, {1, 0}};
int gauge = 1;
// vector<vector<int>> visited(51, vector<int>(51, 0));
int visited[51][51];

struct node
{
    int y, x;
    int curlimit;
};

int bfs(int N, int M)
{
    queue<node> q;
    q.push({sy, sx, 0});
    visited[sy][sx] = 1;

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        if (now.y == gy && now.x == gx)
        {
            return gauge;
        }

        // when snowman is currently on the ground, it can move left and right
        if (field[now.y][now.x] == 1)
        {
            // go left and right if the cell is ground
            for (int i = 0; i < 2; i++)
            {
                int ny = now.y + lr[i][0];
                // int nx = now.x + ud[i][1]; 바보니?
                int nx = now.x + lr[i][1];

                if (ny < 0 || nx < 0 || ny >= N || nx >= M || visited[ny][nx])
                    continue;

                if (field[ny][nx] == 1)
                {
                    visited[ny][nx] = 1;
                    q.push({ny, nx, 0});
                }
            }
        }

        // move up and down as long as in the limit
        for (int i = 0; i < 2; i++)
        {
            int ny = now.y + ud[i][0];
            int nx = now.x + ud[i][1];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M || visited[ny][nx])
                continue;

            int nextlimit = now.curlimit + 1;

            // you need to separate these two cases.
            // when the next cell is not ground
            if (nextlimit <= gauge && field[ny][nx] == 0)
            {
                visited[ny][nx] = 1;
                q.push({ny, nx, nextlimit});
            }
            // when the next cell is ground
            if (nextlimit <= gauge && field[ny][nx] == 1)
            {
                visited[ny][nx] = 1;
                q.push({ny, nx, 0});
            }
        }
    }
    // reaching the end of while loop means that the snowman did not acquire the gem
    return 0;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int N, M;

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> field[i][j];

            if (field[i][j] == 2)
            {
                sy = i;
                sx = j;
                field[i][j] = 1;
            }
            if (field[i][j] == 3)
            {
                gy = i;
                gx = j;
                field[i][j] = 1;
            }
        }
    }

    int answer = 0;
    while (!answer)
    {
        for (int i = 0; i < 51; ++i)
        {
            for (int j = 0; j < 51; j++)
            {
                visited[i][j] = 0;
            }
        }

        // when bfs reaches to the gem with current gauge, bfs returns gauge, not 0
        answer = bfs(N, M);
        if (answer == 0)
        {
            gauge++;
        }
    }

    cout << answer << '\n';
}