#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int s, d;
int visited[100001] = {
    0,
};
int dist[100001];
int result = 0;

void bfs(int source, int dest)
{
    if (source == dest)
    {
        return;
    }

    queue<int> q;
    q.push(source);
    visited[source];

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        int pos[] = {now / 2, now * 2, now + 1, now - 1};

        for (int next : pos)
        {
            if (next > 0 && next <= 100000 && !visited[next])
            {
                q.push(next);
                visited[next] = 1;
                dist[next] = dist[now] + 1;
            }
            if (next == dest)
            {
                result = dist[next];
            }
        }
    }
}

int main()
{
    cin >> s >> d;

    bfs(s, d);

    cout << result;
}