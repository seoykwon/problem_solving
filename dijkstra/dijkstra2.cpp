#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
7 8
0 1 9
1 2 23
0 2 21
3 4 13
2 4 5
2 6 12
6 5 25
4 5 79
*/

int N, M;
struct Edge
{
    int to; // 해당 간선이 어디에 연결될 것인가?
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
vector<Edge> alis[20];
int dist[20];
void dijkstra(int start)
{

    // 세팅
    // 1.PQ준비
    priority_queue<Edge> pq;
    // 2.dist  배열 초기화
    for (int i = 0; i < N; i++)
        dist[i] = 21e8;
    // 3.dist 시작점 기록
    dist[start] = 0;
    // 4.PQ 시작 노드 삽입
    pq.push({start, 0});

    // 구현
    // 큐가 비기 전까지 진행
    while (!pq.empty())
    {
        // 1.큐에서 top 최소값을 가진 간선을 추출(now위치다)
        Edge now = pq.top();
        pq.pop();
        int nowNode = now.to;
        // 처리2~!
        if (dist[nowNode] < now.cost)
            continue;

        // 2. next간선
        for (int i = 0; i < alis[nowNode].size(); i++)
        {
            // 3. next로 진행할 때의 가중치 값을 누적해서 계산
            Edge next = alis[nowNode][i]; // next 간선들을 하나씩 확인
            int nextcost = dist[nowNode] + next.cost;
            if (nextcost >= dist[next.to])
                continue; // visited
            // 4. dist 배열에 기록 후, next PQ에 등록
            dist[next.to] = nextcost;
            pq.push({next.to, nextcost});

            // 처리1~!!
        }
    }

    for (int i = 0; i < N; i++)
        cout << i << "까지의 최단 거리는 " << dist[i] << "\n";
}

void dijkstra_for(int start)
{
    // 1. 정답 배열 초기화
    for (int i = 0; i < N; i++)
        dist[i] = 21e8;
    // 2. 정답배열에 시작노드 정보 기록
    dist[start] = 0;
    // 3. visited 배열
    int visited[100] = {
        0,
    };

    // dijkstra처럼 진행.
    // 노드의 개수만큼 반복 ->한번 돌때마다 최단거리 확정
    // 모든 노드에 대해서 진행, 즉, 모든 노드에 대해 최단거리가 확정 될때까지 진행,
    for (int i = 0; i < N; i++)
    {
        // 가중치가 가장 작은 간선의 값과 노드
        int mincost = 21e8;
        int now = -1;

        for (int j = 0; j < N; j++)
        {
            // 처리1
            if (visited[j] == 1)
                continue;
            // 처리2
            if (dist[j] >= mincost)
                continue;
            mincost = dist[j]; // mincost 최단 거리를 가진 누적 cost
            now = j;           // 최소값을 가지고 있는 now에서 연결될 노드
        }
        // now에서의 최단 거리임을 확정 코드 필수~!!
        // 처리3 visited 처리
        visited[now] = 1; // 확정지었다~!!

        for (int j = 0; j < alis[now].size(); j++)
        {
            Edge next = alis[now][j]; // 다음 후보들 찾기
            int nextcost = dist[now] + next.cost;

            if (dist[next.to] <= nextcost)
                continue;
            dist[next.to] = nextcost;
        }
    }
    for (int i = 0; i < N; i++)
        cout << i << "까지의 최단 거리는 " << dist[i] << "\n";
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        alis[from].push_back({to, cost});
        alis[to].push_back({from, cost});
    }
    // dijkstra(0);
    dijkstra_for(0);
}