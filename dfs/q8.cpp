#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int to;
    int cost;
};

int N, r1, r2;
vector<Edge> path[100001];
int visited[100001] = {
    0,
};
int ans;

void dfs(int robot, int c, int mx)
{
    if (robot == r2)
    {
        ans = c - mx;
        return;
    }

    for (int i = 0; i < path[robot].size(); i++)
    {
        Edge next = path[robot][i];

        if (visited[next.to])
            continue;

        mx = max(next.cost, mx);
        visited[next.to] = 1;
        dfs(next.to, c + next.cost, mx);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N >> r1 >> r2;

    for (int i = 0; i < N - 1; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;

        path[from].push_back({to, cost});
        path[to].push_back({from, cost});
    }

    int maxCost = 0;
    dfs(r1, 0, maxCost);

    cout << ans << '\n';
}

// ################## 강사님 코드 #######################
#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int num;
    int cost;
};

int N;
vector<Edge> al[100001];
int s, e;
int visited[100001];
int sum = 0;
int MIN = 21e8;
int MAX = -21e8;

void dfs(int node, int dest)
{
    if (node == dest)
    {
        if (sum - MAX < MIN)
            MIN = sum - MAX;
        return;
    }

    for (int i = 0; i < al[node].size(); i++)
    {
        Edge next = al[node][i];
        if (visited[next.num] == 1)
            continue;
        sum += next.cost;
        visited[next.num] = 1;
        int temp = MAX;
        if (next.cost > MAX)
            MAX = next.cost;
        dfs(next.num, e);
        visited[next.num] = 0;
        sum -= next.cost;
        MAX = temp;
    }
}

int main()
{
    cin >> N >> s >> e;
    for (int i = 0; i < N - 1; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        al[from].push_back({to, cost});
        al[to].push_back({from, cost});
    }
    visited[s] = 1;
    dfs(s, e);
    if (MIN == 21e8)
        cout << 0;
    else
        cout << MIN;
}