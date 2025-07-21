// 2025-07-22 돌게임
/*
#include <iostream>
#include <string>
using namespace std;

string dp(int curN, string name){
    if (curN < 3) {
        return name;
    }

    if (name == "SK"){
        dp(curN - 1, "CY");
        dp(curN - 3, "CY");
    }
    else {
        dp(curN - 1, "SK");
        dp(curN - 3, "SK");
    }

    return "";
}

int main(){
    freopen("input.txt", "r", stdin);
    int N;
    cin >> N;

    string winner = dp(N, "SK");

    cout << winner << '\n';
}

현재 코드의 문제점
- dp(curN - 1, "CY")와 dp(curN - 3, "CY") 는 호출되지만 결과값을 사용하지 않음
- 반환값이 없고, 재귀호출 결과가 승패에 어떻게 영향을 주는지 판단하지 않음
- 결국 항상 ""만 반환하고 아무 결과도 계산하지 못함

나의 재귀 로직이 작동하려면 dp() 함수가 재귀적으로 승리/패배를 판단하고 반환해야 함. 
단순히 재귀호출만 하고 반환값 없이 끝내면 아무 의미가 없음. 
문제 해결에는 반드시 승패 정보를 기반으로 로직을 구성해야 함.
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<bool> dp(N + 1, false); // dp[i] = true면 SK가 이김

    dp[1] = true; // SK
    if (N >= 2) dp[2] = false; // CY
    if (N >= 3) dp[3] = true; // SK

    for (int i = 4; i <= N; i++){
        // 현재 차례의 사람이 이기려면, 다음 차례가 지는 경우가 있어야 함
        dp[i] = !dp[i - 1] || !dp[i - 3];
    }

    cout << (dp[N] ? "SK" : "CY") << '\n';
    return 0;
}