#include <iostream>

using namespace std;

int main()
{
    // freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        int N, M;
        cin >> N >> M;

        int check = (1 << N) - 1;

        // if (M &= check == check)
        /**
         * 위 코드를 연산자 우선순위에 따라 해석하면
         * M &= (check == check)로 동작해.
         * check == check는 항상 1이야.
         * 따라서 M &= 1이 실행되고, M값이 변경돼
         * 이 후 if (M)이 평가되는데, M이 0이 아니면 true, 0이면 false가 돼
         * 그런데 안에 bitwise구문에 괄호 안 쳐주면 오답이야
         */
        if ((M & check) == check)
        {
            cout << "#" << tc << " " << "ON" << "\n";
        }
        else
        {
            cout << "#" << tc << " " << "OFF" << "\n";
        }
    }
}