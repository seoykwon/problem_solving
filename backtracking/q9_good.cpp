#include <iostream>
using namespace std;

int N;
int flag = 0;
// index : index번째(순서)
// value : index번째 좋은 수열의 요소(값)
int path[100];

void printpath(int level)
{
    for (int i = 0; i < level; i++)
        cout << path[i];
}

// level번째까지 구성된 수열이 "좋은 수열"인지 판단하는 함수
// 작은 숫자부터 수열을 만들어본다 -> 그러므로 이 test를 통과하면,
// level번째까지의 수열은 "가장 작은 좋은 수열"의 일원임이 보장된다.
bool isGood(int level)
{
    // 체크해야할 길이
    int len = (level + 1) / 2;
    for (int i = 1; i <= len; i++)
    {
        int cnt = 0;
        // 이동 간격
        for (int j = 0; j < i; j++)
        {
            if (path[level - j] == path[level - j - i])
                cnt++; // 인접 수열에 동일한 편성으로 이루어진 값이 1개가 더 있다.
        }
        // 만약 인접한 수열이 완벽하게 일치한다면
        if (cnt == i)
            return false; // 좋은 수열이 아니다.
    }
    return true;
}

void func(int level)
{
    // backtracking -> 만약 이미 좋은 수열을 찾은 적이 있다면,
    // 이것보다 더 큰 좋은 수열은 찾아볼 필요가 없다. (가망이 없다)
    if (flag == 1)
        return;

    // 기저 조건 -> N크기(길이)의 좋은 수열을 만들었다면 끝
    if (level == N)
    {
        flag = 1; // 가장 작은 좋은 수열을 찾았다!
        printpath(level);
        return;
    }

    // 재귀 구성 -> 1, 2, 3을 더해보면서 수열을 만들수 있다.
    for (int i = 1; i <= 3; i++)
    {
        path[level] = i;     // level번째 숫자를 i로 선정한다
        if (isGood(level))   // 만약 level번까지 좋은 수열임이 보장된다면
            func(level + 1); // 다음 좋은 수열을 뽑으러 간다
        path[level] = 0;     // level번째 결정된 숫자 초기화
    }
}

int main()
{

    // input
    cin >> N;

    // solve
    func(0);
}