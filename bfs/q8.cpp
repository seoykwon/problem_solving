#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int t;
vector<int> v[11];
int visited[11];
int dist[11];
int arrive = 0;

void input()
{
    // freopen("input.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        v[i] = vector<int>();
        // vector initialization : necessary to get rid of trash valuesd
        visited[i] = 0;
        dist[i] = -1;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        v[a].push_back(b);
        v[b].push_back(a);
    }
    cin >> t;
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
        q.pop();

        // cout << "now : " << now << endl;

        for (int i = 0; i < v[now].size(); i++)
        {
            int next = v[now][i];
            if (!visited[next] && next != t)
            {
                visited[next] = 1;
                q.push(next);
                dist[next] = dist[now] + 1;
                // cout << "next : " << next << endl;
                // cout << "dist : " << dist[next] << endl;
            }
        }
    }
}

int main()
{
    input();

    bfs(1);

    if (!visited[n])
    {
        cout << -1;
        return 0;
    }

    cout << dist[n];
}