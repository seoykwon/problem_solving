#include <iostream>
#include <queue>

using namespace std;

int c, p, k, a, b;

struct Edge
{
    int to;
    int cost;
    bool operator<(Edge right) const
    {
        if (cost < right.cost)
            return false;
        if (cost > right.cost)
            return true;
        return false;
    }
};

vector<Edge> v[100001];
int dist[100001] = {
    0,
};

int dijkstra(int start, int dest)
{
    priority_queue<Edge> pq;

    for (int i = 1; i <= p; i++)
    {
        dist[i] = 21e8;
    }

    dist[start] = 0;

    pq.push({start, 0});

    while (!pq.empty())
    {
        // cout << "not empty" << endl;
        Edge now = pq.top();
        pq.pop();

        if (dist[now.to] < now.cost)
            continue;

        dist[now.to] = now.cost;

        for (int i = 0; i < v[now.to].size(); i++)
        {
            Edge next = v[now.to][i];

            int nextcost = dist[now.to] + next.cost;

            if (dist[next.to] < nextcost)
                continue;

            dist[next.to] = nextcost;

            pq.push({next.to, nextcost});
        }
    }
    return dist[dest];
}

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> c >> p >> k >> a >> b;

    for (int i = 0; i < c; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;

        v[from].push_back({to, cost});
        v[to].push_back({from, cost});
    }

    int first = dijkstra(k, a);
    int second = dijkstra(a, b);

    int third = dijkstra(k, b);
    int fourth = dijkstra(b, a);

    // int case1 = first + third;
    int case2 = first + second;
    int case3 = third + fourth;

    int min = case2;
    // if (min > case2)
    // {
    //     min = case2;
    // }
    if (min > case3)
    {
        min = case3;
    }

    cout << min;
}

// #######################################################################
// example code

/*
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int c, p, start, dest1, dest2;

struct Edge
{
    int num, cost;
};

bool operator<(Edge a, Edge b)
{
    return a.cost > b.cost;
}

vector<Edge> v[100001];

void dijkstra(int start, int dist[])
{
    priority_queue<Edge> pq;
    pq.push({start, 0});
    dist[start] = 0;
    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();
        if (dist[now.num] < now.cost)
            continue;
        for (int i = 0; i < v[now.num].size(); i++)
        {
            Edge next = v[now.num][i];
            int nextcost = dist[now.num] + next.cost;
            if (dist[next.num] <= nextcost)
                continue;
            dist[next.num] = nextcost;
            pq.push({next.num, nextcost});
        }
    }
}

int dist1[100001];
int dist2[100001];

int main()
{
    cin >> c >> p >> start >> dest1 >> dest2;
    for (int i = 0; i <= p; i++)
    {
        dist1[i] = 2134567890;
        dist2[i] = 2134567890;
    }
    for (int i = 0; i < c; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        v[from].push_back({to, cost});
        v[to].push_back({from, cost});
    }
    dijkstra(dest1, dist1);
    dijkstra(dest2, dist2);
    int ans = min(dist1[start], dist2[start]) + dist1[dest2];
    cout << ans;
}
*/