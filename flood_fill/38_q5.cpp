// anna and elsa
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N;
int field[6][6];
int elsay, elsax, annay, annax;
// 0 for path -1 for iceberg
struct pos
{
    int y;
    int x;
};
int ydir[] = {-1, 0, 1, 0};
int xdir[] = {0, -1, 0, 1};
int eyd[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int exd[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dista[6][6];
int diste[6][6];

void input()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char tmp;
            cin >> tmp;

            if (tmp == '_')
            {
                field[i][j] = 0;
            }
            else if (tmp == '#')
            {
                field[i][j] = -1;
            }
        }
    }

    cin >> elsay >> elsax >> annay >> annax;
}

void bfse(int y, int x)
{
}

void bfsa(int y, int x)
{
}

int main()
{
    input();

    bfse(elsay, elsax);

    bfsa(annay, annax);
}