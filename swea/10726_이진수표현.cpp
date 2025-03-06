#include <iostream>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int tc;
    cin >> tc;

    for (int i = 1; i <= tc; i++)
    {
        int N, M;
        cin >> N >> M;

        // int bit = ((1 << (N + 1)) - 1) & M;
        int bit = ((1 << N) - 1) & M;

        // if (bit == ((1 << (N + 1)) - 1))
        if (bit == ((1 << N) - 1))
        {
            cout << "#" << i << " " << "ON" << '\n';
        }
        else
        {
            cout << "#" << i << " " << "OFF" << '\n';
        }
    }
}