#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k, m;
int node[100001];
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
            node[tmp] = i;
        }
    }
}

void bfs(int start)
{
    queue<int> q;
    q.push(start);
    route[start] = 1;

    while (!q.empty())
    {
        int now = q.front();
        q.pop();
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