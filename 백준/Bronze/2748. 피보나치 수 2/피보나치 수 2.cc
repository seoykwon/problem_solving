#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    // 피보나치 수를 저장할 배열
    long long fib[91] = {0, 1};  // 0번째와 1번째 피보나치 수 초기화

    // 2번째부터 n번째까지 피보나치 수 계산
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // n번째 피보나치 수 출력
    cout << fib[n] << endl;

    return 0;
}
