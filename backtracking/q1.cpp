#include <iostream>
using namespace std;

int sum = 0;
void func(int num)
{
    // 기저 조건
    if (num == 0)
        return;

    // 수행
    sum += num % 10;

    // 재귀 구성
    func(num / 10);
}

int main()
{
    int num;
    cin >> num;
    func(num);
    cout << sum;
}