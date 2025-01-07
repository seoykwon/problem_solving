#include <iostream>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    int t;

    cin >> t;

    while (t--)
    {
        int ax, ay, ar, bx, by, br;
        cin >> ax >> ay >> ar >> bx >> by >> br;

        int d = (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
        int cond1 = (ar - br) * (ar - br);
        int cond2 = (ar + br) * (ar + br);

        if (d == 0)
        {
            if (cond1 == 0)
                cout << "-1" << '\n';
            else
                cout << "0" << '\n';
        }
        else if (d == cond1 || d == cond2)
            cout << "1" << '\n';
        else if (cond1 < d && d < cond2)
            cout << "2" << '\n';
        else
            cout << "0" << '\n';
    }
}