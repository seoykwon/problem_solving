#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k, m;
vector<int> node[100001];
int visitedN[100001];
int ans = 0;
vector<int> hyperTube[1001];
int visitedT[1001];

void input()
{
    cin >> n >> k >> m;
    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int tmp;
            cin >> tmp;
            hyperTube[i].push_back(tmp);
            node[tmp].push_back(i);
        }
    }
}

void bfs(int start)
{
    queue<pair<int, int>> q;
    q.push({start, 1});
    visitedN[start] = 1;

    while (!q.empty())
    {
        int now = q.front().first;
        int count = q.front().second;
        q.pop();

        if (now == n)
        {
            ans = count;
            return;
        }

        for (int i = 0; i < node[now].size(); i++)
        {
            int nextT = node[now][i];
            if (!visitedT[nextT])
            {
                visitedT[nextT] = 1;
                // cout << "next T " << nextT << endl;
                for (int j = 0; j < hyperTube[nextT].size(); j++)
                {
                    int nextN = hyperTube[nextT][j];
                    // cout << "next N " << nextN << endl;
                    if (!visitedN[nextN])
                    {
                        q.push({nextN, count + 1});
                        visitedN[nextN] = 1;
                        // cout << "visited N of next N " << visitedN[nextN] << endl;
                    }
                }
            }
        }
    }
}

int main()
{
    input();

    bfs(1);

    if (ans == 0)
    {
        cout << -1;
        return 0;
    }
    cout << ans;
}

// alternative
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, k, m;
vector<int> v[100001 * 2];
int visited[200002] = {
    0,
};

void bfs(int node)
{
    queue<int> q;
    q.push(node);

    visited[node] = 1;

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        for (int i = 0; i < v[now].size(); i++)
        {
            int next = v[now][i];
            if (visited[next] > 0)
                continue;
            visited[next] = visited[now] + 1;
            q.push(next);
        }
    }
}

int main()
{
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int num;
            cin >> num;
            v[num].push_back(n + i);
            v[n + i].push_back(num);
        }
    }
    bfs(1);
    if (visited[n] == 0)
        cout << -1;
    else
        cout << (visited[n] + 1) / 2;
}