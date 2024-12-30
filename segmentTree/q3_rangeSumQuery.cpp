#include <iostream>
#include <vector>
using namespace std;

class SegmentTree
{
private:
    vector<long long> tree;
    int n;

    void build(int node, int start, int end, const vector<int> &data)
    {
        if (start == end)
        {
            tree[node] = data[start];
        }
        else
        {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;

            build(left_child, start, mid, data);
            build(right_child, mid + 1, end, data);

            tree[node] = tree[left_child] + tree[right_child];
        }
    }

    void update(int idx, int value, int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = value;
        }
        else
        {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;

            if (idx <= mid)
            {
                update(idx, value, left_child, start, mid);
            }
            else
            {
                update(idx, value, right_child, mid + 1, end);
            }

            tree[node] = tree[left_child] + tree[right_child];
        }
    }

    long long query(int l, int r, int node, int start, int end)
    {
        if (r < start || l > end)
        {
            return 0;
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        long long sum_left = query(l, r, left_child, start, mid);
        long long sum_right = query(l, r, right_child, mid + 1, end);

        return sum_left + sum_right;
    }

public:
    SegmentTree(const vector<int> &data)
    {
        n = data.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, data);
    }

    void update(int idx, int value)
    {
        update(idx, value, 0, 0, n - 1);
    }

    long long query(int l, int r)
    {
        return query(l, r, 0, 0, n - 1);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    SegmentTree segment_tree(arr);

    for (int i = 0; i < q; ++i)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int a, b;
            cin >> a >> b;
            segment_tree.update(a - 1, b);
        }
        else if (type == 2)
        {
            int s, e;
            cin >> s >> e;
            cout << segment_tree.query(s - 1, e - 1) << "\n";
        }
    }

    return 0;
}

// ###############################################
#include <iostream>
using namespace std;

typedef long long ll;

int N, M;
int arr[1100000];
ll seg[4000000];

ll makeSeg(int index, int s, int e)
{
    int mid = (s + e) / 2;
    if (s > e)
        return 0;
    if (s == e)
        return seg[index] = arr[s];

    ll a = makeSeg(index * 2 + 0, s, mid);
    ll b = makeSeg(index * 2 + 1, mid + 1, e);
    return seg[index] = a + b;
}

ll getSum(int index, int s, int e, int tarS, int tarE)
{
    if (tarS <= s && e <= tarE)
        return seg[index];
    if (s > e || e < tarS || tarE < s)
        return 0;

    int mid = (s + e) / 2;
    ll a = getSum(index * 2 + 0, s, mid, tarS, tarE);
    ll b = getSum(index * 2 + 1, mid + 1, e, tarS, tarE);
    return a + b;
}

ll setUpdate(int index, int s, int e, int a, int b)
{
    if (!(s <= a && a <= e))
        return seg[index];
    if (s == e)
    {
        arr[a] = b;
        return seg[index] = b;
    }

    int mid = (s + e) / 2;
    ll t1 = setUpdate(index * 2 + 0, s, mid, a, b);
    ll t2 = setUpdate(index * 2 + 1, mid + 1, e, a, b);
    return seg[index] = t1 + t2;
}

int main()
{
    // freopen_s(new FILE*, "input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
        cin >> arr[i];

    makeSeg(1, 0, N - 1);

    for (int i = 0; i < M; i++)
    {
        int cmd, a, b;
        cin >> cmd >> a >> b;

        if (cmd == 1)
        {
            setUpdate(1, 0, N - 1, a - 1, b);
        }
        if (cmd == 2)
        {
            cout << getSum(1, 0, N - 1, a - 1, b - 1) << "\n";
        }
    }

    return 0;
}