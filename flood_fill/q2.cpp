#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

int earth[101][101];
long long sprout[101][101];

struct pos
{
    int y;
    int x;
};
int H, W;
queue<pos> q;

long long ans = 0;

void bfs()
{
    while (!q.empty())
    {
        pos now = q.front();
        q.pop();

        int ydir[] = {-1, 0, 1, 0};
        int xdir[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= H || nx >= W)
                continue;

            if (sprout[ny][nx] < sprout[now.y][now.x] + 1)
                continue;

            sprout[ny][nx] = sprout[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> H >> W;

    memset(sprout, 10000, sizeof(sprout));
    memset(earth, 0, sizeof(earth));

    // for (int i = 0; i < H; i++)
    // {
    //     for (int j = 0; j < W; j++)
    //     {
    //         cout << sprout[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < 2; i++)
    {
        int row, col;

        cin >> row >> col;

        q.push({row, col});
        sprout[row][col] = 1;
    }

    bfs();

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            // if (sprout[i][j] > ans)
            // {
            //     ans = sprout[i][j];
            // }
            ans = max(ans, sprout[i][j]);
        }
    }

    cout << ans;
    return 0;
}