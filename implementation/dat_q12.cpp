#include <iostream>
#include <vector>

using namespace std;

int count = 0; // 세 수의 합이 K가 되는 경우의 수
int N, K;

// DFS 함수: arr[start]부터 시작하여 3개의 수를 고르고 그 합이 K인지 확인
void dfs(const vector<int> &arr, int start, int depth, int sum)
{
    if (depth == 3)
    {
        // 세 수를 모두 고른 경우, 그 합이 K인지를 확인
        if (sum == K)
        {
            count++; // 합이 K일 때 경우의 수 증가
        }
        return;
    }

    // 가능한 숫자들을 고른다 (a < b < c)
    for (int i = start; i < N; ++i)
    {
        dfs(arr, i + 1, depth + 1, sum + arr[i]);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N >> K;
    vector<int> arr(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    // DFS를 이용해 3개의 수를 고른다
    dfs(arr, 0, 0, 0);

    // 결과 출력
    cout << count << endl;

    return 0;
}

// ########### 위에 코드는 Time Limit Error 발생 ########################
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int countTriplets(vector<int> &arr, int K)
{
    int N = arr.size();
    int count = 0;

    // 배열을 오름차순으로 정렬
    sort(arr.begin(), arr.end());

    // 첫 번째 수를 고르고 두 번째, 세 번째 수를 두 포인터로 찾기
    for (int i = 0; i < N - 2; ++i)
    {
        int left = i + 1;
        int right = N - 1;

        // 두 포인터로 합이 K인 경우 찾기
        while (left < right)
        {
            int total = arr[i] + arr[left] + arr[right];
            if (total == K)
            {
                count++; // 합이 K가 될 때마다 경우의 수 증가
                left++;  // left 포인터를 오른쪽으로 이동
                right--; // right 포인터를 왼쪽으로 이동
            }
            else if (total < K)
            {
                left++; // 합이 K보다 작으면 left 포인터를 증가시켜 합을 키운다
            }
            else
            {
                right--; // 합이 K보다 크면 right 포인터를 감소시켜 합을 줄인다
            }
        }
    }

    return count;
}

int main()
{
    int N, K;
    cin >> N >> K;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    cout << countTriplets(arr, K) << endl;

    return 0;
}

// ############## 강사님 코드 #############################
#include <iostream>
using namespace std;

int DAT[100001];
int arr[5000];

int main()
{
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        DAT[arr[i]] = 1;
    }
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int target = K - (arr[i] + arr[j]);
            if (target < 0 || target > 100000)
                continue;
            if (target != arr[i] && target != arr[j] && DAT[target] == 1)
            {
                cnt++;
            }
        }
    }
    cout << cnt / 3;
}