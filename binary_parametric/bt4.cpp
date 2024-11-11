// root 값의 정수부를 O(log N) 속도로 구하는 코드
// without using math library

#include <iostream>

using namespace std;

void psearch(int n)
{
    int left = 0;
    int right = n;
    int ans = 0;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (mid * mid == n)
        {
            cout << mid << '\n';
            return;
        }
        if (mid * mid > n)
        {
            right = mid - 1;
        }
        else if (mid * mid < n)
        {
            left = mid + 1;
            ans = mid;
        }
    }
    cout << ans << '\n';
}

int main()
{
    freopen("input.txt", "r", stdin);
    int N;
    cin >> N;

    psearch(N);
}

/**
 * 이전 코드에서 left와 right의 경계 조건이 제대로 설정되지 않아,
 * 큰 숫자에 대해 정확한 값을 반환하지 못하는 문제가 있었습니다.
 * 큰 수를 다룰 때, mid * mid가 오버플로우를 일으킬 수 있기 때문에
 * mid * mid 대신 n / mid와 같은 방식으로 검사를 수행하는 것이 더 안전합니다.
 */

/**
 * 오버플로우의 원인
만약 left와 right 둘 다 매우 큰 값이라면, left + right는 int 범위를 넘어서는 큰 수가 되어
오버플로우가 발생할 수 있습니다. 오버플로우가 발생하면 의도하지 않은 값이 mid에 저장되어
잘못된 동작을 할 가능성이 높습니다.

해결 방법
left + (right - left) / 2를 사용하면 오버플로우가 방지됩니다.
이 방법은 덧셈으로 인한 범위 초과를 피할 수 있는 구조입니다.

right - left는 left와 right의 차이이므로 항상 right와 left 사이의 범위 내에서 작거나 같은 값입니다.
따라서 right - left 자체가 오버플로우를 발생시키지 않습니다.
(right - left) / 2를 먼저 계산하고, 그 결과를 left에 더하는 방식이라서
최종적으로 더 큰 숫자가 되더라도 left가 오버플로우의 위험을 피할 수 있게 됩니다.
예시
예를 들어 left = 2,000,000,000이고 right = 2,100,000,000라고 가정해보겠습니다.

(left + right) / 2 방식으로 mid를 계산하면 4,100,000,000 / 2 = 2,050,000,000이 되어야 하지만,
left + right는 int 범위(2,147,483,647)를 초과하기 때문에 오버플로우가 발생합니다.
그러나 left + (right - left) / 2 방식으로 계산하면:
right - left = 100,000,000
(right - left) / 2 = 50,000,000
left + 50,000,000 = 2,050,000,000, 오버플로우 없이 정확한 값이 계산됩니다.
따라서, int mid = left + (right - left) / 2;는 오버플로우를 방지하면서 중간 값을 정확하게
계산할 수 있는 방법입니다.
 */

#include <iostream>

using namespace std;

void psearch(int n)
{
    int left = 0;
    int right = n;
    int ans = 0;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (mid <= n / mid) // Avoids potential overflow with mid * mid
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << ans << '\n';
}

int main()
{
    freopen("input.txt", "r", stdin);
    int N;
    cin >> N;

    if (N == 1)
    {
        cout << 1 << '\n';
        return 0;
    }

    psearch(N);
    return 0;
}
