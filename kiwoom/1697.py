from collections import deque
import sys

input = sys.stdin.readline

MAX = 100001


def bfs(s, d):
    if s == d:
        return 0

    visited = [False] * MAX
    queue = deque([(s, 0)])
    visited[s] = True

    while queue:
        x, dist = queue.popleft()

        for nx in (x - 1, x + 1, 2 * x):
            if nx < 0 or nx >= MAX:
                continue
            if nx == d:
                return dist + 1
            if not visited[nx]:
                visited[nx] = True
                queue.append((nx, dist + 1))

    return -1


n, k = map(int, input().split())
print(bfs(n, k))