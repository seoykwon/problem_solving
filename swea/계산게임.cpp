/**
 * 1. 각 테스트 케이스 시작 시 init() 함수가 호출된다.
 * 2. 각 테스트 케이스에서 putCards() 함수의 호출 횟수는 10,000회 이하이다.
 * 3. 각 테스트 케이스에서 전체 함수의 총 호출 횟수는 15,000회 이하이다.
 * 4. 주어지는 카드 5장 내에 포함된 조커 카드 개수의 제한은 없다.
 */

#include <deque>

using namespace std;

#define MAX_CARD 50000

struct Table
{
    int joker;                   // 현재 조커의 점수
    int begin, end;              // 카드가 놓인 시작점과 끝점
    int cards[MAX_CARD * 2 + 5]; // 테이블 위 카드 배열
    deque<int> idxList[20][20];  // idxList[joker][score]: 특정 조커 값에서 점수별 카드 시작 인덱스 리스트

    // 네 장의 카드 점수를 기반으로 idxList 갱신
    void updateIdx(int idx, int mdir)
    {
        int sum = 0;       // 조커를 제외한 점수 총합
        int joker_cnt = 0; // 조커 개수 확인
        for (int i = 0; i < 4; i++)
        {
            if (cards[idx + i] == -1) // 조커라면
                joker_cnt++;
            else
                sum += cards[idx + i]; // 조커가 아니라면 점수 누적
        }

        // 조커의 점수를 가능한 모든 값(0~29)로 가정하여 점수 조합 계산
        for (int i = 0; i < 30; i++)
        {
            int num = (sum + (joker_cnt * i)) % 20; // 최종 점수 계산
            if (mdir == 0)                          // 왼쪽에서 추가되었으면 앞쪽에 삽입
                idxList[i][num].push_front(idx);
            else // 오른쪽에서 추가되었으면 뒤쪽에 삽입
                idxList[i][num].push_back(idx);
        }
    }

    // 게임 초기화 함수
    void init(int mJoker, int mNumbers[5])
    {
        begin = end = MAX_CARD; // 카드 시작점을 중앙으로 설정
        for (int i = 0; i < 30; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                idxList[i][j].clear(); // idxList 초기화
            }
        }
        for (int i = 0; i < 5; i++)
        {
            cards[end + i] = mNumbers[i]; // 초기 카드 배치
        }
        end += 5;
        for (int i = 0; i < 2; i++)
        {
            updateIdx(MAX_CARD + i, 1); // 초기 카드의 점수 조합 저장
        }
    }

    // 왼쪽에 새로운 카드 5장 추가
    void push_front(int mNumbers[5])
    {
        begin -= 5; // 왼쪽으로 확장
        for (int i = 0; i < 5; i++)
        {
            cards[begin + i] = mNumbers[i];
        }
        int target = begin;
        for (int i = 4; i >= 0; i--)
        {
            updateIdx(target + i, 0); // 새로 추가된 카드 점수 갱신
        }
    }

    // 오른쪽에 새로운 카드 5장 추가
    void push_back(int mNumbers[5])
    {
        for (int i = 0; i < 5; i++)
        {
            cards[end + i] = mNumbers[i];
        }
        int target = end - 3;
        end += 5;
        for (int i = 0; i < 5; i++)
        {
            updateIdx(target + i, 1); // 새로 추가된 카드 점수 갱신
        }
    }

    // 특정 점수(mNum)에서 mNth 번째 조합을 찾기
    int find(int mNum, int mNth)
    {
        auto &list = idxList[joker][mNum]; // 현재 조커 값에서 특정 점수의 카드 인덱스 리스트 참조
        if (mNth > list.size())            // 요청한 번째가 리스트 크기를 초과하면 실패
            return -1;
        return list[mNth - 1]; // mNth 번째 인덱스 반환
    }

    // 조커 점수 변경
    void changeJoker(int mJoker)
    {
        joker = mJoker % 20;
    }
};

Table t;

void init(int mJoker, int mNumbers[5])
{
    t.init(mJoker, mNumbers);
}

void putCards(int mDir, int mNumbers[5])
{
    if (mDir == 0)
    {
        t.push_front(mNumbers);
    }
    else
    {
        t.push_back(mNumbers);
    }
}

int findNumber(int mNum, int mNth, int ret[4])
{
    int idx = t.find(mNum, mNth);
    if (idx == -1)
        return 0;
    for (int i = 0; i < 4; i++)
    {
        ret[i] = t.cards[idx + i]; // 해당 위치의 4장 복사
    }
    return 1;
}

void changeJoker(int mValue)
{
    t.changeJoker(mValue);
}