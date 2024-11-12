#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> churros;
int N, K;

bool cmp(int a, int b)
{
    if (a < b)
        return false;
    if (a > b)
        return true;
    return false;
}

int distribute()
{
    int left = 1;
    int right = churros[0];
    int ans = 0;

    while (left <= right)
    {
        int tmp = 0;
        int mid = (left + right) / 2;

        for (int i = 0; i < churros.size(); i++)
        {
            int div = churros[i] / mid;
            tmp += div;
        }

        if (tmp >= K)
        {
            ans = mid;
            left = mid + 1;
        }
        else if (tmp < K)
        {
            right = mid - 1;
        }

        // if (tmp = K)
        // {
        //     ans = mid;
        //     // 여기서 parameter를 조정해 주지 않으면 무한 루프에 빠지게 됨.
        // }
        // else if (tmp > K)
        // {
        //     left = mid + 1;
        // }
        // else if (tmp < K)
        // {
        //     right = mid - 1;
        // }
    }

    return ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> N >> K;

    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;

        churros.push_back(tmp);
    }

    sort(churros.begin(), churros.end(), cmp);

    int res = distribute();

    cout << res << '\n';

    return 0;
}