#include <iostream>

using namespace std;
int parent[600];

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
        return;

    // update the group information
    parent[rootB] = rootA;
}

int main()
{
    // 0. setting parents is necessary
    for (int i = 0; i < 600; i++)
    {
        parent[i] = i; // every node's parent is itself (proprietorship)
    }

    // 1. save data
    int cntNode, cntQuery;
    cin >> cntNode >> cntQuery;
    for (int i = 0; i < cntQuery; i++)
    {
        int A, B, mode;
        cin >> mode >> A >> B;
        if (mode == 1)
        {
            Union(A, B);
        }
        else
        {
            int a = Find(A);
            int b = Find(B);

            if (a == b)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}