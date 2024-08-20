#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, K;
int A, B;

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

vector<Edge> v[1001];
int dist[1001];
int visited[1001] = {
    0,
};

void dijkstra(int start)
{
    priority_queue<Edge> pq;

    pq.push({start, 0});

    for (int i = 1; i <= N; i++)
    {
        dist[i] = 21e8;
        visited[i] = 0;
    }

    dist[start] = 0;

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();
        if (visited[now.num])
            continue;
        visited[now.num] = 1;

        for (auto next : v[now.num])
        {

            // for (int i = 0; i < v[now.num].size(); i++)
            // {
            //     Edge next = v[now.num][i];
            if (visited[next.num])
                continue;

            int nextcost = dist[now.num] + next.cost;

            if (dist[next.num] <= nextcost)
                continue;

            dist[next.num] = nextcost;

            pq.push({next.num, nextcost});
        }
    }

    cout << dist[B] << endl;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N >> M >> K;
    cin >> A >> B;

    for (int i = 0; i < M; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        v[from].push_back({to, cost});
        v[to].push_back({from, cost});

        // cout << from << " " << to << " " << cost << endl;
        // cout << to << " " << from << " " << cost << endl;
    }

    dijkstra(A);

    for (int i = 0; i < K; i++)
    {
        int year;
        cin >> year;

        for (int j = 1; j <= N; j++)
        {
            for (int k = 0; k < v[j].size(); k++)
            {
                Edge *now = &v[j][k];
                now->cost += year;
                // cout << j << " " << now.num << " " << now.cost << endl;
            }
        }
        // cout << endl;

        dijkstra(A);
    }
}