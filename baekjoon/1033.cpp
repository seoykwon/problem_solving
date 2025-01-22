#include <iostream>
#include <vector>

using namespace std;

struct proportion
{
    int nominator;
    int denominator;
    int nom;
    int denom;
    float div;
};
int n;
vector<proportion> v;
int a, b, p, q;

void input()
{
    freopen("input.txt", "r", stdin);

    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b >> p >> q;
        v.push_back({a, b, p, q, (p / q)});
    }
}

int main()
{
    input();
}