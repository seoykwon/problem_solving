#include <iostream>
#include <string>
#include <set>
using namespace std;

set<string> M; // set 자료구조.
string S;      // 입력받을 문자열.

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;

    int i, j, l = S.length(); // 반복문 내에서 매번 length()를 수행하는 것보다 한 번만 담아주자.

    for (i = 0; i < l; i++)                   // 0번째 인덱스부터 끝까지 반복.
        for (j = i; j < l; j++)               // 현재(i)인덱스부터 끝까지 반복.
            M.insert(S.substr(i, j - i + 1)); // j-i+1을 하면 현재(i)부터 끝(l)까지의 길이가 된다.

    cout << M.size(); // 마지막에 set에 담겨있는 요소의 개수를 출력하면 완성~
}