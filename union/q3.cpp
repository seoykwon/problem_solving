#include <iostream>

using namespace std;

int n;
int parent[26];
int cnt[26] = {
    0,
};
int group = 0;
int indi = 0;

void input()
{
    cin >> n;

    for (int i = 0; i < 26; i++)
    {
        parent[i] = i;
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
    // find the root of A
    int rootA = Find(A);
    // find the root of B
    int rootB = Find(B);

    // if their roots are the same
    if (rootA == rootB)
    {
        return;
    }
    // update the group information
    parent[rootB] = rootA;
}

int convert(char tmp)
{
    int c = tmp - 'A';
    return c;
}

int main()
{
    input();
    for (int i = 0; i < n; i++)
    {
        char a, b;
        cin >> a >> b;
        int c = convert(a);
        int d = convert(b);
        Union(c, d);
    }

    for (int i = 0; i < 26; i++)
    {
        cnt[Find(i)]++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (cnt[i] == 1)
        {
            indi++;
        }
        else if (cnt[i] > 1)
        {
            group++;
        }
    }

    cout << group << endl;
    cout << indi << endl;
}