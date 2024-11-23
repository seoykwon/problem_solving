#include <iostream>

using namespace std;

int n;
int nums[11];
int result = nums[0];
char operation[11];

void go(int idx)
{
    if (idx == n)
    {
        if (result % 101 == 0)
        {
            for (int i = 0; i < n; i++)
            {
                cout << nums[i] << operation[i];
            }
            cout << '\n';
        }
        return;
    }

    int tmp = result;

    // multiplication
    result *= nums[idx];
    operation[idx - 1] = '*';
    go(idx + 1);
    result = tmp;

    // addition
    result += nums[idx];
    operation[idx - 1] = '+';
    go(idx + 1);
    result = tmp;

    // subtraction
    result -= nums[idx];
    operation[idx - 1] = '-';
    go(idx + 1);
    result = tmp;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    go(1);

    return 0;
}

// 첫 번째 코드의 문제는 전역 변수와 배열 초기화의 부정확함, 출력 로직의 복잡성 때문입니다.

#include <iostream>
#include <vector>

using namespace std;

int n;
int nums[11];
vector<char> path;
long long result;

void go(int idx)
{
    if (idx == n)
    {
        if (result % 101 == 0 && result != 0)
        {
            for (int i = 0; i < n; i++)
            {
                cout << nums[i];
                if (i < path.size())
                    cout << path[i];
            }
            cout << "\n";
        }
        return;
    }

    long long tmp = result;

    // 곱하기
    result *= nums[idx];
    path.push_back('*');
    go(idx + 1);
    result = tmp;
    path.pop_back();

    // 더하기
    result += nums[idx];
    path.push_back('+');
    go(idx + 1);
    result = tmp;
    path.pop_back();

    // 빼기
    result -= nums[idx];
    path.push_back('-');
    go(idx + 1);
    result = tmp;
    path.pop_back();
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    result = nums[0];
    go(1);
    return 0;
}
