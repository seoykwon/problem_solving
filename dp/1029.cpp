#include <iostream>
#include <string.h>
#include <string>
using namespace std;

int artist_num;
int price_board[15][15];
int dp[1 << 15][15][10];

int Resell(int visited, int artist, int price)
{
    int &ret = dp[visited][artist][price];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int i = 1; i < artist_num; ++i)
    {
        if (!(visited & (1 << i)) && price_board[artist][i] >= price)
        {
            int next_visited = visited | (1 << i);
            ret = max(ret, Resell(next_visited, i, price_board[artist][i]) + 1);
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> artist_num;

    for (int i = 0; i < artist_num; ++i)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < artist_num; ++j)
            price_board[i][j] = tmp[j] - '0';
    }

    memset(dp, -1, sizeof(dp));
    Resell(1, 0, 0);
    cout << dp[1][0][0] + 1 << "\n";

    return 0;
}