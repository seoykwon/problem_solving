#include <iostream>

using namespace std;

int board[11][11];
int n;
int cnt = 0;
int row[11];

void search(int num)
{
    if (num == n)
    {
        cnt++;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (row[i])
            continue;
        row[i] = 1;
        search(num + 1);
        row[i] = 0;
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;

    search(0);

    cout << cnt << '\n';
    return 0;
}