#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath> // for ceil() and log2()
using namespace std;

int n, m;
vector<int> nums;
vector<int> segTree;

int build(int node, int start, int end)
{
    if (start == end)
    {
        // leaf node
        return segTree[node] = nums[start];
    }
    int mid = (start + end) / 2;
    int leftMin = build(2 * node, start, mid);
    int rightMin = build(2 * node + 1, mid + 1, end);

    return segTree[node] = min(leftMin, rightMin);
}

int findMin(int node, int start, int end, int left, int right)
{
    if (right < start || left > end)
    {
        return INT_MAX;
    }

    if (left <= start && right >= end)
    {
        // 구간 포함됨
        return segTree[node];
    }

    int mid = (start + end) / 2;
    int leftMin = findMin(2 * node, start, mid, left, right);
    int rightMin = findMin(2 * node + 1, mid + 1, end, left, right);

    return min(leftMin, rightMin);
}

void update(int node, int start, int end, int idx, int value)
{
    if (start == end)
    {
        segTree[node] = value;
        nums[start] = value;
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

    // 부모 노드 갱신
    segTree[node] = min(segTree[2 * node], segTree[2 * node + 1]);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;

    nums.resize(n);
    int height = (int)ceil(log2(n));
    int treesize = (1 << (height + 1));
    segTree.resize(treesize);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    build(1, 0, n - 1);

    cin >> m;
    while (m--)
    {
        int type, a, b;
        cin >> type >> a >> b;

        if (type == 1)
        {
            update(1, 0, n - 1, a - 1, b);
        }
        else
        {
            int ans = findMin(1, 0, n - 1, a - 1, b - 1);
            cout << ans << '\n';
        }
    }
    return 0;
}

// #######################################
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int n, m;
int arr[1100000];
// segment tree의 크기는 원본배열의 4배로 구성
int seg[4400000];

int makeSeg(int index, int s, int e)
{
    // 범위가 같아졌다면, 원본배열 해당 인덱스에 저장된 값을 기록
    if (s == e)
    {
        return seg[index] = arr[s];
    }
    int mid = (s + e) / 2;
    // 범위를 반씩 줄여가며 더 내려가보기
    int a = makeSeg(index * 2, s, mid);
    int b = makeSeg(index * 2 + 1, mid + 1, e);
    // 양쪽의 두 값 중 작은것을 기록
    return seg[index] = min(a, b);
}

int getMin(int index, int s, int e, int &tarS, int &tarE)
{

    // 범위를 아예 벗어난 경우 : 연산에 영향주지 않을 값 return
    if (e < tarS || tarE < s)
        return INT_MAX;
    // 범위를 완전히 포함하는 경우 : 해당 노드의 값 return
    if (tarS <= s && e <= tarE)
        return seg[index];
    // 일부만 포함하는 경우 : 더 내려가 보기
    int mid = (s + e) / 2;
    int a = getMin(index * 2, s, mid, tarS, tarE);
    int b = getMin(index * 2 + 1, mid + 1, e, tarS, tarE);
    return min(a, b);
}

int updateSeg(int index, int s, int e, int a, int b)
{

    // 범위를 벗어난 경우
    if (!(s <= a && a <= e))
        return seg[index];
    // 변경될 원본배열의 index에 해당하는 노드를 찾은 경우
    if (s == e)
    {
        arr[a] = b;
        return seg[index] = b;
    }

    // 더 내려가 보기
    int mid = (s + e) / 2;
    int t1 = updateSeg(index * 2, s, mid, a, b);
    int t2 = updateSeg(index * 2 + 1, mid + 1, e, a, b);
    return seg[index] = min(t1, t2);
}

int main()
{

    // freopen_s(new FILE*, "input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    makeSeg(1, 0, n - 1);

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int cmd;
        cin >> cmd;

        if (cmd == 1)
        {
            int a, b;
            cin >> a >> b;
            updateSeg(1, 0, n - 1, a - 1, b);
        }
        if (cmd == 2)
        {
            int s, e;
            cin >> s >> e;
            s--;
            e--;
            cout << getMin(1, 0, n - 1, s, e) << "\n";
        }
    }

    return 0;
}