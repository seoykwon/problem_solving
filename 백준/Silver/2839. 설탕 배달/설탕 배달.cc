#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int result = -1; // 결과를 초기화 (-1은 실패의 의미)
    
    // 5킬로그램 봉지를 최대한 사용하며, 남은 설탕을 3킬로그램 봉지로 나눌 수 있는지 확인
    for (int i = n / 5; i >= 0; i--) {
        int remaining = n - (i * 5); // 5킬로그램 봉지로 처리한 후 남은 설탕
        if (remaining % 3 == 0) {    // 남은 설탕이 3으로 나누어 떨어지는 경우
            result = i + (remaining / 3); // 봉지의 총 개수
            break; // 가장 적은 봉지로 해결되므로 루프 종료
        }
    }

    cout << result << '\n'; // 결과 출력
    return 0;
}
