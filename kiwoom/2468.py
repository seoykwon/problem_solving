import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

mx_ans = 0
dirs = [[-1, 0], [0, -1], [1, 0], [0, 1]]

def bfs(sy, sx, b2):
    global mx_ans, visited
    queue = deque([(sy, sx)])
    visited[sy][sx] = True

    while queue:
        cy, cx = queue.popleft()

        for dy, dx in dirs:
            ny = cy + dy
            nx = cx + dx

            if ny >= N or nx >= N or ny < 0 or nx < 0:
                continue
            if visited[ny][nx]:
                continue
            if b2[ny][nx] == 0:
                continue
            visited[ny][nx] = True
            queue.append((ny, nx))


N = int(input())
board = []

for i in range(N):
    board.append(list(int(c) for c in input().split()))

max_depth = 0
for i in range(N):
    for j in range(N):
        max_depth = max(max_depth, board[i][j])

for rain in range(max_depth):
    b2 = [[1] * N for _ in range(N)]
    visited = [[False] * (N) for _ in range(N)]
    # sunken due to rain
    for i in range(N):
        for j in range(N):
            if board[i][j] <= rain:
                b2[i][j] = 0
    cnt = 0
    for i in range(N):
        for j in range(N):
            if b2[i][j] == 1 and visited[i][j] == False:
                bfs(i, j, b2)
                cnt += 1

    mx_ans = max(mx_ans, cnt)

print(mx_ans)

# -------------------------------------------
import sys
from collections import deque

input = sys.stdin.readline

DIRS = [(-1, 0), (0, 1), (1, 0), (0, 1)]

def bfs(sy, sx, b2, visited):
    queue = deque([(sy, sx)])
    visited[sy][sx] = True

    while queue:
        cy, cx = queue.popleft()
        for dy, dx in DIRS:
            ny, nx = cy + dy, cx + dx
            if 0 <= ny < N and 0 <= nx < N and not visited[ny][nx] and b2[ny][nx]:
                visited[ny][nx] = True
                queue.append((ny, nx))

def count_islands(rain):
    b2 = [[board[i][j] > rain for j in range(N)] for i in range(N)]
    visited = [[False] * N for _ in range(N)]
    cnt = 0
    for i in range(N):
        for j in range(N):
            if b2[i][j] and not visited[i][j]:
                bfs(i, j, b2, visited)
                cnt += 1
    return cnt

N = int(input())
board = [list(map(int, input().split())) for _ in range(N)]

max_depth = max(board[i][j] for i in range(N) for j in range(N))
print(max(count_islands(rain) for rain in range(max_depth)))