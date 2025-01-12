#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

bool is_square(int n)
{
    return sqrt(n) == (int)sqrt(n);
}

int find_square(char arr[][10], int n, int m)
{
    int max_square = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int dx = -n; dx < n; dx++)
                for (int dy = -m; dy < m; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue;

                    int x = i, y = j;
                    string num = "";

                    while (x >= 0 && x < n && y >= 0 && y < m)
                    {
                        num += arr[x][y];
                        if (is_square(stoi(num)))
                            max_square = max(max_square, stoi(num));

                        x += dx;
                        y += dy;
                    }
                }

    return max_square;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    char arr[10][10];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];

    cout << find_square(arr, n, m) << '\n';

    return 0;
}