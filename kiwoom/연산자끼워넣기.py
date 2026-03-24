import sys

input = sys.stdin.readline


def solve():
    N = int(input())
    A = list(map(int, input().split()))
    ops = list(map(int, input().split()))  # +, -, *, /

    max_val = -10 ** 9
    min_val = 10 ** 9

    def dfs(idx, cur, ops):
        nonlocal max_val, min_val

        if idx == N:
            max_val = max(max_val, cur)
            min_val = min(min_val, cur)
            return

        for i in range(4):
            if ops[i] == 0:
                continue
            ops[i] -= 1
            if i == 0:
                dfs(idx + 1, cur + A[idx], ops)
            elif i == 1:
                dfs(idx + 1, cur - A[idx], ops)
            elif i == 2:
                dfs(idx + 1, cur * A[idx], ops)
            else:
                # 음수 나눗셈: C++14 기준 (0 방향 truncation)
                if cur < 0:
                    dfs(idx + 1, -(-cur // A[idx]), ops)
                else:
                    dfs(idx + 1, cur // A[idx], ops)
            ops[i] += 1

    dfs(1, A[0], ops)
    print(max_val)
    print(min_val)


solve()