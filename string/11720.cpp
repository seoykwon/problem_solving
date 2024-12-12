#include <iostream>

using namespace std;

int main()
{
    int t;
    int sum = 0;
    string num;

    cin >> t >> num;
    for (int i = 0; i < t; i++)
    {
        sum += (num[i] - '0');
    }
    cout << sum;
    return 0;
}