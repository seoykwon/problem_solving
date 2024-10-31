#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

// 소수 판별 함수
bool isPrime(int num)
{
    if (num <= 1)
        return false;
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int solution(string numbers)
{
    set<int> primes; // 고유한 소수 저장을 위한 set

    // 모든 가능한 조합을 생성
    sort(numbers.begin(), numbers.end());
    do
    {
        for (int len = 1; len <= numbers.size(); len++)
        {
            int num = stoi(numbers.substr(0, len));
            if (isPrime(num))
            {
                primes.insert(num);
            }
        }
    } while (next_permutation(numbers.begin(), numbers.end()));

    // 고유한 소수의 개수를 반환
    return primes.size();
}

// ####################################################################

#include <string>
#include <vector>
#include <set>
#include <cstring>

using namespace std;
int answer = 0;
bool visited[10];
set<int> s;

bool check(string str)
{
    int a = stod(str);
    if (a < 2)
    {
        return false;
    }
    for (int i = 2; i < a; i++)
    {
        if (a % i == 0)
        {
            return false;
        }
    }
    s.insert(a);
    return true;
}

void dfs(string numbers, string str)
{
    if (str != "")
    {
        check(str);
    }
    for (int i = 0; i < numbers.length(); i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            dfs(numbers, str + numbers[i]);
            visited[i] = 0;
        }
    }
}

int solution(string numbers)
{
    memset(visited, false, sizeof(visited));
    dfs(numbers, "");
    answer = s.size();
    s.clear();
    return answer;
}