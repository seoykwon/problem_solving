#include <iostream>
#include <queue>
#include <climits>

using namespace std;

int t;
int n;
int field[10][10] = {
    0,
};
int maxApple;

void input()
{
    cin >> n;

    maxApple = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            field[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> field[i][j];

            if (field[i][j] > maxApple)
            {
                maxApple = field[i][j];
            }
        }
    }
}

int main()
{

    cin >> t;

    while (t--)
    {
        input();
    }
}