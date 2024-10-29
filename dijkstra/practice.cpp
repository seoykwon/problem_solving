#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

struct Edge
{
    int num;
    int cost;
    int cities;

    bool operator<(const Edge &right) const
    {
        if (cost == right.cost)
        {
            return cities > right.cities;
        }
        return cost > right.cost;
    }
};

int N, M;
vector<Edge> adj[101];
int dist[101][101];

void dijkstra(int start, int end)
{
    priority_queue<Edge> pq;
    fill(&dist[0][0], &dist[0][0] + 101 * 101, INT_MAX);
    dist[start][1] = 0;
    pq.push({start, 0, 1});

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        if (now.num == end)
        {
            cout << now.cost << " " << now.cities << endl;
            return;
        }

        if (dist[now.num][now.cities] < now.cost)
            continue;

        for (Edge next : adj[now.num])
        {
            int nextcost = now.cost + next.cost;
            int nextcity = now.cities + 1;

            if (nextcity <= N && dist[next.num][nextcity] > nextcost)
            {
                dist[next.num][next.city] = nextcost;
                pq.push({next.num, nextcost, nextcity});
            }
        }
    }

    cout << "-1" << endl;
}

int main()
{
    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int from, to, base, extra, time;
        cin >> from >> to >> base >> extra >> time;

        int cost = base;
        if (time > 10)
        {
            cost += (time - 10) * extra;
        }

        adj[from].push_back({to, cost, 1});
    }

    dijkstra(1, N);

    return 0;
}