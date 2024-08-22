#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int T;
int X, Y;

char board[51][51];

void input()
{
    cin >> X >> Y;
}

int main()
{
    cin >> T;

    for (int i = 1; i <= T; i++)
    {
        input();
    }
}