#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> a;
vector<long long> sumTree;

// initialize segment tree
void init(int node, int nodeLeft, int nodeRight)
{
    if (nodeLeft == nodeRight)
    {
        sumTree[node] = a[nodeLeft];
        return;
    }

    int mid = (nodeLeft + nodeRight) / 2;

    init(node * 2, nodeLeft, mid);
    init(node * 2 + 1, mid + 1, nodeRight);

    sumTree[node] = sumTree[node * 2] + sumTree[node * 2 + 1];
}

// update segment tree
void update(int node, int nodeLeft, int nodeRight, int queryIndex, int value)
{
    if (queryIndex < nodeLeft || nodeRight < queryIndex)
    {
        return;
    }

    if (nodeLeft == nodeRight)
    {
        sumTree[node] = value;
        return;
    }

    int mid = (nodeLeft + nodeRight) / 2;

    update(node * 2, nodeLeft, mid, queryIndex, value);
    update(node * 2 + 1, mid + 1, nodeRight, queryIndex, value);

    sumTree[node] = sumTree[node * 2] + sumTree[node * 2 + 1];
}

long long querySum(int node, int nodeLeft, int nodeRight, int queryLeft, int queryRight)
{
    if (queryRight < nodeLeft || nodeRight < queryLeft)
    {
        return 0;
    }

    if (queryLeft <= nodeLeft && nodeRight <= queryRight)
    {
        return sumTree[node];
    }

    int mid = (nodeLeft + nodeRight) / 2;
    long long leftSum = querySum(node * 2, nodeLeft, mid, queryLeft, queryRight);
    long long rightSum = querySum(node * 2 + 1, mid + 1, nodeRight, queryLeft, queryRight);

    return leftSum + rightSum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int test = 1; test <= t; test++)
    {
        cin >> n;
        int m;
        cin >> m;

        cout << "#" << test << " ";

        a.resize(n);
        sumTree.resize(4 * n);

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            if (i % 2 == 1)
            {
                a[i] = -a[i];
            }
        }

        init(1, 0, n - 1);

        for (int i = 0; i < m; i++)
        {
            int query, left, right;
            cin >> query >> left >> right;

            if (query == 0)
            {
                if (left % 2 == 1)
                {
                    right = -right;
                }
                update(1, 0, n - 1, left, right);
            }
            else if (query == 1)
            {
                long long sum = querySum(1, 0, n - 1, left, right - 1);
                if (left % 2 == 1)
                {
                    sum = -sum;
                }
                cout << sum << " ";
            }
        }
        cout << '\n';
    }

    return 0;
}