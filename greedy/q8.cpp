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

bool cmp(lumber a, lumber b)
{
    return a.x1 < b.x1;
}

int main()
{
    freopen("input.txt", "r", stdin);
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

    // use union find. if lumbers are connected, unionize.
    for (int i = 0; i < N - 1; i++)
    {
        lumber a = lumbers[i];
        lumber b = lumbers[i + 1];

        // union
        if (b.x1 <= a.x2)
        {
            Union(a.num, b.num);
        }
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