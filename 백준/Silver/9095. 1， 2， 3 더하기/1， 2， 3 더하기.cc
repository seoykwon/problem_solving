#include <iostream>
using namespace std;

int n;
int res = 0;

void go(int num)
{
    if (num == n)
    {
        res += 1;
    }
    if (num > n)
    {
        return;
    }
    go(num + 1);

    go(num + 2);

    go(num + 3);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int t;
    cin >> t;

    while (t--)
    {
        cin >> n;
        res = 0;

        go(0);

        cout << res << '\n';
    }
}