#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int width, height;
int zombie[101][101];
int ppl[101][101];
int sx, sy;
struct pos
{
    int y;
    int x;
};
int untreated = 0;
int timeSpent = 0;

void bfs(int y, int x)
{
    queue<pos> q;
    q.push({y, x});
    ppl[y][x] = 3;

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

            if (ny < 0 || nx < 0 || ny >= height || nx >= width)
                continue;

            if (ppl[ny][nx] != 0 || zombie[ny][nx] != 1)
                continue;

            ppl[ny][nx] = ppl[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    memset(ppl, 0, sizeof(ppl));
    cin >> width >> height;
    // cout << height << " " << width << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char tmp;
            cin >> tmp;
            zombie[i][j] = tmp - '0';

            // when there are no spaces in input numbers,
            // you need to intentionally separate each value
            // in this case, I used char
            // cout << zombie[i][j] << " ";
        }
        // cout << endl;
    }

    cin >> sx >> sy;
    // cout << sy << " " << sx << endl;

    bfs(sy - 1, sx - 1);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            timeSpent = max(timeSpent, ppl[i][j]);

            if (zombie[i][j] == 1 && ppl[i][j] == 0)
            {
                untreated++;
            }
            // cout << ppl[i][j] << " ";
        }
        // cout << endl;
    }

    cout << timeSpent << endl;
    cout << untreated << endl;
}