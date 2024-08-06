#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, t;
int koko, partner;
vector<int> v[101];
int visited[101];

void input()
{

    cin >> n >> t;
    for (int i = 0; i < t; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    cin >> koko >> partner;
}

void bfs(int start)
{
    queue<int> q;
    visited[start] = 1;
    q.push(start);

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        for (int i = 0; i < v[now].size(); i++)
        {
            int next = v[now][i];
            if (!visited[next])
            {
                visited[next] = 1;
                q.push(next);
            }
        }
    }
}

int main()
{
    input();

    bfs(koko);
    if (visited[partner])
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
}