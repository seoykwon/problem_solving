#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    unordered_set<int> items;
    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        items.insert(value);
    }

    int soldItemsCount = 0;

    for (int i = 0; i < m; i++)
    {
        int bid;
        cin >> bid;

        int neededValue = -bid;

        if (items.count(neededValue) > 0)
        {
            soldItemsCount++;
            items.erase(neededValue);
        }
    }
    cout << soldItemsCount << endl;
}