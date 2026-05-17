# 도착한 이메일 수 매일 기록한 배열 mails와 기간 period, 평균 메일 수 K, period일 동안 도착한 평균 메일 수가 K개 이상인 경우 총 몇 가지야?

# 3 <= mails <= 200000
# 0 <= mails <= 10000 정수
# 2 <= period <= mails 자연수
# 0 <= K <= 10000 정수

def solution(mails, period, K):
    cnt = 0
    n = len(mails)
    left = 0
    right = period - 1

    init = 0

    for i in range(0, period):
        init += mails[i]
    if init >= K:
        cnt += 1

    while right < period:
        init -= mails[left]
        left += 1
        right += 1
        init += mails[right]

        if init >= K:
            cnt += 1

    return cnt

solve(mails, period, K)

# 개선된 코드
def solution(mails, period, K):
    n = len(mails)
    threshold = K * period
    s = sum(mails[:period])
    cnt = 1 if s >= threshold else 0

    for i in range(period, n):
        s += mails[i] - mails[i - period]
        if s >= threshold:
            cnt += 1

    return cnt

# --------

public class Solution {
    public int solution(int[] mails, int period, int K){
        int n = mails.length;
        long threshold = (long) K * period;

        long sum = 0;
        for (int i = 0; i < period; i++) {
            sum += mails[i];
        }

        int cnt = (sum >= threshold) ? 1 : 0;

        for (int i = period; i < n; i++) {
            sum += mails[i] - mails[i - period];
            if (sum >= threshold) {
                cnt++;
            }
        }

        return cnt;
    }
}