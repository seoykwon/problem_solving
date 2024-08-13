#include <iostream>

using namespace std;

/*
11 9
0 2 4 6 8 10 1 5 9

1 1
2 1
3 1
4 1
5 1
6 1
5 3
4 3
3 3
*/

int width, n;
int arr[1000000];
int order[1000000];
int parent[1000000];
int cnt[1000000];

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

    parent[rootB] = rootA;
}

void check(int rock)
{
    int left = rock - 1;
    int right = rock + 1;

    if (left >= 0 && left < width)
    {
        if (arr[left] == 1)
        {
            Union(left, rock);
        }
    }
    if (right >= 0 && right < width)
    {
        if (arr[right] == 1)
        {
            Union(rock, right);
        }
    }
}

int main()
{

    int size = 0;
    cin >> width >> n;

    for (int i = 0; i < width; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        int number = 0;
        int x;
        cin >> x;
        arr[x] = 1;
        order[i] = x;
        check(x);

        for (int w = 0; w < width; w++)
        {
            cnt[w] = 0;
        }

        for (int j = 0; j < i + 1; j++)
        {
            cnt[Find(order[j])]++;
        }

        for (int s = 0; s < width; s++)
        {
            // cout << "cnt[s]: " << cnt[s] << endl;
            if (cnt[s] > 0)
            {
                number++;
            }
            if (cnt[s] > size)
            {
                size = cnt[s];
            }
        }
        cout << number << " " << size << endl;
    }

    return 0;
}