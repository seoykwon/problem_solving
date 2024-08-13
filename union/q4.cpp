#include <iostream>
#include <string>

using namespace std;

int n;
int population[24] = {0};
int cases;
int parent[25];
int flag = 0;

int convert(int tmp)
{
    int x = tmp - 'A';
    return x;
}

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

int War(int a, int b)
{
    int parentA = Find(a);
    int parentB = Find(b);

    int cntA = 0;
    int cntB = 0;
    int popA = 0;
    int popB = 0;

    for (int i = 0; i < n; i++)
    {
        if (parent[i] == parentA)
        {
            cntA++;
            popA += population[i];
        }
        else if (parent[i] == parentB)
        {
            cntB++;
            popB += population[i];
        }
    }

    if (popA > popB)
    {
        return cntB;
    }
    else if (popA < popB)
    {
        return cntA;
    }
    return cntA + cntB;
}

int main()
{
    cin >> n;
    int dead = 0;

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> population[i];
    }

    cin >> cases;
    for (int i = 0; i < cases; i++)
    {
        string s;
        char a, b;
        cin >> s >> a >> b;
        int c = convert(a);
        int d = convert(b);

        if (s == "alliance")
        {
            Union(c, d);
        }
        else if (s == "war")
        {
            dead += War(c, d);
        }
    }

    cout << n - dead;
}