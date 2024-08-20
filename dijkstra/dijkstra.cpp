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
        // MIN HEAP // MAX HEAP "참" left < right
        //          //          "거짓" left < right
        if (cost < right.cost)
            return false;
        if (cost > right.cost)
            return true;

        return false;
    }
};

/*
9 12
0 1 7
0 2 12
1 4 9
1 3 42
2 3 31
2 7 27
3 4 27
3 6 8
7 6 16
4 5 42
5 6 20
6 8 3
*/
vector<Edge> alis[20];
int N, M;

int dist[20];
int visited[20]; //
void dijkstra(int start)
{
    // 초기 세팅 단계
    // 1. PQ준비
    priority_queue<Edge> pq;
    // 2. 시작 노드 삽입
    pq.push({start, 0});
    // 3. 정답 배열 초기화
    for (int i = 0; i < N; i++)
    {
        dist[i] = 21e8;
    }
    // 4. 시작노드의 정답을 기록 하고 진행
    dist[start] = 0;

    // 구현 단계
    while (!pq.empty())
    {

        // 1. PQ 에 top 에 있는 노드를 확인하고 추출(now 위치에 있다)
        Edge now = pq.top();
        pq.pop();

        /*	if (visited[now.num] == 1)continue;
            visited[now.num] = 1;*/
        // now 까지 나왔다라는 것은 거리가 확정된 것
        // 이후에 나오는 now들은 절대로 dist 에 기록된 값보다 더 작을 일이 없다~!!
        // 동일한 now.num 로 PQ에 다른 가중치로 등장할 수 있다.
        // 전에 이미 확정된 node 더 볼일 없다~!!
        if (dist[now.num] < now.cost)
            continue; // now.cost now까지의 누적 가중치

        // 2. now 에서 갈수 있는 next 후보 찾기
        for (int i = 0; i < alis[now.num].size(); i++)
        {
            Edge next = alis[now.num][i]; // next 후보 확인
            // 누적합 계산 필요~!
            int nextcost = dist[now.num] + next.cost;
            // now위치까지의 정답 + next 간선의 cost
            //							  > 누적해서 추가

            // 3. 갈 수 있는 next 후보들은 > 정답 배열에 저장되어 있는 next 기록과 비교해서
            //								visited 처리~!
            if (dist[next.num] <= nextcost)
                continue;
            //
            dist[next.num] = nextcost;     // 정답에 기록
                                           // 정답을 확정
            pq.push({next.num, nextcost}); // PQ에 등록
        }
    }
    for (int i = 0; i < N; i++)
    {
        cout << i << " 노드까지의 거리는 " << dist[i] << "\n";
    }
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
    dijkstra(0);
}