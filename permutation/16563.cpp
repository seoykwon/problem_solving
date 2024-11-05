#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int SIZE = 5000000;

// 소수 경로 정해서 리턴하는 함수
vector<int> isPrime()
{
    vector<int> prime(SIZE + 1, 0);

    // 먼저 모든 수를 소수라 가정, i번째 인덱스에 i 값 지정
    for (int i = 2; i <= SIZE; i++)
        prime[i] = i;

    for (int i = 2; i <= sqrt(SIZE); i++)
    {
        if (prime[i] == i)
        {
            for (int j = i * i; j <= SIZE; j += i)
            {
                if (prime[j] == j)
                {
                    prime[j] = i;
                }
            }
        }
    }
    return prime;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    cin >> n;

    vector<int> prime = isPrime();

    while (n--)
    {
        cin >> k;

        while (k > 1)
        {
            cout << prime[k] << ' ';
            k = k / prime[k];
        }
        cout << '\n';
        // cout << endl; 이라고 하면 시간 초과가 뜸.
    }
    return 0;
}