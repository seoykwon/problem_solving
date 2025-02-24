#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;

    stringstream sb;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        sb << "#" << tc << " ";
        
        priority_queue<int> pq;

        for (int i = 0; i < N; i++) {
            int op;
            cin >> op;

            if (op == 1) {
                int input;
                cin >> input;
                pq.push(input);
            } else {
                int output = -1;
                if (!pq.empty()) {
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
