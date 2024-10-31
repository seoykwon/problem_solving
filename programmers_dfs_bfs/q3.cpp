#include <vector>
#include <queue>
using namespace std;

int visited[101][101] = {
    0,
};
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

struct Edge
{
    int y;
    int x;
    int cost;
};

int bfs(vector<vector<int>> &maps, int n, int m)
{
    queue<Edge> q;
    visited[0][0] = 1;
    q.push({0, 0, 1});

    while (!q.empty())
    {
        Edge now = q.front();
        q.pop();

        if (now.y == (n - 1) && now.x == (m - 1))
        {
            return now.cost;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dir[i][0];
            int nx = now.x + dir[i][1];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m)
                continue;

            if (visited[ny][nx] || maps[ny][nx] == 0)
                continue;

            visited[ny][nx] = 1;
            q.push({ny, nx, now.cost + 1});
        }
    }
    return -1;
}

int solution(vector<vector<int>> maps)
{
    int answer = 0;

    int n = maps.size();    // row
    int m = maps[0].size(); // column

    answer = bfs(maps, n, m);

    return answer;
}