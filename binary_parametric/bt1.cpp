#include <iostream>
#include <algorithm>

using namespace std;

int n;
int num[100000];

int k;
int group[1000];

bool search(int left, int right, int target)
{
    int ret;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (num[mid] < target)
        {
            left = mid + 1;
        }
        else if (num[mid] >= target)
        {
            ret = mid;
            right = mid - 1;
        }
    }
    return num[ret] == target;
}

bool cmp(int left, int right)
{
    if (left < right)
        return true;
    if (left > right)
        return false;
    return false;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }

    sort(num, num + n, cmp);

    cin >> k;
    for (int i = 0; i < k; i++)
    {
        cin >> group[i];

        bool res = search(0, n - 1, group[i]);

        if (res)
        {
            cout << "O";
        }
        else
        {
            cout << "X";
        }
    }
    return 0;
}

// ##################### 강사님 코드 ##############################
#include <iostream>
#include <algorithm>

using namespace std;

int arr[100001];
int N;

void bs(int tar)
{
    int st = 0;
    int ed = N - 1;

    while (st <= ed)
    {
        int mid = (st + ed) / 2;
        if (arr[mid] == tar)
        {
            cout << "O";
            return;
        }
        else if (arr[mid] > tar)
        {
            ed = mid - 1;
        }
        else
        {
            st = mid + 1;
        }
    }
    cout << "X";
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr + N);

    int K;
    cin >> K;
    for (int i = 0; i < K; i++)
    {
        int tar;
        cin >> tar;
        bs(tar);
    }
    return 0;
}