#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node
{
    int y;
    int x;
};

int board[8][9];
int visited[8][9];
queue<Node> person1;

void input()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            char tmp;
            cin >> tmp;

            if (tmp == '_')
            {
                board[i][j] = -1;
            }
            else if (tmp == '#')
            {
                board[i][j] = 0;
            }
        }
    }
    memset(visited, -1, sizeof(visited));
}

void bfs(int y, int x)
{
    queue<Node> q;
    q.push({y, x});
    visited[y][x] = 0;

    int ydir[] = {-1, 0, 1, 0};
    int xdir[] = {0, -1, 0, 1};

    while (!q.empty())
    {
        Node now = q.front();
        person1.push(now);
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 8 || nx >= 9 || visited[ny][nx] != -1)
                continue;

            if (board[ny][nx] == -1)
                continue;

            visited[ny][nx] = 0;
            q.push({ny, nx});
        }
    }
    // debugging. as i need to find the shortest distance, needed to initialize with big values
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (visited[i][j] == -1)
            {
                visited[i][j] = 21e8;
            }
        }
    }

    while (!person1.empty())
    {
        Node now = person1.front();
        person1.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 8 || nx >= 9)
                continue;

            if (visited[ny][nx] < visited[now.y][now.x] + 1)
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;

            if (board[ny][nx] == 0)
            {
                // found!
                cout << visited[ny][nx] - 1;
                return;
            }

            person1.push({ny, nx});
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    input();

    for (int i = 0; i < 8; i++)
    {
        int flag = 0;
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 0 && visited[i][j] == -1)
            {
                bfs(i, j);
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
    }
    // cout << "done";
    return 0;
}

// 서영아 지피티 사용하지 않고 스스로 디버깅한 거 칭찬해
// 계속 이렇게만 해보자! 그러면 원하는 곳을 갈 수 있을 것이라 믿어
