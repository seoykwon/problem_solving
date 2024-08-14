#include <iostream>
#include <cmath>

using namespace std;

int parent[3000];
int t, n, r;
int cnt[3000];

struct coord
{
    int y;
    int x;
    int r;
};

coord base[3000];

int Find(int a)
{
    if (a == parent[a])
    {
        return a;
    }
    return parent[a] = Find(parent[a]);
}

void Union(int a, int b)
{
    int rootA = Find(a);
    int rootB = Find(b);

    if (rootA == rootB)
    {
        return;
    }
    parent[rootB] = parent[rootA];
}

int distance(coord a, coord b)
{
    int r = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return r;
}

int main()
{
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        cin >> n;
        int group = 0;

        // cout << "i : " << i << endl;
        // cout << "n: " << n << endl;

        for (int j = 0; j < n; j++)
        {
            int col, row, radius;
            cin >> col >> row >> radius;

            base[j] = {row, col, radius};

            parent[j] = j;

            cnt[j] = 0;
        }

        for (int s = 0; s < n; s++)
        {
            for (int si = s + 1; si < n; si++)
            {
                int dis = distance(base[s], base[si]); // r**2

                // cout << "s : " << s << ", si : " << si << endl;
                // cout << "dis: " << dis << endl;

                if (dis <= (base[s].r + base[si].r) * (base[s].r + base[si].r))
                {
                    // if (s < si)
                    // {
                    //     Union(s, si);
                    // }
                    // else
                    // {
                    //     Union(si, s);
                    // }
                    Union(s, si);
                }
            }
        }

        for (int j = 0; j < n; j++)
        {
            cnt[Find(parent[j])]++;
            // cout << "parent of " << j << parent[j] << endl;
            // cout << "cnt of parent j " << cnt[parent[j]] << endl;
        }

        for (int j = 0; j < n; j++)
        {
            if (cnt[j] > 0)
            {
                group++;
            }
            // cout << "cnt: " << j << " is " << cnt[j] << group << endl;
        }

        cout << group << endl;
    }
}

// do not use sqrt
// when counting groups, use minimum path by using Find
// Union function does not change its result by the order of two parameters