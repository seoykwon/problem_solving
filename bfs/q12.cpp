#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m, k, p;
vector<int> roads[200001];
int oil[200001] = {
    0,
};
int visited[200001] = {
    0,
};
vector<int> dest;

void input()
{
    cin >> n >> m >> k >> p;

    for (int i = 0; i < m; i++)
    {
        int from, to;
        cin >> from >> to;
        roads[from].push_back(to);
    }
}

void bfs(int start)
{
    queue<int> q;
    q.push(start);
    oil[start] = 0;
    visited[start] = 1;

    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        visited[now] = 1;

        for (int i = 0; i < roads[now].size(); i++)
        {
            int next = roads[now][i];
            if (!visited[next])
            {
                q.push(next);
                visited[next] = 1;
                oil[next] = oil[now] + 1;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (oil[i] == k)
        {
            dest.push_back(i);
        }
    }
}

int main()
{
    input();

    bfs(p);

    if (dest.size() == 0)
    {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < dest.size(); i++)
    {
        cout << dest[i] << endl;
    }
}