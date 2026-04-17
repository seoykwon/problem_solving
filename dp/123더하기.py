import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

T = int(input())

for _ in range(T):
    N = int(input())

    dp = [0] * (N + 1)
    dp[1] = 1
    # dp[2] = 2 index error 생길 수 있음
    dp[0] = 1

    for i in range(2, N+1):
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3]

    print(dp[N])

'''
손으로 풀어서 기댓값부터 만들기
'''