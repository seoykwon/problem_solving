#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
    int N, Q;
    vector<int> mineral;
    cin >> N >> Q;

    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;

        mineral.push_back(tmp);
    }

    sort(mineral.begin(), mineral.end(), cmp);

    while (Q--)
    {
        int left, right;
        cin >> left >> right;

        cout << upper_bound(mineral.begin(), mineral.end(), right) - lower_bound(mineral.begin(), mineral.end(), left) << '\n';
    }
}

// ################## 강사님 코드 ###########################
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1000000000;
int N, Q;
int stone[100000];

int lowerBound(int tar)
{
    int left = 0;
    int right = N + 1;
    int idx = 0;

    while (left <= right)
    {
        int mid = (left + mid) / 2;

        if (stone[mid] >= tar)
        {
            idx = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return idx;
}

int upperBound(int tar)
{
    int left = 0;
    int right = N + 1;
    int idx = 0;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (stone[mid] > tar)
        {
            idx = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    return idx;
}

int main(void)
{
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
        cin >> stone[i];

    stone[0] = -MAX - 1;
    stone[N + 1] = MAX + 1;

    sort(stone, stone + N + 2);

    for (int i = 0; i < Q; i++)
    {
        int s, e;
        cin >> s >> e;
        cout << upperBound(e) - lowerBound(s) << '\n';
    }

    return 0;
}