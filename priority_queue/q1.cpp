#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int field[1000][1000] = {0};
int b, y, x;

struct node
{
    int bomb;
    int y;
    int x;
};

struct cmp
{
    bool operator()(node &left, node &right)
    {
        return left.bomb > right.bomb;
    }
};

priority_queue<node, vector<node>, cmp> pq;

int yd[4] = {1, 0, -1, 0};
int xd[4] = {0, -1, 0, 1};
// memset(field, 0, sizeof(field));

void explode()
{
    while (!pq.empty())
    {
        auto now = pq.top();
        pq.pop();

        if (field[now.y][now.x] == 0)
        {
            field[now.y][now.x] = 1;

            for (int i = 0; i < 4; i++)
            {
                int ny = now.y + yd[i];
                int nx = now.x + xd[i];

                if (ny < 0 || nx < 0 || ny >= 1000 || nx >= 1000)
                    continue;

                field[ny][nx] = 1;
            }

            cout << now.bomb << endl;
            return;
        }
    }

    cout << -1 << endl;
}

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> N >> M;

    for (int i = 0; i < N + M; i++)
    {
        cin >> b;

        if (b == 0)
        {
            explode();
            continue;
        }
        cin >> y >> x;

        pq.push({b, y, x});
    }
}

// #####################################
#include <queue>
#include <iostream>

using namespace std;

int MAP[1000][1000];
priority_queue<pair<int, pair<int, int>>> pq;

void setBoom(int num)
{
    int row, col;
    cin >> row >> col;
    pq.push({-num, {row, col}});
}

void activeBoom()
{
    int num;
    pair<int, int> pos;

    do
    {
        if (pq.empty())
        {
            cout << -1 << endl;
            return;
        }
        num = -pq.top().first;
        pos = pq.top().second;
        pq.pop();
    } while (MAP[pos.first][pos.second]);
    int dr[] = {-1, 1, 0, 0, 0};
    int dc[] = {0, 0, -1, 1, 0};

    for (int i = 0; i < 5; i++)
    {
        int nr = pos.first + dr[i];
        int nc = pos.second + dc[i];

        if (nr < 0 || nc < 0 || nr >= 1000 || nc >= 1000)
            continue;

        MAP[nr][nc] = num;
    }
    cout << num << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N + M; i++)
    {
        int type;
        cin >> type;
        if (type)
            setBoom(type);
        else
            activeBoom();
    }
}