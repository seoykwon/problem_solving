#include <iostream>

using namespace std;

int arr[36];

int fibonacci(int num)
{
    if (num == 0)
    {
        arr[0] = 0;
        return arr[0];
    }
    if (num == 1)
    {
        arr[1] = 1;
        return arr[1];
    }

    return fibonacci(num - 1) + fibonacci(num - 2);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    cout << fibonacci(n - 1);
}

// ################### 강사님 코드 ############################
#include <iostream>

using namespace std;

int memo[1000];

int getFibo(int n)
{
    if (n == 1)
        return 0;
    if (n == 0)
        return 1;

    if (memo[n] != 0)
        return memo[n];

    int a = getFibo(n - 1);
    int b = getFibo(n - 2);

    memo[n] = a + b;
    return a + b;
}

int main()
{
    int n;
    cin >> n;

    cout << getFibo(n);

    return 0;
}