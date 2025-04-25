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

// ##################################
#include <iostream>
using namespace std;

bool check[30001];
int arr[30001], v[30001], m;
bool f(int dx, int r)
{
    for (int i = 0; i < m; i++)
    {
        int idx = i;
        while (idx + 1 < m && v[idx + 1] - v[i] <= dx)
            idx++;
        if (--r == -1)
            return false;
        i = idx;
    }
    return true;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int testcase, num = 0, x;
    cin >> testcase;
    while (testcase--)
    {
        int mode;
        cin >> mode;
        if (mode == 100)
        {
            cin >> num;
            for (int i = 1; i <= num; i++)
                cin >> arr[i], check[i] = true;
        }
        else if (mode == 200)
        {
            cin >> x;
            arr[++num] = x;
            check[num] = true;
        }
        else if (mode == 300)
        {
            cin >> x;
            check[x] = false;
        }
        else if (mode == 400)
        {
            cin >> x;
            m = 0;

            for (int i = 1; i <= num; i++)
            {
                if (check[i])
                    v[m++] = arr[i];
            }
            if (!m)
            {
                cout << "0\n";
                continue;
            }
            int left = 0, right = v[m - 1] - v[0];
            while (right - left > 1)
            {
                int mid = (left + right) / 2;
                f(mid, x) ? right = mid : left = mid + 1;
            }
            cout << (f(left, x) ? left : right) << '\n';
        }
    }
    return 0;
}