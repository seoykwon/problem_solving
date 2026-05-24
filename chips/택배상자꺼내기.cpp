#include <string>
#include <vector>

using namespace std;

int solution(int n, int w, int num) {
    // 0-indexed 행 번호
    int row = (num - 1) / w; // num이 있는 행
    int topRow = (n - 1) / w; // 맨 위 행
    int topCnt = n - topRow * w; // 맨 위 행에 놓인 박스 수 (1 ~ w)

    // num의 컬럼 (지그재그 반영)
    int numCol;
    if (row % 2 == 0) numCol = (num - 1) % w; // 왼 -> 오
    else numCol = w - 1 - (num - 1) % w; // 오 -> 왼

    // 맨 위 행에 numCol 위치에 박스가 있는지
    bool topHasBox;
    if (topRow % 2 == 0) topHasBox = numCol < topCnt; // 왼 -> 오: 0 ~ topCnt-1
    else topHasBox = numCol >= w - topCnt; // 오 -> 왼: w-topCnt ~ w-1;

    return (topRow - row) + (topHasBox ? 1 : 0);
}

/**
 * 변수명을 top, row 같은 모호한 것 말고 topRow, numRow, numCol, topCount로 풀어쓰고,
 * 행 인덱스와 컬럼 인덱스를 절대 같은 비교식에 섞지 않는다는 원칙만 지키기
 */