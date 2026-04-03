import sys
from collections import deque
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline


def solve():
    N, M, T = map(int, input().split())

    disk = [[]]  # index 0 placeholder
    for i in range(N):
        disk.append(deque(map(int, input().split())))

    for _ in range(T):
        x, d, k = map(int, input().split())

        # Step 1: x의 배수인 원판 회전
        for i in range(1, N + 1):
            if i % x == 0:
                if d == 0:  # 시계 방향
                    disk[i].rotate(k)
                else:  # 반시계 방향
                    disk[i].rotate(-k)

        # Step 2: 인접하면서 같은 수 탐색
        to_remove = set()

        for i in range(1, N + 1):
            for j in range(M):
                val = disk[i][j]
                if val == 0:
                    continue
                if disk[i][(j + 1) % M] == val:  # 오른쪽
                    to_remove.add((i, j))
                    to_remove.add((i, (j + 1) % M))
                if disk[i][(j - 1) % M] == val:  # 왼쪽
                    to_remove.add((i, j))
                    to_remove.add((i, (j - 1) % M))
                if i < N and disk[i + 1][j] == val:  # 바깥 원판
                    to_remove.add((i, j))
                    to_remove.add((i + 1, j))
                if i > 1 and disk[i - 1][j] == val:  # 안쪽 원판
                    to_remove.add((i, j))
                    to_remove.add((i - 1, j))

        if to_remove:
            for (i, j) in to_remove:
                disk[i][j] = 0
        else:
            # 평균 계산 후 조정
            total = sum(disk[i][j] for i in range(1, N + 1) for j in range(M) if disk[i][j] != 0)
            count = sum(1 for i in range(1, N + 1) for j in range(M) if disk[i][j] != 0)
            if count == 0:
                continue
            mean = total / count
            for i in range(1, N + 1):
                for j in range(M):
                    if disk[i][j] != 0:
                        if disk[i][j] > mean:
                            disk[i][j] -= 1
                        elif disk[i][j] < mean:
                            disk[i][j] += 1

    print(sum(disk[i][j] for i in range(1, N + 1) for j in range(M)))


solve()