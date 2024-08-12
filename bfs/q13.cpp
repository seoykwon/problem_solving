#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k, m;
// vector<vector<int>> path;
vector<int> path[100001];
int cnt = 0;
int in[1000] = {
    0,
};
int route[100001] = {
    0,
};
int ans = 0;

void input()
{
    cin >> n >> k >> m;
    // path = vector<vector<int>>(n + 1, vector<int>()); // n* ? 깡통배열

    // n*n 2로 채워진 배열
    // vector<vector<int>> v(n, vector<int>(n,2));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cin >> in[j];
        }

        for (int j = 0; j < k; j++)
        {
            for (int m = 0; m < k; m++)
            {
                if (j == m)
                {
                    continue;
                }
                path[in[j]].push_back(in[m]);
                // cout << "j " << j << endl;
                // cout << "m " << m << endl;
            }
        }
    }
}

// int n = 5;
// vector<vector<int>> v(n, vector<int>());

// int a; // 초기화 안됨.

// vector<int> v; //<< 초기화는 안됨. 근데 push_back(2) 이런거가능,
// queue<int> q;

// 2차원 벡터인데 가로도 모르고 세로도 모를 경우
// vector<vector<int>> v;
// v.push_back(vector<int>());

void bfs(int start)
{
    queue<int> q;
    q.push(start);
    // visited[start] = 1;
    cnt++;
    route[start] = 1;

    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        // visited[now] = 1;

        // cout << "now " << now << endl;

        if (now == n)
        {
            ans = 1;
            // cout << cnt;
            cout << route[now];
            return;
        }

        for (int i = 0; i < path[now].size(); i++)
        {
            int next = path[now][i];
            // if (!visited[next])
            if (!route[next])
            {
                q.push(next);
                // visited[next] = 1;
                route[next] = route[now] + 1;
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
    }
}