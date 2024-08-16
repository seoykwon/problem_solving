#include <iostream>
#include <queue>
using namespace std;

// using namespace std;
// priority_queue<int, vector<int>, greater<>>pq;
//
// int main() {
//
//	//1. 데이터 추가
//	pq.push(21); //<-1
//	pq.push(13);
//	pq.push(7);
//	pq.push(16);
//	pq.push(42); //<-3
//	pq.push(1); //<-2
//	pq.push(15);
//
//
//	//2. 우선순위에 따라 관리된 맨 앞 노드를 or root노드 확인
//	cout << pq.top() << "\n";
//
//     //3. 데이터 삭제
//	pq.pop();
//	cout << pq.size() << "\n";
//
//	//4. 큐가 비었는지 확인
//
//	while (!pq.empty()) {
//		int now = pq.top(); pq.pop();
//		cout << now << " ";
//	}
//
//	int de = -1;
// }

// 1.멤버를 가지고 있는 데이터 타입(struct)
// 2.멤버를 가지지 않는 데이터 타입(ex int)

struct Coord
{
    int row;
    int col;
    bool operator<(Coord right) const
    {
        // 기본 형태가 MAX HEAP 구조
        // left < right "참" right(큰값) 먼저
        // left < right "거짓" left(작은값) 먼저

        // 1. row가 작은 거 우선
        if (row < right.row)
            return true; // 1 < 2 < 3
        if (row > right.row)
            return false;
        // 2. col이 작은 거 우선
        if (col < right.col)
            return true;
        if (col > right.col)
            return false;

        return false;
    }
};

// struct Plus {
//
//	int operator()(int left, int right)const {
//		return left + right;
//	}
// };
//

// 1. operator< 오버로딩
// 2. function object 객체를 함수처럼 쓰는 방식 add = 1;

struct cmp_coord
{
    bool operator()(Coord left, Coord right) const
    {
        // 1. row 큰 거 우선
        if (left.row < right.row)
            return true;
        if (left.row > right.row)
            return false;
        // 2. col 은 작은 거 우선
        if (left.col < right.col)
            return false;
        if (left.col > right.col)
            return true;

        // 같은 경우
        return false;
    }
};

priority_queue<Coord, vector<Coord>, cmp_coord> pq;

int main()
{

    // Plus p;
    // int ans = p(1, 2);
    // cout << ans;

    pq.push({1, 4});
    pq.push({4, 7});
    pq.push({4, 3});
    pq.push({2, 6});
    pq.push({3, 1});

    while (!pq.empty())
    {

        Coord now = pq.top();
        pq.pop();
        cout << now.row << " , " << now.col << "\n";
    }

    return 0;
}
