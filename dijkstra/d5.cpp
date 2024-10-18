#include <iostream>
#include <queue>
#include <vector>

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

vector<Edge> v[5001];
int V, E, P;
int dist[5001];

void dijkstra(int start, int V)
{
    priority_queue<Edge> pq;
    fill(dist, dist + V + 1, 21e8);
    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        if (dist[now.num] < now.cost)
            continue;

        for (Edge next : v[now.num])
        {
            int nextcost = dist[now.num] + next.cost;

            if (dist[next.num] > nextcost)
            {
                dist[next.num] = nextcost;
                pq.push({next.num, nextcost});
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> V >> E >> P;

    for (int i = 0; i < E; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;

        v[from].push_back({to, cost});
        v[to].push_back({from, cost});
    }

    dijkstra(1, V);
    int directdist = dist[V];

    dijkstra(1, P);
    int distp = dist[P];

    dijkstra(P, V);
    int distv = dist[V];

    if (distp + distv == directdist)
    {
        cout << "OKAY";
    }
    else
    {
        cout << "SORRY";
    }

    return 0;
}