#include <bits/stdc++.h>
using namespace std;

// 각 줄마다 문자들을 저장하는 deque (줄바꿈 처리를 위함)
deque<char> grid[303];

// counting[i][j]는 i번째 줄에 있는 문자 'a'+j의 개수
int counting[303][26];

// 그리드의 높이(h), 너비(w), 전체 문자열 길이(len)
int h, w, len;

// 현재 커서 위치 (cur_r: 행, cur_c: 열)
int cur_r, cur_c;

// 문자열 초기화 함수
void init(int H, int W, char str[])
{
    len = 0;
    h = H, w = W;

    // 문자 개수 배열 초기화
    memset(counting, 0, sizeof(counting));

    // 모든 줄 초기화
    for (int i = 0; i < 303; ++i)
        grid[i].clear();

    // 문자열을 왼쪽 위부터 채워넣기
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (str[len]) // 아직 문자가 남아 있으면
            {
                counting[i][str[len] - 'a']++; // 해당 줄의 해당 문자 개수 증가
                grid[i].push_back(str[len++]); // grid에 문자 삽입
            }
            else
                break; // 문자열이 끝났으면 종료
        }
    }

    // 커서 초기화
    cur_r = cur_c = 0;
}

// 문자 삽입 함수
void insert(char c)
{
    // 현재 커서 위치에 문자 삽입
    grid[cur_r].insert(grid[cur_r].begin() + cur_c, c);
    counting[cur_r][c - 'a']++; // 문자 개수 업데이트

    int row = cur_r; // 현재 행 기억
    ++cur_c;         // 커서 오른쪽 이동
    ++len;           // 전체 문자열 길이 증가

    // 커서가 줄 끝을 넘었다면 다음 줄로 이동
    if (cur_c == w)
    {
        ++cur_r;
        cur_c = 0;
    }

    // 해당 줄의 길이가 w를 넘는다면 줄바꿈 처리
    while ((int)grid[row].size() > w)
    {
        // 마지막 문자를 빼서 다음 줄 앞으로 이동
        char bk = grid[row].back();

        counting[row][bk - 'a']--; // 현재 줄에서 문자 제거
        grid[row].pop_back();      // 맨 뒤 문자 제거

        counting[row + 1][bk - 'a']++; // 다음 줄에 문자 추가
        grid[row + 1].push_front(bk);  // 다음 줄 맨 앞에 문자 삽입

        ++row; // 다음 줄로 진행
    }
}

// 커서를 주어진 위치로 이동하고, 해당 문자를 반환
char moveCursor(int row, int col)
{
    --row, --col; // 1-based → 0-based 인덱스로 변환

    // 전체 문자열 길이를 초과하는 위치에 접근하려는 경우
    if (row * w + col >= len)
    {
        // 커서를 마지막 문자 이후 위치로 이동
        row = len / w;
        col = len % w;
        cur_r = row;
        cur_c = col;
        return '$'; // 범위를 초과했음을 나타내는 특수 문자 반환
    }

    // 커서 위치 갱신
    cur_r = row;
    cur_c = col;

    // 해당 위치의 문자 반환
    return grid[row][col];
}

// 현재 커서 이후부터 특정 문자의 개수를 세는 함수
int countCharacter(char c)
{
    int row = cur_r, col = cur_c;
    int ret = 0;

    // 현재 줄에서 커서 이후부터 끝까지 직접 확인
    if (col)
    {
        for (int i = col; i < (int)grid[row].size(); ++i)
        {
            ret += grid[row][i] == c;
        }
        ++row; // 다음 줄부터는 counting 배열 사용
    }

    // 이후 줄은 counting 배열을 사용해 빠르게 개수 계산
    for (int i = row; i < h; ++i)
    {
        ret += counting[i][c - 'a'];
    }

    return ret;
}
