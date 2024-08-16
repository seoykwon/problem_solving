#include <iostream>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int>()> pq;

int main()
{
    // 1. 데이터 추가
    pq.push(3);
    pq.push(13);
    pq.push(7);
    pq.push(16);
    pq.push(42);
    pq.push(1);
    pq.push(15);

    // 2. 우선 순위에 따라 관리된 맨 앞 노드를 or root 노드 확인
    cout << pq.top() << endl;

    // 3. 데이터 삭제
    pq.pop();

    // 4. 큐가 비었는지 확인
    while (!pq.empty())
    {
        int now = pq.top();
        pq.pop();
        cout << now << " ";
    }

    int de = -1;
}