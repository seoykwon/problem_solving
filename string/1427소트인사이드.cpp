#include <iostream>
#include <algorithm>
using namespace std;

string num;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> num;
    sort(num.begin(), num.end(), greater<char>());
    cout << num;
    return 0;
}