import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

def prepare_spice(S):
    return S

def discard_spice(idx, spices):
    if spices[idx] != -1:
        print(spices[idx])
        spices[idx] = -1
    elif spices[idx] == -1:
        print(-1)

def blending(K, spices):
    # 특정 값까지 도달하기 위한 조합이 항상 같아야 함
    # dp[M] 은 항상 최소한의 수의 합이 되어야 함
    # 계단 문제: i번째 칸에 오는 방법은 1칸 또는 2칸 -> dp[i] = dp[i-1] + dp[i-2]
    # 배낭 문제: i번째 물건을 (안 넣거나) 또는 넣거나
    # -> dp[i][w] = max(dp[i-1][w], dp[i-1][w-weight[i]] + value[i])
    INF = float('inf')
    dp = [INF] * (K + 1)
    dp[0] = 0

    # 폐기된 향료(-1)와 0 이하 향료 제외
    available = [s for s in spices if s is not None and s > 0]

    for k in range(1, K + 1):
        for s in available:
            if s <= k and dp[k - s] + 1 < dp[k]:
                dp[k] = dp[k - s] + 1

    return dp[K] if dp[K] != INF else -1

def spice_composition(K):
    # 세 향료의 향도의 합이 K 이상이 되는 모든 경우의 수 출력
    # 같은 번호의 향료 여러 자리에 사용 가능,
    # 사용한 향료가 같더라도 배치한 자리가 다르면 서로 다른 경우
    A = sorted(s for s in spices if s != -1)
    M = len(A)
    total = 0

    for j in range(M):
        # 중간 자리를 A[j]로 고정
        # x + z >= K - A[j] 인 (x, z) 순서쌍 개수 세기
        T = K - A[j]
        p = M
        for i in range(M):
            threshold = T - A[i]
            # A[k] >= threshold 인 최소 인덱스로 p 당기기
            while p > 0 and A[p - 1] >= threshold:
                p -= 1
            total += M - p

    return total

def solve():
    global N, spices
    Q = int(input())

    for _ in range(Q):
        query = list(map(int, input().split()))
        op = query[0]

        if op == 1:
            # 1 N S_1 S_2 ... S_N
            N = query[1]
            S = query[2:2+N]
            spices = prepare_spice(S)

        elif op == 2:
            v = query[1]
            spices.append(v)
            N += 1

        elif op == 3:
            idx = query[1]
            discard_spice(idx, spices)

        elif op == 4:
            K = query[1]
            print(blending(K, spices))

        elif op == 5:
            K = query[1]
            spice_composition(K)

spices = []
N = 0

solve()