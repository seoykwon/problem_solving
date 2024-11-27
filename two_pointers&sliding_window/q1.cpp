#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M; // 수열의 크기 N과 구간 합 M 입력

    vector<int> A(N); // 수열 A
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    int left = 0, right = 0, sum = 0, count = 0;

    // 슬라이딩 윈도우 방식으로 구간 합 계산
    while (right < N)
    {
        sum += A[right]; // right를 한 칸 확장하면서 sum에 더함

        // sum이 M보다 커지면 left를 오른쪽으로 이동하여 구간을 축소
        while (sum > M && left <= right)
        {
            sum -= A[left]; // left를 한 칸 이동하면서 sum에서 빼기
            left++;
        }

        // sum이 M이면 count 증가
        if (sum == M)
        {
            count++;
        }

        right++; // right를 오른쪽으로 한 칸 이동
    }

    cout << count << endl; // 구간 합이 M인 경우의 수 출력
    return 0;
}

// ############################################
#include <iostream>
using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    int arr[10000] = {
        0,
    };
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // two pointer
    int left = 0;
    int right = 0;
    int sum = 0;
    int cnt = 0;

    while (right <= n)
    {
        // 중간합이 작으면 우측 포인터를 하나 이동, 해당 위치의 값을 누적
        if (sum < m)
        {
            sum += arr[right];
            right++;
        }
        // 중간합이 크면 좌측 포인터를 하나 이동, 원래 위치에 있던 값을 제거
        if (sum > m)
        {
            sum -= arr[left];
            left++;
        }
        // 중갑합이 같으면 cnt 누적, 종료조건을 위해 우측 포인터 이동
        if (sum == m)
        {
            cnt++;
            sum += arr[right];
            right++;
        }
    }
    cout << cnt;
}
// ####################################
#include <iostream>
using namespace std;

int main()
{
    int n, m;
    int arr[100000];
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int cnt = 0;

    int sum = 0;
    int b = 0;
    for (int a = 0; a < n; a++)
    {
        while (b < n && sum < m)
        {
            sum += arr[b];
            b++;
        }
        if (b >= n && sum < m)
            break;
        // [a,b)
        if (sum == m)
        {
            cnt++;
        }
        sum -= arr[a];
    }
    cout << cnt;
    return 0;
}