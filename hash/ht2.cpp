/*
unordered_set
목적: 중복되지 않는 요소들을 저장하는 데 사용됩니다. 즉, 집합을 구현합니다.
구조: 값만 저장하며, 각 값의 유일성만을 보장합니다.
기본 연산:
삽입 (insert): O(1) 평균 시간 복잡도
삭제 (erase): O(1) 평균 시간 복잡도
검색 (find): O(1) 평균 시간 복잡도
사용 예: 특정 값이 집합에 존재하는지 여부를 확인할 때 사용됩니다. 예를 들어, 중복된 데이터를 제거할 때 유용합니다.
unordered_map
목적: 키-값 쌍을 저장하는 데 사용됩니다. 즉, 사전을 구현합니다.
구조: 각 요소는 고유한 키와 그에 대응하는 값을 가지고 있습니다. 키는 중복될 수 없으며, 각 키는 하나의 값에만 연결됩니다.
기본 연산:
삽입 (insert): O(1) 평균 시간 복잡도
삭제 (erase): O(1) 평균 시간 복잡도
검색 (find): O(1) 평균 시간 복잡도
사용 예: 특정 키에 대한 값을 빠르게 조회할 때 사용됩니다. 예를 들어, 키를 통해 데이터에 접근하고, 키와 관련된 정보를 저장할 때 유용합니다.
요약
unordered_set은 단일 값의 집합을 저장하고, 중복을 허용하지 않으며, 값의 존재 여부를 빠르게 확인할 수 있습니다.
unordered_map은 키와 값의 쌍을 저장하고, 키를 통해 값에 접근할 수 있습니다. 키는 중복되지 않으며, 각 키는 하나의 값에만 매핑됩니다.
*/

#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    unordered_map<int, int> nct;

    for (int i = 0; i < n; i++)
    {
        int number;
        cin >> number;
        nct[number]++;
    }

    for (int i = 0; i < m; i++)
    {
        int query;
        cin >> query;
        cout << nct[query] << endl;
    }
}