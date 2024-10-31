#include <iostream>
#include <algorithm>

using namespace std;

struct Edge
{
    int from;
    int to;
    int cost;

    bool operator<(Edge right) const
    {
        if (cost < right.cost)
            return true;
        if (cost > right.cost)
            return false;
        return false;
    }
};

Edge edges[10001];
int parent[10001];

int Find(int A)
{
    if (A == parent[A])
    {
        return A;
    }
    return parent[A] = Find(parent[A]);
}

void Union(int A, int B)
{
    int rootA = Find(A);
    int rootB = Find(B);

    if (rootA == rootB)
        return;

    parent[rootB] = parent[rootA];
}

int main()
{
    int V, E;
    cin >> V >> E;

    for (int i = 0; i < E; i++)
    {
        int from, to, cost;

        cin >> from >> to >> cost;

        edges[i] = {from, to, cost};
    }

    sort(edges, edges + E);

    for (int i = 0; i <= V; i++)
    {
        parent[i] = i;
    }

    int sum = 0;

    // 3. connect one by one
    for (int i = 0; i < E; i++)
    {
        Edge now = edges[i]; // choose the smallest weighted edge that is located in the front
        if (Find(now.from) == Find(now.to))
            continue;
        Union(now.from, now.to); // 하나씩 연결
        sum += now.cost;
    }

    cout << sum;
}

// ############### KRUSKAL ################################

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int a, b, cost;
};

bool cmp(Edge a, Edge b)
{
    if (a.cost < b.cost)
        return true;
    if (a.cost > b.cost)
        return false;
    return false;
}

int parent[10001];
vector<Edge> v;
int ans = 0;

int Find(int node)
{
    if (node == parent[node])
        return node;

    return parent[node] = Find(parent[node]);
}

void Union(int a, int b)
{
    int pa = Find(a);
    int pb = Find(b);

    if (pa == pb)
        return;
    parent[pb] = pa;
}

void kruskal()
{
    sort(v.begin(), v.end(), cmp);

    for (int i = 0; i < v.size(); i++)
    {
        Edge now = v[i];
        if (Find(now.a) == Find(now.b))
            continue;
        ans += now.cost;
        Union(now.a, now.b);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        v.push_back({from, to, cost});
    }

    kruskal();
    cout << ans;
}

// ################### PRIM #############################

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
    int to;
    int cost;

    bool operator<(Edge next) const
    {
        if (cost < next.cost)
            return false;
        if (cost > next.cost)
            return true;
        return false;
    }
};

int N, M;
vector<Edge> al[10001];
int connected[100001];

int prim(int start)
{
    priority_queue<Edge> pq;
    pq.push({start, 0});

    int sum = 0;

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        if (connected[now.to] == 1)
            continue;

        connected[now.to] = 1;
        sum += now.cost;

        for (int i = 0; i < al[now.to].size(); i++)
        {
            Edge next = al[next.to][i];
            if (connected[next.to] == 1)
                continue;
            pq.push(next);
        }
    }
    return sum;
}

int main()
{
    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        al[from].push_back({to, cost});
        al[to].push_back({from, cost});
    }

    // start wherever you want
    cout << prim(1);
}