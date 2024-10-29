// #include <iostream>
// #include <vector>
// #include <queue>

// using namespace std;

// struct Edge
// {
//     int num;
//     int cost;
//     int cities;

//     bool operator<(Edge right) const
//     {
//         if (cost < right.cost)
//         {
//             return false;
//         }
//         if (cost > right.cost)
//         {
//             return true;
//         }
//         // 만약 최소 비용으로 이동할 수 있는 경로가 2개 이상이라면,
//         // 방문해야 하는 도시의 개수가 최소인 경로를 출력한다.
//         if (cities < right.cities)
//         {
//             return false;
//         }
//         if (cities > right.cities)
//         {
//             return true;
//         }
//         return false;
//     }
// };

// int N, M;
// vector<Edge> v[101];
// int dist[101];

// void dijkstra(int start, int end)
// {
//     priority_queue<Edge> pq;
//     fill(dist, dist + N + 1, 21e8);
//     dist[start] = 0;
//     pq.push({start, 0, 1});

//     while (!pq.empty())
//     {
//         Edge now = pq.top();
//         pq.pop();

//         if (now.num == end)
//         {
//             cout << now.cost << " " << now.cities << endl;
//             return;
//         }

//         if (dist[now.num] < now.cost)
//             continue;

//         for (Edge next : v[now.num])
//         {
//             int nextcost = dist[now.num] + next.cost;

//             if (dist[next.num] > nextcost)
//             {
//                 dist[next.num] = nextcost;
//                 pq.push({next.num, next.cost, now.cities + 1});
//             }
//         }
//     }

//     cout << "-1" << endl;
// }

// int main()
// {
//     freopen("input.txt", "r", stdin);
//     cin >> N >> M;

//     for (int i = 0; i < M; i++)
//     {
//         int from, to, base, extra, time;
//         cin >> from >> to >> base >> extra >> time;

//         int cost = 0;
//         cost += base;
//         if (time > 10)
//         {
//             int rem = time - 10;
//             cost += (rem * extra);
//         }

//         v[from].push_back({to, cost, 1});
//     }

//     dijkstra(1, N);
// }

/*
1. dist 배열을 2차원으로 선언하여 도시의 방문 수까지 고려하도록 변경해야 함:
    기존 코드에서는 dist 배열이 단일 배열로 선언되어 있어, 단일 경로만 저장하게 됩니다.
    하지만 최소 비용 경로가 여러 개 있을 수 있으며, 최소 도시 개수를 고려해야 합니다.
    따라서 dist를 비용과 도시 개수를 모두 고려하는 2차원 배열로 선언합니다.

2. 도로 이동 비용 계산 로직 수정:
    도로 이동 시간이 10분 이하인지에 따라 기본 요금만 지불하거나 추가 요금을 계산하는 로직을
    명확히 구현합니다.

3. 다익스트라 알고리즘 내에서 도시 개수를 업데이트하도록 수정:
    기존 코드에서는 도착 도시에 대한 최소 비용만 저장했지만, 경로에 포함된 도시 개수 또한 관리하도록
    업데이트합니다.
*/

/*
fill 함수

#include <algorithm>
fill(채울 자료구조의 시작 iterator, 끝 iterator + 1, 채울 값)
*/

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

    bool operator<(const Edge &other) const
    {
        if (cost == other.cost)
        {
            return cities > other.cities; // 비용이 같을 때는 도시 개수 최소 경로 선택
        }
        return cost > other.cost; // 비용이 낮은 것 우선
    }
};

int N, M;
vector<Edge> adj[101];
int dist[101][101]; // dist[i][j]: i번 도시에 j개의 도시를 거쳐서 도달할 때 최소 비용

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
            int next_cost = now.cost + next.cost;
            int next_cities = now.cities + 1;

            if (next_cities <= N && dist[next.num][next_cities] > next_cost)
            {
                dist[next.num][next_cities] = next_cost;
                pq.push({next.num, next_cost, next_cities});
            }
        }
    }

    cout << "-1" << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
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

/*****************************************************
 * 강사님 코드
 ***************************************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int num;
    int cost;
    int cnt;
};

int n, m;
vector<Edge> v[101];
int DAT[101];

bool operator<(Edge a, Edge b)
{
    if (a.cost < b.cost)
        return false;
    if (a.cost > b.cost)
        return true;
    return false;
}

void dijkstra(int node)
{
    priority_queue<Edge> pq;
    pq.push({node, 0, 1});

    int dist[101] = {
        0,
    };
    for (int i = 0; i <= n; i++)
    {
        dist[i] = 21e8;
        DAT[i] = 21e8;
    }
    dist[node] = 0;

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        if (dist[now.num] < now.cost)
            continue;

        if (now.cnt < DAT[now.num])
            DAT[now.num] = now.cnt;

        for (int i = 0; i < v[now.num].size(); i++)
        {
            Edge next = v[now.num][i];
            int nextcost = dist[now.num] + next.cost;
            if (dist[next.num] < nextcost)
                continue;
            dist[next.num] = nextcost;
            pq.push({next.num, nextcost, now.cnt + 1});
        }
    }

    if (dist[n] == 21e8)
        cout << "-1" << endl;
    else
        cout << dist[n] << " " << DAT[n];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int from, to, basecost, extracost, time;
        cin >> from >> to >> basecost >> extracost >> time;
        // 단방향
        int cost = 0;
        if (time - 10 > 0)
            cost = basecost + (time - 10) * extracost;
        else
            cost = basecost;
        v[from].push_back({to, cost, 0});
    }
    dijkstra(1);
}

/*
1. 코스트와 도시 수 비교 방법
강사님 코드: 비용이 낮은 순서로 우선순위 정렬하지만, 동일 비용일 때 도시 수는 고려하지 않음.
대신 DAT 배열을 사용해 경로에서 현재 도시를 방문한 횟수를 최소로 유지합니다.
다만 이 접근은 동일 비용 경로를 중복 탐색할 수 있어 비효율적일 수 있습니다.

강사님 코드는 별도의 DAT 배열을 사용해 방문 수를 관리하지만, 중복 탐색이 발생할 수 있습니다.

*/