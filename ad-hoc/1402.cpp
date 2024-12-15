#include <iostream>
#include <vector>

typedef long long ll;
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int tc;
    cin >> tc;

    while (tc--)
    {
        ll a, b;
        cin >> a >> b;
        cout << "yes" << '\n';
    }
}

/**
 * A = a1 * a2 * a3 * ... * an으로 했을 때 A' = a1 + a2 + a3 + ... + an이면 A는 A'가 될 수 있다고 한다.
만약 A를 A * 1이라고 표현했을 때 A' = A + 1이 된다.
 
이를 반복하면
A = A * 1 * 1일 때는 A' = A + 2 ....
즉, A는 A보다 큰 모든 수는 다 가능하게 된다!
 
음수의 경우는 어떨까?
 
A = A * -1 * -1 * 1이라는 식으로 표현할 수 있다.
이 경우에는 A'이 A - 1 - 1 + 1이 되는데 즉 A' = A - 1이 된다..
이런 식으로 A는 A보다 작은 모든 수도 다 가능하다는 것이다..
 
결론적으로 어떠한 수가 A, B로 와도 모든 경우가 다 가능하다는 것이다!!
출처: https://w00ye0l.tistory.com/56 [열이의 개발블로그:티스토리]
 */