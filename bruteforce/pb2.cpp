#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers)
{
    vector<int> answer;

    // 점수 카운트 배열
    int cnt[3] = {0};

    // 각 수포자의 답안 패턴 정의
    int onePattern[] = {1, 2, 3, 4, 5};                  // 1번 수포자 패턴
    int twoPattern[] = {2, 1, 2, 3, 2, 4, 2, 5};         // 2번 수포자 패턴
    int threePattern[] = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5}; // 3번 수포자 패턴

    // 정답 길이
    int n = answers.size();

    // 각 수포자의 점수를 계산
    for (int i = 0; i < n; i++)
    {
        if (answers[i] == onePattern[i % 5])
        {
            cnt[0]++;
        }
        if (answers[i] == twoPattern[i % 8])
        {
            cnt[1]++;
        }
        if (answers[i] == threePattern[i % 10])
        {
            cnt[2]++;
        }
    }

    // 최대 점수 찾기
    int maxScore = 0;
    for (int i = 0; i < 3; i++)
    {
        maxScore = max(maxScore, cnt[i]);
    }

    // 최대 점수를 얻은 수포자 찾기
    for (int i = 0; i < 3; i++)
    {
        if (cnt[i] == maxScore)
        {
            answer.push_back(i + 1); // 수포자 번호는 1부터 시작
        }
    }

    return answer;
}
