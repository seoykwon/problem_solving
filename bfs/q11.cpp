#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int start, dest;
int cnt = 0;
int visited[100001] = {
    0,
};

void input()
{
    cin >> start >> dest;
}

void bfs()
{
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty())
    {
        int size = q.size();
        cnt++;

        while (size--)
        {
            int now = q.front();
            q.pop();

            if (now + 1 == dest || now - 1 == dest || now * 2 == dest)
            {
                return;
            }

            if (now + 1 <= 100000 && !visited[now + 1])
            {
                q.push(now + 1);
                visited[now + 1] = 1;
            }
            if (now - 1 > 0 && !visited[now - 1])
            {
                q.push(now - 1);
                visited[now - 1] = 1;
            }
            if (now * 2 <= 100000 && !visited[now * 2])
            {
                q.push(now * 2);
                visited[now * 2] = 1;
            }
        }
    }
}

int main()
{
    input();

    if (start == dest)
    {
        cout << 0;
        return 0;
    }

    bfs();

    cout << cnt;
}