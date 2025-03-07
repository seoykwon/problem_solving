/**********************

해당 문제 조건
* 입국심사를 기다리는 사람은 1명 이상 1,000,000,000명 이하입니다.
* 각 심사관이 한 명을 심사하는데 걸리는 시간은 1분 이상 1,000,000,000분 이하입니다.
* 심사관은 1명 이상 100,000명 이하입니다.

**********************/
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;
	// 가장 큰 값을 뽑기 위해 정렬
	// 해당 함수는 max_element()를 사용해도 됨.
    sort(times.begin(), times.end());

    long long min = 1;

	// 주의. 데이터타입
    long long max = n * (long long)times.back();

	/* 이분탐색 */

	// 최대값과 최소값이 바뀌는 구간이 가장 최소 시간이다.
    while (min <= max) {

        long long avg = (max + min) / 2;
        long long tmp = 0;

			// 현재 시간 기준으로 심사위원들이
			// 몇명을 처리하는지 확인하는 부분
        for (int i = 0; i < times.size(); i++) {
            tmp += (avg / (long long) times[i]);
        }
			// 현재 값 보다 많은 사람을 처리할 수 있을 경우
        if (tmp >= n) {
            max = avg - 1;
            answer = avg;
        }
			// 현재 값보다 적은 사람을 처리할 수 있을 경우
        else min = avg + 1;
    }
    return answer;
}
