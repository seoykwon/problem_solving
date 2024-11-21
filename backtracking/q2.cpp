#include <iostream>

using namespace std;

// Recursive function to calculate the number of steps to reach 1
int collatzSteps(int n)
{
    if (n == 1)
    {
        return 0; // Base case: If n is 1, no more steps are needed
    }

    if (n % 2 == 0)
    {
        return 1 + collatzSteps(n / 2); // If n is even, divide by 2 and recurse
    }
    else
    {
        return 1 + collatzSteps(3 * n + 1); // If n is odd, compute 3n + 1 and recurse
    }
}

int main()
{
    int N;
    cin >> N; // Read the input number

    cout << collatzSteps(N) << endl; // Output the number of steps

    return 0;
}

// ################### 강사님 코드 ####################
#include <iostream>
using namespace std;

int cnt;

void func(int num)
{
    // 기저 조건
    if (num == 1)
        return;

    if (num % 2 == 0)
    {
        num /= 2;
    }
    else
    {
        num = num * 3 + 1;
    }
    cnt++;

    func(num);
}

int main()
{
    int num;
    cin >> num;
    func(num);
    cout << cnt;
}