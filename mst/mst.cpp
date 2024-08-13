// spanning tree
// the number of nodes: 9
// the number of lines: 8
// Spanning tree: connected N nodes using N-1 lines (신장 트리)

// 가중치가 최소인 신장트리
// = Minimum spanning tree

// 그래프 내에 여러개의 신장 트리가 있을 수 있다
// 그래프 & 트리의 차이점
/*
트리는 특정 노드 간의 경로가 유일한 그래프. 무방향 간선과 사이클이 없음
점 (노드)
선
*/

// // 1. 데이터를 저장
// struct Edge
// {
//     int A, B, cost;
// };
// // 2. Edge 정렬
// sort(edges, edges + cntEdge);

// // 3. 하나씩 연결한다
// // Union Find를 활용해서 같은 그룹인지를 판별한다
// // 같은 그룹이면 연결하지 않는다
// // 다른 그룹이면 Union(A, B)

#include <iostream>
#include <algorithm>
using namespace std;

/*
9 13
1 2 1
2 3 13
3 4 17
1 6 21
3 5 82
5 4 99
4 8 6
5 6 20
5 7 57
4 7 15
8 9 31
6 7 32
7 9 3
*/

struct Edge
{
    int A, B;
    int cost;
    bool operator<(Edge right) const
    {
        if (cost < right.cost)
            return true;
        if (cost > right.cost)
            return false;

        if (A < right.A)
            return true;
        if (A > right.A)
            return false;

        if (B < right.B)
            return true;
        if (B > right.B)
            return false;

        return false;
    }
};

int parent[20];
Edge edges[20];

int Find(int A)
{
    if (A == parent[A])
        return A;
    // int root = Find(parent[A]);
    // parent[A] = root; // root & direct connection
    // return root;

    return parent[A] = Find(parent[A]);
}

void Union(int A, int B)
{
    int rootA = Find(A);
    int rootB = Find(B);

    if (rootA == rootB)
        return;
    parent[rootB] = rootA; // update the record to mark the same group
}

int main()
{

    // 1. save data
    int cntNode, cntEdge;
    cin >> cntNode >> cntEdge;

    for (int i = 0; i < cntEdge; i++)
    {
        int A, B;
        int cost;
        cin >> A >> B >> cost;
        edges[i] = {A, B, cost};
    }

    // 2. sort Edge in ascending order
    sort(edges, edges + cntEdge);

    // extra 1. setting parent
    for (int i = 1; i <= cntNode; i++)
    {
        parent[i] = i;
    }

    int sum = 0;
    // 3. connect one by one
    for (int i = 0; i < cntEdge; i++)
    {
        Edge now = edges[i]; // choose the smallest weighted edge that is located in the front
        if (Find(now.A) == Find(now.B))
            continue;
        Union(now.A, now.B); // 하나씩 연결
        sum += now.cost;
    }

    // Define whether they are in the same group by using Union-Find
    cout << sum;
    int de = -1;

    return 0;
}