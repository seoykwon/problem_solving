#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct lumber
{
    int x1, x2, y;
    int num;
};

vector<lumber> lumbers;
int parent[100001];

int Find(int A)
{
    if (A == parent[A])
        return A;

    return parent[A] = Find(parent[A]);
}

void Union(int A, int B)
{
    int rootA = Find(A);
    int rootB = Find(B);

    if (rootA == rootB)
        return;

    parent[rootB] = rootA;
}

// 비교군을 끝나는 시점으로 해야 함. 회의실 배정처럼. 시작점으로 정렬하면 제대로 유니온이 안될 수 있음.
bool cmp(lumber a, lumber b)
{
    if (a.x1 == b.x1)
        return a.x2 < b.x2;
    return a.x1 < b.x1;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < N; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < N; i++)
    {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;

        lumbers.push_back({x1, x2, y, i + 1});
    }
    sort(lumbers.begin(), lumbers.end(), cmp);

    int curX2 = lumbers[0].x2;

    // use union find. if lumbers are connected, unionize.
    for (int i = 1; i < N; i++)
    {
        lumber a = lumbers[i];

        if (a.x1 <= curX2)
        {
            Union(a.num, lumbers[i - 1].num);
        }
        curX2 = max(curX2, lumbers[i].x2);
        // 이 부분 구현을 안 하면 틀림
        // x2값을 맥스로 계속 유지해야 함
        // 바로 전 통나무랑 지금 통나무만 비교하면 안 됨.
        // 디버깅 할 때 유의하기
    }

    for (int i = 0; i < Q; i++)
    {
        int a, b;
        cin >> a >> b;

        int rootA = Find(a);
        int rootB = Find(b);

        if (rootA == rootB)
        {
            cout << 1 << '\n';
        }
        else
        {
            cout << 0 << '\n';
        }
    }
}