#include <iostream>

using namespace std;

int gcdRecursion(int a, int b)
{
    if (b == 0)
        return a;

    return gcdRecursion(b, a % b);
}

int main()
{
    string s;

    cin >> s;

    int index = s.find(':');
    int n = stoi(s.substr(0, index));
    int m = stoi(s.substr(index + 1, s.length()));

    int g = gcdRecursion(max(n, m), min(n, m));

    cout << n / g << ':' << m / g << '\n';

    return 0;
}