import sys
from collections import deque
input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n = int(input())
    points = []

    # 집 (0번), 편의점(1~n번), 페스티벌(n+1번) 좌표 입력
    for i in range(n + 2):
        x, y = map(int, input().split())
        points.append((x, y))

    visited = [False] * (n + 2)
    visited[0] = True
    queue = deque([0])
    found = False

    while queue:
        cur = queue.popleft()
        cx, cy = points[cur]

        if cur == n + 1:
            found = True
            break

        for nxt in range(n + 2):
            if not visited[nxt]:
                nx, ny = points[nxt]
                if abs(cx - nx) + abs(cy - ny) <= 1000:
                    visited[nxt] = True
                    queue.append(nxt)

    print("happy" if found else "sad")