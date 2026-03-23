N = int(input())
consultations = [tuple(map(int, input().split())) for _ in range(N)]

# dp[i] = i일부터 퇴사일까지 얻을 수 있는 최대 수익
dp = [0] * (N + 1)

for i in range(N - 1, -1, -1):
    T, P = consultations[i]
    # 이 상담을 안 하는 경우: 다음 날의 최대 수익 그대로
    dp[i] = dp[i + 1]
    # 이 상담을 하는 경우: 퇴사일을 넘지 않아야 함
    if i + T <= N:
        dp[i] = max(dp[i], P + dp[i + T])

print(dp[0])