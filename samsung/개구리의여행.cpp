#include <iostream>
#include <queue>

#define MAX_MAP 50
#define MAX_COST 1 << 29

#define SAFE 0
#define MONSTER 1
#define WALL 2

using namespace std;

struct node
{
    int energy, r, c;
};

int N;
int map[MAX_MAP][MAX_MAP], cost[6][MAX_MAP][MAX_MAP];
int move_r[4] = {-1, 1, 0, 0}, move_c[4] = {0, 0, -1, 1};

void print_cost()
{
    for (int k = 1; k <= 5; k++)
    {
        cout << "energy : " << k << '\n';
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (cost[k][i][j] != MAX_COST)
                    cout << cost[k][i][j] << "\t";
                else
                    cout << "_\t";
            }
            cout << "\n\n";
        }
        cout << "............................\n";
    }
    cout << "\n\n";
}

bool out_map(int r, int c)
{
    return (r < 0) || (c < 0) || (r >= N) || (c >= N);
}

void clear_cost()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 1; k <= 5; k++)
            {
                cost[k][i][j] = MAX_COST;
            }
        }
    }
}

void search(int start_r, int start_c)
{
    queue<node> q;

    cost[1][start_r][start_c] = 0;
    q.push(node{1, start_r, start_c});

    while (!q.empty())
    {
        node curr_n = q.front();
        q.pop();

        int curr_e = curr_n.energy, curr_r = curr_n.r, curr_c = curr_n.c;

        if (curr_e < 5)
        {
            if (cost[curr_e + 1][curr_r][curr_c] > cost[curr_e][curr_r][curr_c] + (curr_e + 1) * (curr_e + 1))
            {
                cost[curr_e + 1][curr_r][curr_c] = cost[curr_e][curr_r][curr_c] + (curr_e + 1) * (curr_e + 1);
                q.push(node{curr_e + 1, curr_r, curr_c});
            }
        }

        for (int e = curr_e - 1; e >= 1; e--)
        {
            if (cost[e][curr_r][curr_c] > cost[curr_e][curr_r][curr_c] + 1)
            {
                cost[e][curr_r][curr_c] = cost[curr_e][curr_r][curr_c] + 1;
                q.push(node{e, curr_r, curr_c});
            }
        }

        for (int m = 0; m < 4; m++)
        {
            bool jumpable = true;
            int n_r = curr_r, n_c = curr_c;
            for (int e = 0; e < curr_e; e++)
            {
                n_r += move_r[m];
                n_c += move_c[m];

                if (out_map(n_r, n_c))
                {
                    jumpable = false;
                    break;
                }

                if (map[n_r][n_c] == WALL)
                {
                    jumpable = false;
                    break;
                }
            }

            if (!jumpable)
                continue;

            if (map[n_r][n_c] != SAFE)
                continue;

            if (cost[curr_e][n_r][n_c] > cost[curr_e][curr_r][curr_c] + 1)
            {
                cost[curr_e][n_r][n_c] = cost[curr_e][curr_r][curr_c] + 1;
                q.push(node{curr_e, n_r, n_c});
            }
        }
    }
}

int get_cost(int dst_r, int dst_c)
{
    int min_cost = MAX_COST;
    for (int e = 1; e <= 5; e++)
    {
        if (min_cost > cost[e][dst_r][dst_c])
        {
            min_cost = cost[e][dst_r][dst_c];
        }
    }

    return (min_cost == MAX_COST) ? -1 : min_cost;
}

void init()
{
    char c;

    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> c;
            switch (c)
            {
            case '.':
                map[i][j] = SAFE;
                break;
            case 'S':
                map[i][j] = MONSTER;
                break;
            case '#':
                map[i][j] = WALL;
                break;
            }
        }
    }
}

int main()
{
    int k;
    queue<int> res_q;
    init();

    cin >> k;
    while (k--)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        clear_cost();
        search(r1 - 1, c1 - 1);
        res_q.push(get_cost(r2 - 1, c2 - 1));
    }

    while (!res_q.empty())
    {
        cout << res_q.front() << "\n";
        res_q.pop();
    }
    return 0;
}