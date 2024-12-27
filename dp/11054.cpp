#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int longestBitonicSubsequence(int n, const vector<int> &arr)
{
    vector<int> dp_increase(n, 1); // 증가 부분 수열
    vector<int> dp_decrease(n, 1); // 감소 부분 수열

    // 증가 부분 수열 계산
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (arr[j] < arr[i])
            {
                dp_increase[i] = max(dp_increase[i], dp_increase[j] + 1);
            }
        }
    }

    // 감소 부분 수열 계산
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[i])
            {
                dp_decrease[i] = max(dp_decrease[i], dp_decrease[j] + 1);
            }
        }
    }

    // 가장 긴 바이토닉 수열 길이 계산
    int max_length = 0;
    for (int i = 0; i < n; ++i)
    {
        max_length = max(max_length, dp_increase[i] + dp_decrease[i] - 1);
    }

    return max_length;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    cout << longestBitonicSubsequence(n, arr) << endl;

    return 0;
}
