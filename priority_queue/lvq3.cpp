#include <iostream>
#include <queue>

using namespace std;

int n;
int bombf[1000][1000];

struct bomb
{
    int y;
    int x;
    int weight;
};

struct cmp
{
    bool operator()(bomb a, bomb b)
    {
        return a.weight > b.weight;
    }
};

priority_queue<bomb, vector<bomb>, cmp> pq;

void explode(int y, int x)
{
    int ydir[4] = {1, 0, -1, 0};
    int xdir[4] = {0, -1, 0, 1};

    for (int i = 0; i < 4; i++)
    {
        int ny = y + ydir[i];
        int nx = x + xdir[i];

        if (ny < 0 || ny >= n || nx < 0 || nx >= n)
            continue;

        bombf[ny][nx] = 0;
    }
}

bool clear()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (bombf[i][j] > 0)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int tmp;
            cin >> tmp;
            bombf[i][j] = tmp;
            bomb b = {i, j, tmp};
            pq.push(b);
        }
    }

    while (!pq.empty())
    {
        bomb now = pq.top();
        pq.pop();

        int y = now.y;
        int x = now.x;
        int w = now.weight;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (bombf[i][j] == now.weight)
                {
                    bombf[y][x] = 0;
                    explode(y, x);
                }
            }
        }

        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         cout << bombf[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        if (clear())
        {
            cout << now.weight << "초";
            break;
        }
    }
}