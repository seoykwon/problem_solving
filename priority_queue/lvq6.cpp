#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N;

int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    cin >> N;

    // Max-heap for the lower half
    priority_queue<int> left;

    // Min-heap for the upper half
    priority_queue<int, vector<int>, greater<int>> right;

    // Initialize with a median value of 500
    left.push(500);

    for (int i = 0; i < N; i++)
    {
        int first, second;
        cin >> first >> second;

        // Insert both numbers into the heaps
        if (first <= left.top())
            left.push(first);
        else
            right.push(first);

        if (second <= left.top())
            left.push(second);
        else
            right.push(second);

        // Balance the heaps
        if (left.size() > right.size() + 1)
        {
            right.push(left.top());
            left.pop();
        }
        else if (right.size() > left.size())
        {
            left.push(right.top());
            right.pop();
        }

        // The median is the top of the max-heap (left)
        cout << left.top() << endl;
    }

    return 0;
}

// ####################### 강사님 코드 ########################
#include <iostream>
#include <queue>
using namespace std;

priority_queue<int> lheap;                            // max heap
priority_queue<int, vector<int>, greater<int>> rheap; // min heap
int mid;

void push(int v)
{
    if (mid > v)
        lheap.push(v);
    else
        rheap.push(v);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);

    mid = 500;

    int n;
    int a, b;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;

        push(a);
        push(b);

        if (lheap.size() > rheap.size())
        {
            rheap.push(mid);
            mid = lheap.top();
            lheap.pop();
        }
        else if (lheap.size() < rheap.size())
        {
            lheap.push(mid);
            mid = rheap.top();
            rheap.pop();
        }

        cout << mid << "\n";
    }

    return 0;
}