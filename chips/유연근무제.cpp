#include <string>
#include <vector>

using namespace std;

int solution(vector<int> schedules, vector<vector<int>> timelogs, int startday) {
    int n = schedules.size();
    int answer = 0;

    for (int i = 0; i < n; i++) {
        // 출근 마감 시각 = 희망 시각 + 10분 (분 자리 올림 처리)
        int hour = schedules[i] / 100;
        int minute = schedules[i] % 100 + 10;
        if (minute >= 60) {
            hour += 1;
            minute -= 60;
        }
        int deadline = hour * 100 + minute;

        bool isWinner = true;
        for (int j = 0; j < 7; j++) {
            // j일차의 요일
            int dayOfWeek = (startday - 1 + j) % 7;

            if (dayOfWeek == 5 || dayOfWeek == 6) continue;

            if (timelogs[i][j] > deadline){
                isWinner = false;
                break;
            }
        }
        if (isWinner) answer++;
    }
    return answer;
}