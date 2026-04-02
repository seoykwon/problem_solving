import sys

input = sys.stdin.readline


def solve():
    N = int(input())
    A = []
    for _ in range(N):
        A.append(list(map(int, input().split())))

    ans = float('inf')

    # 1-indexed
    for x in range(1, N + 1):
        for y in range(1, N + 1):
            for d1 in range(1, N + 1):
                # y - d1 >= 1 이어야 함
                if y - d1 < 1:
                    break
                for d2 in range(1, N + 1):
                    # x + d1 + d2 <= N, y + d2 <= N 이어야 함
                    if x + d1 + d2 > N:
                        break
                    if y + d2 > N:
                        break

                    pop = [0] * 6  # 1~5번 선거구 인구

                    for r in range(1, N + 1):
                        for c in range(1, N + 1):
                            val = A[r - 1][c - 1]

                            # 5번 선거구: 마름모 내부 또는 경계
                            if (r + c >= x + y and c - r <= y - x and r - c <= x + 2 * d1 - y and r + c <= x + y + 2 * d2):
                                pop[5] += val
                            # 1번 선거구: 1번 경계선 왼쪽 위
                            elif r < x + d1 and 1 <= c <= y:
                                pop[1] += val
                            # 2번 선거구: 2번 경계선 오른쪽 위
                            elif r <= x + d2 and y < c <= N:
                                pop[2] += val
                            # 3번 선거구: 3번 경계선 왼쪽 아래
                            elif r >= x + d1 and 1 <= c < y - d1 + d2:
                                pop[3] += val
                            # 4번 선거구: 4번 경계선 오른쪽 아래
                            else:
                                pop[4] += val

                    ans = min(ans, max(pop[1:6]) - min(pop[1:6]))

    print(ans)


solve()