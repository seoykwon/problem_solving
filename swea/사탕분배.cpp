#include <iostream>

using namespace std;

int get2Power(int cnt, int mod) {
    long long res = 1;
    long long num = 2;
    while (cnt > 0) {
        if (cnt % 2 == 1) {
            res = (res * num) % mod;
        }
        num = (num * num) % mod;
        cnt /= 2;
    }
    return (int)res;
}

long long solution(int num1, int num2, int cnt) {
    int sum = num1 + num2;
    int max = sum / 2;
    long long result = ((long long) get2Power(cnt, sum) * (long long)num1) % sum;
    return result > max ? sum - result : result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        int num1, num2, cnt;
        cin >> num1 >> num2 >> cnt;
        cout << "#" << tc << " " << solution(num1, num2, cnt) << "\n";
    }

    return 0;
}