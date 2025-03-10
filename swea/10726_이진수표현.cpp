#include <iostream>

using namespace std;

int main()
{
    freopen("sample_input.txt", "r", stdin);
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++)
    {
        int n, m;
        cin >> n >> m;

        // n + 1 이동이 아니라 n 이동이다
        int bit = (1 << n) - 1;
        int chk = (bit & m);
        // & (비트 and)
        // |= (비트 OR)

        if (chk == bit)
        {
            cout << "#" << t << " " << "ON" << "\n";
        }
        else
        {
            cout << "#" << t << " " << "OFF" << "\n";
        }
    }
}