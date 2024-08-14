#include <iostream>

using namespace std;

int charger;
int carline;
int flag = 0;
int parent[100001];

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
        return;

    parent[rootB] = parent[rootA];
}

int main()
{
    cin >> charger >> carline;

    for (int i = 1; i <= charger; i++)
    {
        parent[i] = i;
    }

    int max_cars = 0;

    for (int i = 0; i < carline; i++)
    {
        int car;
        cin >> car;

        // Find the highest available charger the car can use
        int available_charger = Find(car);

        if (available_charger > 0)
        {
            max_cars++;
            // Union the current charger with the one below it
            Union(available_charger - 1, available_charger);
        }
        else
        {
            break; // No available charger
        }
    }

    cout << max_cars << endl;

    // DAT
    // for (int i = 0; i < carline; i++)
    // {
    //     int car_ver = line[i];
    //     int flag = 0;
    //     for (int j = car_ver; j > 0; j--)
    //     {
    //         if (!version[j])
    //         {
    //             version[j] = 1;
    //             flag = 1;
    //             break;
    //         }
    //     }
    //     if (flag == 0)
    //     {
    //         cout << i << endl;
    //         return 0;
    //     }
    // }
    return 0;
}