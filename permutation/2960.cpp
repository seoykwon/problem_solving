#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int isPrime(int n, int k)
{
    vector<bool> is_prime(n + 1, true);
    int cnt = 0;

    // 제곱근까지 검사할 경우 반례: k번째 지워지는 수가 제곱근 이상의 소수일 경우
    // 따라서 이 문제에서는 꼭 n까지 돌려야 함

    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
        { // i가 소수라면

            for (int j = i; j <= n; j += i)
            { // 이 문제에서 i번째도 지우는 수에 포함되므로 i부터
                if (!is_prime[j])
                    continue; // 이미 지워진 수라면 넘어감

                is_prime[j] = false; // i의 배수를 제거
                if (++cnt == k)
                    return j; // k번째 지우는 수 리턴
            }
        }
    }
    return -1;
}

int main()
{
    int n, k;

    cin >> n >> k;

    cout << isPrime(n, k) << '\n';

    return 0;
}