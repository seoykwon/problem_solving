// #include <iostream>
// #include <algorithm>
// #include <vector>
// #include <queue>

// using namespace std;

// struct pos
// {
//     int y, x;
// };

// struct Edge
// {
//     int from;
//     int to;
//     int cost;

//     // bool operator<(Edge right) const
//     // {
//     //     if (cost < right.cost)
//     //         return false;
//     //     if (cost > right.cost)
//     //         return true;
//     //     return false;
//     // }
// };

// bool cmp(Edge a, Edge b)
// {
//     if (a.cost < b.cost)
//         return true;
//     if (a.cost > b.cost)
//         return false;
//     return false;
// }

// pos edges[2001];
// int parent[2001 * 2];
// vector<Edge> v;
// int ans = 0;

// int Find(int node)
// {
//     if (node == parent[node])
//     {
//         return node;
//     }

//     return parent[node] = Find(parent[node]);
// }

// void Union(int a, int b)
// {
//     int rootA = Find(a);
//     int rootB = Find(b);

//     if (rootA == rootB)
//         return;

//     parent[rootB] = rootA;
// }

// void kruskal(int N)
// {
//     sort(v.begin(), v.end(), cmp);
//     int edgesUsed = 0;

//     for (int i = 0; i < v.size(); i++)
//     {
//         Edge now = v[i];

//         if (Find(now.from) == Find(now.to))
//             continue;

//         ans += now.cost;
//         Union(now.from, now.to);
//         edgesUsed++;
//         // MST가 완성되면 룹에서 꺼내줘야 함. time limit exceed
//         if (edgesUsed == N - 1)
//             break;
//     }

//     // loop을 돌려서 모든 밭이 이어져 있는지 확인하면 시간이 추가됨
//     // 만약 모든 밭을 잇는 관개 시스템 설치 불가 -1
//     if (edgesUsed != N - 1)
//     {
//         ans = -1;
//     }
// }

// int main()
// {
//     // freopen("input.txt", "r", stdin);
//     int N, K;
//     cin >> N >> K;

//     for (int i = 0; i < N; i++)
//     {
//         parent[i] = i;
//     }

//     for (int i = 0; i < N; i++)
//     {
//         int y, x;
//         cin >> y >> x;

//         edges[i].y = y;
//         edges[i].x = x;
//     }

//     // calculate each edge's cost
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             if (i == j)
//                 continue;

//             pos a = edges[i];
//             pos b = edges[j];

//             int dist = (a.y - b.y) * (a.y - b.y) + (a.x - b.x) * (a.x - b.x);
//             if (dist < K)
//                 continue;

//             // cout << "adding into the vector!" << endl;
//             v.push_back({i, j, dist});
//         }
//     }

//     kruskal(N);

//     cout << ans;
// }

// ####################### PRIM ################################
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct pos
{
    int y;
    int x;
    int num;
};

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

int N, K;
vector<pos> position;
vector<Edge> v[2001];

void input()
{
    freopen("input.txt", "r", stdin);
    cin >> N >> K;

    for (int i = 0; i < N; i++)
    {
        int y, x;
        cin >> y >> x;

        position.push_back({y, x, i});
    }
}

void createEdges()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;

            pos a = position[i];
            pos b = position[j];

            int dist = (a.y - b.y) * (a.y - b.y) + (a.x - b.x) * (a.x - b.x);

            if (dist < K)
                continue;

            v[a.num].push_back({b.num, dist});
            v[b.num].push_back({a.num, dist});
        }
    }
}

int prim(int start)
{
    priority_queue<Edge> pq;
    pq.push({start, 0});

    int connected[2001] = {
        0,
    };
    int sum = 0;
    int cnt = 0;

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        if (connected[now.to] == 1)
            continue;
        connected[now.to] = 1;

        sum += now.cost;
        cnt++;

        for (int i = 0; i < v[now.to].size(); i++)
        {
            Edge next = v[now.to][i];

            if (connected[next.to] == 1)
                continue;
            pq.push(next);
        }
    }
    if (cnt == N)
    {
        return sum;
    }
    return -1;
}

int main()
{
    input();

    createEdges();

    cout << prim(0);
}