import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

def bfs(sy, sx, visited):
    queue = deque([(sy, sx, 1)])
    visited[sy][sx] = True
    while queue:
        cy, cx, cnt = queue.popleft()
        if cy == n - 1 and cx == m - 1:
            return cnt

        for dy, dx in dirs:
            ny = cy + dy
            nx = cx + dx

            if ny < 0 or nx < 0 or ny >= n or nx >= m:
                continue
            if visited[ny][nx]:
                continue
            # 0인 칸(이동 불가)은 건너뜀
            if visited[ny][nx] or board[ny][nx] == 0:
                continue

            visited[ny][nx] = True
            queue.append((ny, nx, cnt + 1))
    return -1

n, m = map(int, input().split())
board = []
for i in range(n):
    board.append([int(c) for c in input().strip()])

dirs = [[-1, 0], [0, -1], [1, 0], [0, 1]]
visited = [[False] * m for _ in range(n)]

print(bfs(0, 0, visited))