#include <iostream>
using namespace std;

int N;
int cnt = 0;

void func(int num)
{
    // 기저 조건 -> N에 도달했다면, 하나의 경우의 수를 더찾았다!
    if (num == N)
    {
        cnt++;
        return;
    }

    // backtracking -> 만약 num이 N을 넘어간다면 가망이 없다
    if (num > N)
        return;

    // 수행
    // 재귀 구성 -> 1, 2, 3을 더해서 다음 조합으로 넘어가보자
    for (int i = 1; i <= 3; i++)
        func(num + i);
}

int main()
{
    // input
    cin >> N;

    // solve
    func(0);
    cout << cnt;
}