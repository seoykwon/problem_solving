#include <iostream>
#include <stdlib.h>
#include <queue>

using namespace std;

int T;
int N;
struct tree
{
    int height;
    int day;
};
int ans = 0;
int goal = 0;

tree trees[101];

void cnt()
{
    int today = 0;

    for (int i = 0; i < N; i++)
    {
        if (trees[i].height == goal)
            continue;

        tree t = trees[i];

        while (1)
        {
            today++;

            int diff = goal - t.height;

            if (today % 2 != 0)
            {
                if (diff != 2)
                    t.height += 1;
                else
                {
                    trees[i + 1].height += 1;
                }
            }
            else
            {
                if (diff != 1)
                    t.height += 2;
                else
                {
                    trees[i + 1].height += 2;
                }
            }

            if (t.height == goal)
            {
                ans = max(ans, today);
                break;
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;
        ans = 0;
        goal = 0;

        for (int i = 0; i < N; i++)
        {
            int tmp;
            cin >> tmp;
            trees[i] = {tmp, 0};

            goal = max(goal, tmp);
        }

        cnt();

        cout << "#" << tc << " " << ans << endl;
    }
}