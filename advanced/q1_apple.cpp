#include <iostream>
#include <queue>

using namespace std;

int t;
int n;
int field[10][10] = {
    0,
};

void input()
{
    cin >> n;

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