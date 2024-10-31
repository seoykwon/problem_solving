#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int coin[4] = {500, 100, 50, 10};

    int pay;
    cin >> pay;

    int cnt = 0;

    for (int i = 0; i < 4; i++)
    {
        cnt += pay / coin[i];
        pay = pay % coin[i];
    }

    cout << cnt;
}