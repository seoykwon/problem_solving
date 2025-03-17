#include <iostream>
#include <string>

using namespace std;

int main()
{
    // freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;

    // int check = (1 << 9) - 1;
    int check = (1 << 10) - 1;

    for (int tc = 1; tc <= T; tc++)
    {
        int N;
        cin >> N;

        int mul = 0;
        int seenDigits = 0;

        while (seenDigits != check)
        {
            mul++;
            int sheep = N * mul;

            string str = to_string(sheep);
            for (char c : str)
            {
                seenDigits |= (1 << (c - '0'));
            }
        }
        cout << "#" << tc << " " << mul * N << "\n";
    }
}