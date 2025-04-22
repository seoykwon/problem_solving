#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

int ground[51][51];
int visited[51][51][6];
int N, Q;
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
// int jump = 1;

void init()
{
    for (int i = 0; i < 51; i++)
    {
        for (int j = 0; j < 51; j++)
        {
            ground[i][j] = 0;
        }
    }

    for (int i = 0; i < 51; i++)
    {
        for (int j = 0; j < 51; j++)
        {
            for (int k = 0; k <= 5; k++)
            {
                visited[i][j][k] = 0;
            }
        }
    }
}

void printG()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cout << ground[i][j] << " ";
        }
        cout << "\n";
    }
}

struct status
{
    int y, x;
    int time;
    int jump;
};

int travel(int r1, int c1, int r2, int c2)
{
    // jump
    queue<status> q;
    q.push({r1, c1, 0, 1});
    visited[r1][c1][1] = 1;

    while (!q.empty())
    {
        status now = q.front();
        q.pop();

        if (now.y == r2 && now.x == c2)
        {
            return now.time;
        }

        int jump = now.jump;

        // cannot land on (1) slimy rock
        // cannot pass over (2) cousin rock
        for (int d = 0; d < 4; d++)
        {
            int ny = now.y + (dir[d][0] * jump);
            int nx = now.x + (dir[d][1] * jump);

            if (ny < 1 || nx < 1 || ny > N || nx > N || visited[ny][nx][jump])
                continue;

            // cannot land on slimy rock or cousin rock
            if (ground[ny][nx] == -1 || ground[ny][nx] == 2)
                continue;

            // cannot pass over cousin rock
            if (jump > 1)
            {
                int flag = 0;

                for (int i = 1; i < jump; i++)
                {
                    int ty = now.y + (dir[d][0] * i);
                    int tx = now.x + (dir[d][1] * i);

                    if (ty < 1 || tx < 1 || ty > N || tx > N)
                        continue;

                    if (ground[ty][tx] == 2)
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 1)
                    continue;
            }

            visited[ny][nx][jump] = 1;
            q.push({ny, nx, now.time + (jump * jump), jump});

            // increase jump strength
            if (jump < 5)
            {
                int tmpjump = jump + 1;

                ny = now.y + (dir[d][0] * tmpjump);
                nx = now.x + (dir[d][1] * tmpjump);

                if (ny < 1 || nx < 1 || ny > N || nx > N || visited[ny][nx][tmpjump])
                    continue;

                // cannot land on slimy rock or cousin rock
                if (ground[ny][nx] == -1 || ground[ny][nx] == 2)
                    continue;

                q.push({ny, nx, now.time + (tmpjump * tmpjump), tmpjump});
                visited[ny][nx][tmpjump] = 1;
            }

            // decrease jump strength
            if (jump > 1)
            {
                for (int tmpjump = jump - 1; tmpjump >= 1; tmpjump--)
                {
                    ny = now.y + (dir[d][0] * tmpjump);
                    nx = now.x + (dir[d][1] * tmpjump);

                    if (ny < 1 || nx < 1 || ny > N || nx > N)
                        continue;

                    if (visited[ny][nx][tmpjump])
                        continue;

                    if (ground[ny][nx] == -1 || ground[ny][nx] == 2)
                        continue;

                    visited[ny][nx][tmpjump] = 1;
                    q.push({ny, nx, now.time + (tmpjump * tmpjump), tmpjump});
                }
            }
        }
    }
    return -1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    init();

    cin >> N;
    cin.ignore();

    for (int i = 1; i <= N; i++)
    {
        string str;
        getline(cin, str);

        stringstream st(str);

        for (int j = 1; j <= N; j++)
        {
            char rock;
            st >> rock;
            int fin = 0;

            // safe rock
            if (rock == '.')
            {
                fin = 1;
            }

            // slimy rock
            else if (rock == 'S')
            {
                fin = -1;
            }

            // cousin rock
            else if (rock == '#')
            {
                fin = 2;
            }

            ground[i][j] = fin;
        }
    }

    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        int ans = travel(r1, c1, r2, c2);

        cout << ans << '\n';

        // printG();
    }
}