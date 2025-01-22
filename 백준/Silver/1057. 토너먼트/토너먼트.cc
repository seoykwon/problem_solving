#include <iostream>
using namespace std;

int main()
{

    int n, kim, lim;
    cin >> n >> kim >> lim;

    int round = 0;

    while (kim != lim)
    {
        kim = (kim + 1) / 2;
        lim = (lim + 1) / 2;
        round++;
    }
    cout << round << '\n';
    return 0;
}