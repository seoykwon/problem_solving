// #include <iostream>
// #include <queue>
// #include <vector>

// using namespace std;

// struct Edge
// {
//     int to;
//     int cost;

//     bool operator<(Edge right) const
//     {
//         if (cost < right.cost)
//             return false;
//         if (cost > right.cost)
//             return true;
//         return false;
//     }
// };

// vector<Edge> v[1001];
// int visited[1001] = {
//     0,
// };
// char gender[1001];
// int N, M;

// int prim(int start)
// {
//     priority_queue<Edge> pq;
//     pq.push({start, 0});
//     int cnt = 0;
//     int totalcost = 0;

//     while (!pq.empty())
//     {
//         Edge now = pq.top();
//         pq.pop();

//         if (visited[now.to])
//             continue;
//         visited[now.to] = 1;
//         cnt++;
//         totalcost += now.cost;

//         for (int i = 0; i < v[now.to].size(); i++)
//         {
//             Edge next = v[now.to][i];

//             if (visited[next.to])
//                 continue;

//             pq.push({next.to, next.cost});
//         }
//     }
//     if (cnt == N)
//     {
//         return totalcost;
//     }
//     return -1;
// }

// int main()
// {
//     // freopen("input.txt", "r", stdin);
//     cin >> N >> M;

//     for (int i = 1; i <= N; i++)
//     {
//         char sex;
//         cin >> sex;

//         gender[i] = sex;
//     }

//     for (int i = 0; i < M; i++)
//     {
//         int from, to, cost;
//         cin >> from >> to >> cost;

//         if (gender[from] == gender[to])
//             continue;

//         v[from].push_back({to, cost});
//         v[to].push_back({from, cost});
//     }

//     cout << prim(1);
// }

// ################### kruskal #######################
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge
{
    int from;
    int to;
    int cost;
};

bool cmp(Edge a, Edge b)
{
    if (a.cost < b.cost)
        return true;
    if (a.cost > b.cost)
        return false;
    return false;
}

int N, M;
int parent[1001];
Edge edges[10001]; // indexing 조심하기!!! 이것 때문에 디버깅 해야 했음 (runtime error가 나오면 거의 대부분 인덱싱 문제임)
char gender[1001];

int Find(int node)
{
    if (node == parent[node])
        return node;

    return parent[node] = Find(parent[node]);
}

void Union(int a, int b)
{
    int rootA = Find(a);
    int rootB = Find(b);

    if (rootA == rootB)
        return;

    parent[rootB] = rootA;
}

int kruskal()
{
    int totalcost = 0;
    int cntEdge = 0;
    sort(edges, edges + M, cmp);

    int validEdges = 0;
    for (int i = 0; i < M; i++)
    {
        if (gender[edges[i].from] != gender[edges[i].to])
            validEdges++;
    }

    if (validEdges < N - 1)
        return -1;

    for (int i = 0; i < M; i++)
    {
        Edge now = edges[i];
        if (Find(now.from) == Find(now.to))
            continue;
        if (gender[now.from] == gender[now.to])
            continue;
        totalcost += now.cost;
        cntEdge++;
        Union(now.from, now.to);

        if (cntEdge == N - 1)
            break;
    }
    if (cntEdge == N - 1)
    {
        return totalcost;
    }
    return -1;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        char sex;
        cin >> sex;

        gender[i] = sex;

        // parent 초기화 해주기!!!!! 이거 때문에 디버깅 해야 했음
        parent[i] = i;
    }

    int originalM = M;
    int edgeCnt = 0;
    for (int i = 0; i < originalM; i++)
    {
        int from, to, cost;

        cin >> from >> to >> cost;

        if (gender[from] == gender[to])
            continue;

        edges[edgeCnt++] = {from, to, cost};
    }
    M = edgeCnt;

    cout << kruskal();
}

// #################### kruskal with better time complexity #######################
// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// struct Edge
// {
//     int a, b, cost;
// };

// bool cmp(Edge left, Edge right)
// {
//     if (left.cost < right.cost)
//         return true;
//     if (left.cost > right.cost)
//         return false;
//     return false;
// }

// int N, M;
// int parent[1001];
// char gender[1001];
// vector<Edge> v;

// int Find(int now)
// {
//     if (now == parent[now])
//         return now;
//     return parent[now] = Find(parent[now]);
// }

// void Union(int a, int b)
// {
//     int pa = Find(a);
//     int pb = Find(b);
//     if (pa == pb)
//         return;
//     parent[pb] = pa;
// }

// int kruskal()
// {
//     sort(v.begin(), v.end(), cmp);
//     int sum = 0;
//     int cnt = 0;
//     for (int i = 0; i < v.size(); i++)
//     {
//         Edge now = v[i];
//         if (Find(now.a) == Find(now.b))
//             continue;
//         if (gender[now.a] == gender[now.b])
//             continue;
//         cnt++;
//         sum += now.cost;
//         Union(now.a, now.b);
//     }
//     if (cnt == N - 1)
//         return sum;
//     else
//         return -1;
// }

// int main()
// {
//     cin >> N >> M;

//     // parent 초기화
//     for (int i = 0; i <= N; i++)
//         parent[i] = i;

//     for (int i = 1; i <= N; i++)
//         cin >> gender[i];

//     for (int i = 0; i < M; i++)
//     {
//         int a, b, cost;
//         cin >> a >> b >> cost;
//         v.push_back({a, b, cost});
//     }

//     cout << kruskal();
// }