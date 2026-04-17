import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

'''
N, 연산 세 개 활용해 1 만들며, 연산을 사용하는 횟수의 최솟값
'''

N = int(input())

INF = float('inf')
dp = [INF] * (N + 1)
dp[1] = 0

for i in range(2, N + 1):
    dp[i] = min(dp[i], dp[i - 1] + 1)
    if i % 3 == 0:
        dp[i] = min(dp[i], dp[i // 3] + 1)
    if i % 2 == 0:
        dp[i] = min(dp[i], dp[i // 2] + 1)


print(dp[N])

'''
dp 정의를 말로 안 해봐서
dp[N] = N 같은 의미 없는 초기값을 넣음
'''
'''
1단계: dp[i]가 뭐냐고 자기한테 물어보기
2단계: 점화식 방향이 정의랑 맞는지
3단계: elif에 의심의 눈길 보내기
4단계: 경계값 머릿속에서 실행해보기
5단계: print로 기댓값과 비교
'''