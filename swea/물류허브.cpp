#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

// 간선 정보 저장용 구조체
struct E
{
    int end, weight;

    E(int end, int weight) : end(end), weight(weight) {}

    // 최소 힙을 사용하기 위해 weight를 기준으로 오름차순 우선순위 설정
    bool operator<(const E &other) const
    {
        return weight > other.weight;
    }
};

// 도시 번호를 인덱스로 매핑 (예: 100 -> 0, 101 -> 1 ...)
unordered_map<int, int> id2idx;

// 정방향과 역방향 인접 리스트
vector<vector<E>> fwdList, revList;

// 도시 수
int Num;

// 다익스트라 알고리즘: 단일 출발점 최단 거리 구함
vector<int> dijkstra(const vector<vector<E>> &fwdList, int mHub)
{
    int X = id2idx[mHub];               // 허브 도시의 인덱스
    vector<bool> visit(Num, false);     // 방문 여부
    vector<int> distance(Num, INT_MAX); // 최단 거리 초기화

    priority_queue<E> pq;
    pq.emplace(X, 0); // 시작점에서 시작
    distance[X] = 0;

    while (!pq.empty())
    {
        E curNode = pq.top();
        pq.pop();
        int cur = curNode.end;

        if (visit[cur])
            continue;
        visit[cur] = true;

        for (const E &n : fwdList[cur])
        {
            // 더 짧은 경로 발견 시 업데이트
            if (distance[n.end] > distance[cur] + n.weight)
            {
                distance[n.end] = distance[cur] + n.weight;
                pq.emplace(n.end, distance[n.end]);
            }
        }
    }

    return distance; // 시작점으로부터 각 노드까지의 최단 거리
}

// 그래프 초기화 함수
int init(int N, int sCity[], int eCity[], int mCost[])
{
    id2idx.clear();
    int idx = 0;

    // 도시 번호를 0부터 연속된 인덱스로 매핑
    for (int i = 0; i < N; i++)
    {
        if (id2idx.find(sCity[i]) == id2idx.end())
            id2idx[sCity[i]] = idx++;
        if (id2idx.find(eCity[i]) == id2idx.end())
            id2idx[eCity[i]] = idx++;
    }
    Num = id2idx.size(); // 전체 도시 수

    fwdList.resize(Num);
    revList.resize(Num);

    for (int i = 0; i < Num; i++)
    {
        fwdList[i].clear();
        revList[i].clear();
    }

    // 간선 정보 추가 (정방향과 역방향)
    for (int i = 0; i < N; i++)
    {
        fwdList[id2idx[sCity[i]]].emplace_back(id2idx[eCity[i]], mCost[i]);
        revList[id2idx[eCity[i]]].emplace_back(id2idx[sCity[i]], mCost[i]);
    }

    return Num; // 도시 수 반환
}

// 간선 추가 함수
void add(int sCity, int eCity, int mCost)
{
    fwdList[id2idx[sCity]].emplace_back(id2idx[eCity], mCost);
    revList[id2idx[eCity]].emplace_back(id2idx[sCity], mCost);
}

// mHub 도시를 허브로 했을 때의 왕복 비용 합산
int cost(int mHub)
{
    vector<int> distance = dijkstra(fwdList, mHub);    // 허브 -> 다른 도시
    vector<int> revdistance = dijkstra(revList, mHub); // 다른 도시 -> 허브

    int sum = 0;
    for (int i = 0; i < Num; i++)
    {
        sum += distance[i];    // 허브에서 출발
        sum += revdistance[i]; // 허브로 도착
    }

    return sum; // 전체 왕복 최단 거리의 합
}
