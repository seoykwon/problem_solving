#include <iostream>

using namespace std;

int t, n;
int arr[11][11];
int order = 1;
int housesN;
int routerX = 0;
int routerY = 0;
int radius = 0;

int check(int r)
{
    int cnt = 0;
    for (int i = routerY - r; i <= routerY + r; i++)
    {
        if (i < 0 || i > n)
            continue;
        for (int j = routerX - r; j <= routerX + r; j++)
        {
            if (j < 0 || j > n)
                continue;

            int dist = (i - routerY) * (i - routerY) + (j - routerX) * (j - routerX);

            if (dist <= r * r)
            {
                if (arr[i][j] == 1)
                {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> t;

    while (t--)
    {
        cin >> n;
        housesN = 0;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == 1)
                {
                    housesN++;
                }

                if (arr[i][j] == 2)
                {
                    routerY = i;
                    routerX = j;
                }
            }
        }
        cout << "#" << order << " ";
        // cout << housesN << " : ";

        for (int i = 1; i <= 20; i++)
        {
            int c = check(i);

            // cout << "i: " << i << " ";
            // cout << "c: " << c << " ";

            if (c == housesN)
            {
                radius = i;
                break;
            }
        }

        cout << radius << endl;
        order++;
    }
}