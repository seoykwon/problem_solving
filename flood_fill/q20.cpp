#include <iostream>
#include <queue>
using namespace std;

int N;
int field[6][6];
int visitede[6][6];
int visiteda[6][6];
int ey, ex;
int ay, ax;
int ydir[] = {-1, 0, 1, 0, 0};
int xdir[] = {0, -1, 0, 1, 0};

struct node
{
    int y;
    int x;
    int time;
    char type;
};

queue<node> q;

void bfs()
{
    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        for (int i = 0; i < 5; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N || field[ny][nx])
                continue;

            if (now.type == 'e')
            {
                if (visitede[ny][nx])
                    continue;
                visitede[ny][nx] = 1;
            }
            else
            {
                if (visiteda[ny][nx])
                    continue;
                visiteda[ny][nx] = 1;
            }
            q.push({ny, nx, now.time + 1, now.type});
        }
    }
}

int main()
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
                field[i][j] = 1;
            }
        }
    }

    cin >> ey >> ex >> ay >> ax;

    visitede[ey][ex] = 1;
    q.push({ey, ex, 0, 'e'});

    visiteda[ay][ax] = 1;
    q.push({ay, ax, 0, 'a'});
    bfs();
}