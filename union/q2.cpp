#include <iostream>

using namespace std;

int arr[1001][1001] = {
    0,
};
int n;
int parent[1001];
int flag = 0;

void input()
{

    // 0. setting parents is necessary
    for (int i = 0; i < 1001; i++)
    {
        parent[i] = i; // every node's parent is itself (proprietorship)
    }

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
}

int Find(int A)
{
    // when the representative is itself
    if (A == parent[A])
        return A;

    return parent[A] = Find(parent[A]);
}

void Union(int A, int B)
{
    // unionize two groups

    // find the root of A
    int rootA = Find(A);
    // find the root of B
    int rootB = Find(B);

    // if their roots are the same
    if (rootA == rootB)
    {
        cout << "WARNING" << endl;
        flag = 1;
        return;
    }
    // update the group information
    parent[rootB] = rootA;
}

int main()
{
    input();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] == 1 && i < j)
            {
                if (flag)
                {
                    return 0;
                }
                Union(i, j);
            }
        }
    }

    if (!flag)
    {
        cout << "STABLE";
    }
}