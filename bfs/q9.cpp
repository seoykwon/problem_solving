#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int s, d;
int cnt[100001] = {
    0,
};

void bfs(int source, int dest)
{
    queue<int> q;
    q.push(source);

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        if (now == dest)
        {
            cnt[now]++;
        }

        while (now > 1000000 || now < 0)
        {
            if (!q.empty())
            {
                now = q.front();
                q.pop();
            }
            else
            {
                return;
            }
        }
        cnt[now] += 1;
        cout << "now : " << now << endl;

        q.push(now / 2);
        q.push(now * 2);
        q.push(now + 1);
        q.push(now - 1);
    }
}

int main()
{
    cin >> s >> d;

    bfs(s, d);
}