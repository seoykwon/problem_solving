#include <iostream>
#include <queue>

using namespace std;

int field[51][51] = {
    0,
};
// snow = 2
// gem = 3

int main()
{
    freopen("input.txt", "r", stdin);
    int N, M;

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> field[i][j];
        }
    }
}