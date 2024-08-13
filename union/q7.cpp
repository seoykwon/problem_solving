#include <iostream>

using namespace std;

int charger;
int carline;
int line[100000];
int flag = 0;
int parent[100000];

int Find(int a)
{
    if (a == parent[a])
    {
        return a;
    }
    return parent[a] = Find(parent[a]);
}

int main()
{
    cin >> charger >> carline;

    for (int i = 0; i < carline; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < carline; i++)
    {
        int car;
        cin >> car;
        line[i] = car;
    }
}