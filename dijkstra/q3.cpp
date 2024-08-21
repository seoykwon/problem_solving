#include <iostream>
#include <queue>
#include <vector>

using namespace std;

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

int n, m, p;
vector<Edge> v[1001];
int maxCnt = 0;
int dist[1001] = {
    0,
};
int arr[1001] = {
    0,
};

void dijkstra(int start)
{
    // 초기 세팅 단계
    // 1. PQ준비
    priority_queue<Edge> pq;
    // 2. 시작 노드 삽입
    pq.push({start, 0});
    // 3. 정답 배열 초기화
    for (int i = 0; i <= n; i++)
    {
        dist[i] = 21e8;
        // arr[i + 1] = 21e8;
    }
    // 4. 시작노드의 정답을 기록 하고 진행
    dist[start] = 0;

    // 구현 단계
    while (!pq.empty())
    {

        Edge now = pq.top();
        pq.pop();

        if (dist[now.to] < now.cost)
            continue; // now.cost now까지의 누적 가중치

        // if (now.to == p && arr[start] > dist[now.to])
        // {
        //     arr[start] = dist[now.to];
        //     // return;
        // }

        for (int i = 0; i < v[now.to].size(); i++)
        {
            Edge next = v[now.to][i]; // next 후보 확인

            int nextcost = dist[now.to] + next.cost;

            if (dist[next.to] <= nextcost)
                continue;

            dist[next.to] = nextcost;     // 정답에 기록
                                          // 정답을 확정
            pq.push({next.to, nextcost}); // PQ에 등록
        }
    }
}

void dijkstra2(int start)
{
    // 초기 세팅 단계
    // 1. PQ준비
    priority_queue<Edge> pq;
    // 2. 시작 노드 삽입
    pq.push({start, 0});
    // 3. 정답 배열 초기화
    for (int i = 0; i <= n; i++)
    {
        dist[i] = 21e8;
    }
    // 4. 시작노드의 정답을 기록 하고 진행
    dist[start] = 0;

    // 구현 단계
    while (!pq.empty())
    {

        Edge now = pq.top();
        pq.pop();

        if (dist[now.to] < now.cost)
            continue; // now.cost now까지의 누적 가중치

        for (int i = 0; i < v[now.to].size(); i++)
        {
            Edge next = v[now.to][i]; // next 후보 확인

            int nextcost = dist[now.to] + next.cost;

            if (dist[next.to] <= nextcost)
                continue;

            dist[next.to] = nextcost;     // 정답에 기록
                                          // 정답을 확정
            pq.push({next.to, nextcost}); // PQ에 등록
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n >> m >> p;

    for (int i = 0; i < m; i++)
    {
        int from, to, cost;

        cin >> from >> to >> cost;

        v[from].push_back({to, cost});
    }

    for (int i = 1; i <= n; i++)
    {
        dijkstra(i);
        arr[i] = dist[p];
    }
    dijkstra2(p);

    for (int i = 1; i <= n; i++)
    {
        int check = arr[i] + dist[i];
        if (maxCnt < check)
        {
            maxCnt = check;
        }
    }

    cout << maxCnt;
}