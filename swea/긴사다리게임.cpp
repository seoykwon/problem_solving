/**
 * 1. 각 테스트 케이스 시작 시 init() 함수가 호출된다.
 * 2. 각 테스트 케이스에서 add() 함수의 호출 횟수는 200,000 이하이다.
 * 3. 각 테스트 케이스에서 remove() 함수의 호출 횟수는 5,000 이하이다.
 * 4. 각 테스트 케이스에서 numberOfCross() 함수의 호출 횟수는 500 이하이다.
 * 5. 각 테스트 케이스에서 participant() 함수의 호출 횟수는 500 이하이다.
 * 6. 사다리 게임을 진행했을 때, 한 참가자가 지나게 되는 가로줄의 개수는 항상 5,000개 이하이다.
 */

#include <map>
using namespace ::std;

const int N = 100;
const int MAX_NUM_NODE = 400210;
const int LAST_START_NODE = N;
const int FIRST_END_NODE = MAX_NUM_NODE - N - 5;

struct Node
{
    Node *prev;
    Node *next;
} node[MAX_NUM_NODE];
// 교점들의 이중 연결 리스트

// 두 정점을 서로 연결해주기
void link(Node *front, Node *back)
{
    front->next = back;
    back->prev = front;
}

// nodeMap[x] := x번 세로줄의 정점들의 y 좌표를 들고 있는 TreeMap
map<int, Node *> nodeMap[N + 1];
Node *newNode;

void init()
{
    for (int i = 1; i <= N; i++)
    {
        nodeMap[i].clear();
        nodeMap[i][0] = node + i;
        nodeMap[i][1000000000] = node + FIRST_END_NODE + i - 1;
        link(node + i, node + FIRST_END_NODE + i - 1);
    }
    newNode = node + N + 1;
}

// (mX, mY)와 (mX + 1, mY)을 잇는 가로줄 추가하기, O(Log N)
void add(int mX, int mY)
{
    Node *nowLeft = newNode++;
    Node *nowRight = newNode++;

    // mX번 세로 줄에서 mY 직전 정점 찾기
    Node *prevLeft = (--nodeMap[mX].upper_bound(mY))->second;
    // (mX + 1)번 세로 줄에서 mY 직전 정점 찾기
    Node *prevRight = (--nodeMap[mX + 1].upper_bound(mY))->second;

    // mX번 세로 줄에서 mY 직후 정점 찾기
    Node *nextLeft = prevLeft->next;
    // (mX + 1)번 세로 줄에서 mY 직후 정점 찾기기
    Node *nextRight = prevRight->next;

    // 순서 재조정 하기
    link(prevLeft, nowRight);
    link(nowRight, nextRight);

    link(prevRight, nowLeft);
    link(nowLeft, nextLeft);

    nodeMap[mX][mY] = nowLeft;
    nodeMap[mX + 1][mY] = nowRight;
}

// (mX, mY)와 (mX + 1, mY)을 잇는 가로줄 제거하기, O(Log N)
void remove(int mX, int mY)
{
    // mX번 세로 줄에서 mY 위치 정점 찾기
    Node *nowLeft = nodeMap[mX][mY];
    // (mX + 1)번 세로 줄에서 mY 위치 정점 찾기
    Node *nowRight = nodeMap[mX + 1][mY];

    Node *prevLeft = nowRight->prev;
    Node *prevRight = nowLeft->prev;

    Node *nextLeft = nowLeft->next;
    Node *nextRight = nowRight->next;

    // 순서 재조정 하기
    link(prevLeft, nextLeft);
    link(prevRight, nextRight);

    nodeMap[mX].erase(mY);
    nodeMap[mX + 1].erase(mY);
}

// mID번 참가자가 지나게 되는 가로줄의 개수 구하기, O(5000)
int numberOfCross(int mID)
{
    int ret = -1;
    // mID번 세로줄에서 출발하기
    Node *now = node + mID;
    // 마지막 줄에 도착할 때까지 다음으로 이동하기기
    while (now < node + FIRST_END_NODE)
    {
        ret++;
        now = now->next;
    }
    return ret;
}

// (mX, mY)에 도착하는 참가자 찾기, O(5000)
int participant(int mX, int mY)
{
    // mX번 세로 줄에서 mY 직전 정점 찾기기
    Node *now = (--nodeMap[mX].upper_bound(mY))->second;
    // 최상단에 도착할 때까지 이전으로 돌아가기기
    while (now > node + LAST_START_NODE)
        now = now->prev;
    return now - node;
}