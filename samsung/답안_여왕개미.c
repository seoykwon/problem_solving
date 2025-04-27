#include <stdio.h>
#include <stdbool.h>

#define MAX (20000 + 10000 + 500)
#define INF (1000000000)

#define INIT (100)
#define CREATE (200)
#define REMOVE (300)
#define FIND (400)

int Q;
int N;

int house[MAX];
bool isBroken[MAX];
int hcnt = 0;

void input()
{
    scanf("%d", &N);

    hcnt = 1;
    for (int i = 0; i < N; i++)
    {
        int x;
        scanf("%d", &x);
        house[hcnt++] = x;
    }

    for (int i = 0; i < MAX; i++)
        isBroken[i] = false;
}

void createAntHouse(int pos)
{
    house[hcnt++] = pos;
}

void removeAntHouse(int index)
{
    isBroken[index] = true;
}

int binarysearch(int r)
{
    int left, right, ans;

    left = 0;
    right = INF;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        int antCount, start, prevPos;

        antCount = prevPos = 0;
        for (int i = 1; i < hcnt; i++)
        {
            if (isBroken[i] == false)
            {
                prevPos = house[i];
                start = i + 1;
                break;
            }
        }

        antCount = 1;

        for (int i = start; i < hcnt; i++)
        {
            if (isBroken[i] == true)
                continue;

            int curPos = house[i];

            if (curPos - prevPos <= mid)
                continue;

            prevPos = curPos;
            antCount++;
        }

        if (antCount <= r)
        {
            ans = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    return ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    scanf("%d", &Q);

    for (int q = 0; q < Q; q++)
    {
        int COMMAND;

        scanf("%d", &COMMAND);

        if (COMMAND == INIT)
            input();

        else if (COMMAND == CREATE)
        {
            int p;

            scanf("%d", &p);

            createAntHouse(p);
        }

        else if (COMMAND == REMOVE)
        {
            int q;

            scanf("%d", &q);

            removeAntHouse(q);
        }

        else if (COMMAND == FIND)
        {
            int r;

            scanf("%d", &r);

            printf("%d\n", binarysearch(r));
        }
    }

    return 0;
}