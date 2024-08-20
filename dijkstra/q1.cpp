#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int num;
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

vector<Edge> v[20000];
int N, T;
int dist[20000];

void dijstra(int start)
{
    priority_queue<Edge> pq;

    pq.push({start, 0});

    for (int i = 0; i < N; i++)
    {
        dist[i] = 21e8;
    }

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

    if (dist[N - 1] != 21e8)
    {
        cout << dist[N - 1];
    }
    else
    {
        cout << "impossible";
    }
}

int main()
{
    cin >> N >> T;

    for (int i = 0; i < T; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;

        v[from].push_back({to, cost});
        // v[to].push_back({from, cost});
    }
    dijstra(0);
}