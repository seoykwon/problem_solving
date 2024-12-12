#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, v;
vector<int> Edge[1001];
int used[1001];
int visited[1001];

void dfs(int node)
{
    cout << node << " ";
    for (int i = 0; i < Edge[node].size(); i++)
    {
        int next = Edge[node][i];

        if (used[next])
            continue;

        used[next] = 1;
        dfs(next);
    }
}

void bfs(int node)
{
    queue<int> q;
    q.push(node);
    visited[node] = 1;

    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        cout << now << " ";

        for (int i = 0; i < Edge[now].size(); i++)
        {
            int next = Edge[now][i];

            if (visited[next])
                continue;

            visited[next] = 1;
            q.push(next);
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n >> m >> v;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        Edge[a].push_back(b);
        Edge[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        sort(Edge[i].begin(), Edge[i].end());
    }

    used[v] = 1;
    dfs(v);
    cout << '\n';
    bfs(v);

    return 0;
}

/**
 * 디버깅: 방문할 수 있는 정점이 여러 개인 경우는 정점 번호가 작은 것을 먼저 방문
 * 그래서 벡터를 정렬해 줘야 한다.
 */