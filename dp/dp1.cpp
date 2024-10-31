#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(int N, int number)
{
    if (N == number)
        return 1; // 숫자 N 하나로 바로 만들 수 있는 경우

    vector<set<int>> dp(9); // dp[i]는 N을 i번 사용하여 만들 수 있는 수들의 집합

    // 초기화: N을 i번 사용한 수 만들기 (예: N, NN, NNN 등)
    int currentNum = 0;
    for (int i = 1; i <= 8; i++)
    {
        currentNum = currentNum * 10 + N;
        dp[i].insert(currentNum);
    }

    // i개의 N을 사용하여 수를 만들기 시작
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j < i; j++)
        {
            for (int a : dp[j])
            {
                for (int b : dp[i - j])
                {
                    dp[i].insert(a + b);
                    dp[i].insert(a - b);
                    dp[i].insert(a * b);
                    if (b != 0)
                        dp[i].insert(a / b);
                }
            }
        }
        // 목표 숫자가 dp[i]에 있다면 반환
        if (dp[i].count(number))
            return i;
    }

    return -1; // 8번 이상 사용해도 못 만드는 경우
}
