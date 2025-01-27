// solved 2025-01-27
// caution to 0-based index
// caution to overflow (usage of long long)

// #include <iostream>
// #include <vector>
// #include <climits>
// #include <cmath>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 1000000007;

int n, m, k;
vector<ll> v;
vector<ll> segTree;

ll build(int node, int start, int end)
{
    if (start == end)
    {
        return segTree[node] = v[start];
    }
    int mid = (start + end) / 2;
    ll left = build(2 * node, start, mid);
    ll right = build(2 * node + 1, mid + 1, end);

    return segTree[node] = (left * right) % MOD;
}

ll findMul(int node, int start, int end, int left, int right)
{
    if (right < start || left > end)
    {
        return 1; // neutral element for multiplication
    }

    if (left <= start && right >= end)
    {
        return segTree[node];
    }

    int mid = (start + end) / 2;
    ll leftmul = findMul(2 * node, start, mid, left, right);
    ll rightmul = findMul(2 * node + 1, mid + 1, end, left, right);

    return (leftmul * rightmul) % MOD;
}

void update(int node, int start, int end, int idx, ll value)
{
    if (start == end)
    {
        segTree[node] = value;
        v[start] = value;
        return;
    }

    int mid = (start + end) / 2;

    if (idx <= mid)
    {
        update(2 * node, start, mid, idx, value);
    }
    else
    {
        update(2 * node + 1, mid + 1, end, idx, value);
    }
    segTree[node] = (segTree[2 * node] * segTree[2 * node + 1]) % MOD;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n >> m >> k;

    v.resize(n);
    int height = (int)ceil(log2(n));
    int treesize = (1 << (height + 1));
    segTree.resize(treesize);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    build(1, 0, n - 1);
    int total = m + k;

    while (total--)
    {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == 1)
        {
            // change bth ordered number to c
            update(1, 0, n - 1, b - 1, c);
        }
        else if (a == 2)
        {
            // calculate multiplication from b to c
            ll ans = findMul(1, 0, n - 1, b - 1, c - 1);
            cout << ans << '\n';
        }
    }
    return 0;
}