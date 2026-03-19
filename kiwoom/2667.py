import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

ans = []

dirs = [[-1, 0], [0, -1], [1, 0], [0, 1]]

def bfs(sy, sx, visited):
    cnt = 0
    queue = deque([(sy, sx)])

    while queue:
        cy, cx = queue.popleft()
        visited[cy][cx] = True
        cnt += 1

        for dy, dx in dirs:
            ny = cy + dy
            nx = cx + dx

            if ny < 0 or nx < 0 or ny >= n or nx >= n:
                continue
            if visited[ny][nx]:
                continue
            if board[ny][nx] == 0:
                continue

            visited[ny][nx] = True
            queue.append((ny, nx))
    return cnt

n = int(input())

board = []
for i in range(n):
    board.append([int(c) for c in input().strip()])

visited = [[False] * (n) for _ in range(n)]

for i in range(0, n):
    for j in range(0, n):
        if board[i][j] == 1 and visited[i][j] == False:
            ans.append(bfs(i, j, visited))

print(len(ans))
for x in sorted(ans):
    print(x)