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

    // multiplication
    result *= nums[idx];
    go(idx + 1);
    result /= nums[idx];

    // addition
    result += nums[idx];
    go(idx + 1);
    result -= nums[idx];

    // subtraction
    result -= nums[idx];
    go(idx + 1);
    result += nums[idx];
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