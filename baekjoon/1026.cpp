#include <iostream>
#include <algorithm>
using namespace std;
int N, Res = 0, _A[50], _B[50];
// 오름차순 정렬
bool Greater(int a, int b)
{
    return a > b;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> _A[i];
    for (int i = 0; i < N; i++)
        cin >> _B[i];
    sort(_A, _A + N, Greater);
    sort(_B, _B + N);
    for (int i = 0; i < N; i++)
        Res += (_B[i] * _A[i]);
    cout << Res;
    return 0;
}