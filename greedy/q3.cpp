#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int minTotalPrice = INT_MAX;
int minSet = INT_MAX;
int minEach = INT_MAX;

int minPrice(int set, int each, int totalnum)
{
    if (set < minSet)
    {
        minSet = set;
    }
    if (each < minEach)
    {
        minEach = each;
    }

    float seteach = (float)minSet / 6.0;

    int tmpPrice = 0;

    int remainder = 0;

    if (seteach < minEach)
    {
        remainder = totalnum % 6;
        int quotient = totalnum / 6;
        tmpPrice += quotient * minSet;
    }
    if (remainder)
    {
        if (minSet < (minEach * remainder))
        {
            tmpPrice += set;
        }
        else
        {
            tmpPrice += remainder * minEach;
        }
    }
    else if (minEach <= seteach)
    {
        tmpPrice += minEach * totalnum;
    }

    if (minTotalPrice > tmpPrice)
    {
        minTotalPrice = tmpPrice;
    }

    return minTotalPrice;
}

int main()
{
    int n;
    int m;
    cin >> n >> m;

    int price = 0;

    while (m--)
    {
        int set, each;
        cin >> set >> each;

        price = minPrice(set, each, n);
    }
    cout << price;
}