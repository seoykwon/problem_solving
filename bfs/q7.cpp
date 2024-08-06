#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m;
int r, k;
vector<int> v[11];
int dist[11];
int visited[11] = {0};
int cnt = 0;

void input()
{
    // freopen("input.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i <= n; i++)
        dist[i] = 2147483647;
    if (m != 0)
    {
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
    }

    cin >> r >> k;
}

void bfs(int start)
{
    queue<int> q;
    visited[start] = 1;
    q.push(start);
    dist[start] = 0;

    while (!q.empty())
    {
        int now = q.front();
        // cout << now << "\n";
        q.pop();

        // cout << "next: ";
        for (int i = 0; i < v[now].size(); i++)
        {
            int next = v[now][i];
            // cout << next << " ";
            if (!visited[next])
            {
                q.push(next);
                visited[next] = 1;
                dist[next] = 1 + dist[now];
            }
        }
        // cout << endl;
    }
}

int main()
{
    input();

    bfs(r);

    for (int i = 1; i <= n; i++)
    {
        if (dist[i] <= k)
        {
            cnt++;
        }
        // cout << "dist " << i << ": " << dist[i] << endl;
    }
    cout << cnt;
}