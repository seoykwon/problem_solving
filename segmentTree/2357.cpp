#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<int> numV;
vector<pair<int, int>> tree;

pair<int, int> init(int start, int end, int node)
{
    if (start == end)
        return tree[node] = {numV[start], numV[start]};

    int mid = (start + end) >> 1;

    pair<int, int> leftVal, rightVal;
    leftVal = init(start, mid, node << 1);
    rightVal = init(mid + 1, end, (node << 1) + 1);
    return tree[node] = {min(leftVal.first, rightVal.first), max(leftVal.second, rightVal.second)};
}

pair<int, int> find(int start, int end, int node, int left, int right)
{
    if (start > right || end < left)
        return {INT_MAX, 0};

    if (start >= left && end <= right)
        return tree[node];

    int mid = (start + end) >> 1;
    pair<int, int> leftVal, rightVal;
    leftVal = find(start, mid, node << 1, left, right);
    rightVal = find(mid + 1, end, (node << 1) + 1, left, right);
    return {min(leftVal.first, rightVal.first), max(leftVal.second, rightVal.second)};
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int N, M;
    cin >> N >> M;
    tree = vector<pair<int, int>>((N << 2));
    numV.push_back(0);
    for (int i = 0; i < N; ++i)
    {
        int num;
        cin >> num;
        numV.push_back(num);
    }
    init(1, N, 1);
    for (int i = 0; i < M; ++i)
    {
        int l, r;
        cin >> l >> r;
        auto cur = find(1, N, 1, l, r);
        cout << cur.first << " " << cur.second << "\n";
    }
}