#include <iostream>
#include <string>

int main()
{
    freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    int total = (1 << 10) - 1;

    for (int tc = 1; tc <= T; tc++)
    {
        int N;
        cin >> N;

        int visited = 0;
        int count = 0;

        while (1)
        {
            // N * count 값을 문자열로 표현한 것것
            string strNum = to_string(N * (++count));

            for (char c : strNum)
            {
                int num = c - '0';
                visited |= (1 << num);
            }

            if (visited == total)
                break;
        }

        cout << "#" << tc << " " << N * count << "\n";
    }

    return 0;
}