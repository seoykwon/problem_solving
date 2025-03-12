#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * C++에서 cout을 사용하여 반복적으로 출력하는 경우, 각 출력마다 콘솔에 데이터를 바로 출력하게 됩니다.
 * 이로 인해 입출력 속도가 상대적으로 느려질 수 있습니다.
 * stringstream을 사용하면 중간 결과를 메모리 내의 문자열에 저장해두고, 마지막에 한 번에 출력할 수 있어 효율적입니다.
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;

    stringstream sb;

    for (int tc = 1; tc <= TC; tc++)
    {
        int N;
        cin >> N;

        sb << "#" << tc << " ";

        priority_queue<int> pq;

        for (int i = 0; i < N; i++)
        {
            int op;
            cin >> op;

            if (op == 1)
            {
                int input;
                cin >> input;
                pq.push(input);
            }
            else
            {
                int output = -1;
                if (!pq.empty())
                {
                    output = pq.top();
                    pq.pop();
                }
                sb << output << " ";
            }
        }

        sb << "\n";
    }

    cout << sb.str();

    return 0;
}
