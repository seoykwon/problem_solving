#include <iostream>

using namespace std;

/*
6 4
1 2
3 4
5 6
2 4
*/
// int Find(int A)
// {
//     // when the representative is itself
//     if (A == parent[A])
//         return A;

//     // find the representative of certain group
//     // recursive finding until the code reaches the root node
//     int root = Find(parent[A]);

//     // answering the question of who's the parent
//     return root;
// }

// // upgrade Find
// int Find(int A)
// {
//     // when the representative is itself
//     if (A == parent[A])
//         return A;

//     // find the representative of certain group
//     // recursive finding until the code reaches the root node
//     int root = Find(parent[A]);
//     parent[A] = root; // direct connection with root

//     // answering the question of who's the parent
//     return root;
// }

// upgrade Find second step (compress)
// why compression?
// union find is only interested in the roots, not the intermediate ones
// we want to cut the process short
// disjoint set (if they have no element in common)
// unionizing groups exist
// however, no disunionization exist
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

int parent[20];
int main()
{
    // 0. setting parents is necessary
    for (int i = 0; i < 20; i++)
    {
        parent[i] = i; // every node's parent is itself (proprietorship)
    }

    // 1. save data
    int cntNode, cntQuery;
    cin >> cntNode >> cntQuery;
    for (int i = 0; i < cntQuery; i++)
    {
        int A, B;
        cin >> A >> B;
        Union(A, B);
    }
}