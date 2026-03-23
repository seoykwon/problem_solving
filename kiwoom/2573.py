import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

dirs = [(-1, 0), (0, -1), (1, 0), (0, 1)]
N, M = map(int, input().split())
board = []

for i in range(N):
    board.append(list(map(int, input().split())))

def melting():
    # 감소량을 별도 배열에 기록한 뒤 한꺼번에 반영
    decrease = [[0] * M for _ in range(N)]
    for i in range(N):
        for j in range(M):
            if board[i][j] != 0:
                for dy, dx in dirs:
                    ny = i + dy
                    nx = j + dx
                    if 0 <= ny < N and 0 <= nx < M and board[ny][nx] == 0:
                        decrease[i][j] += 1

    for i in range(N):
        for j in range(M):
            board[i][j] = max(0, board[i][j] - decrease[i][j])

def bfs(sy, sx, visited):
    queue = deque([(sy, sx)])
    visited[sy][sx] = True
    while queue:
        cy, cx = queue.popleft()
        for dy, dx in dirs:
            ny = cy + dy
            nx = cx + dx
            if 0 <= ny < N and 0 <= nx < M and not visited[ny][nx] and board[ny][nx] > 0:
                visited[ny][nx] = True
                queue.append((ny, nx))

time = 0
while True:
    melting()
    time += 1

    visited = [[False] * M for _ in range(N)]
    count = 0

    for i in range(N):
        for j in range(M):
            if board[i][j] > 0 and not visited[i][j]:
                bfs(i, j, visited)
                count += 1
    
    if count >= 2:
        print(time)
        break
    if count == 0:
        print(0)
        break

# --------------------------------------------
import sys
input = sys.stdin.readline
from collections import deque

dirs = [(-1,0),(0,-1),(1,0),(0,1)]
N, M = map(int, input().split())
board = []
ice = set()

for i in range(N):
    row = list(map(int, input().split()))
    board.append(row)
    for j in range(M):
        if row[j] > 0:
            ice.add((i, j))

def melting():
    decrease = {}
    for (i, j) in ice:
        cnt = 0
        for dy, dx in dirs:
            ny, nx = i+dy, j+dx
            if board[ny][nx] == 0:
                cnt += 1
        if cnt:
            decrease[(i,j)] = cnt

    for (i,j), d in decrease.items():
        board[i][j] = max(0, board[i][j] - d)
        if board[i][j] == 0:
            ice.discard((i,j))

def count_chunks():
    if not ice:
        return 0
    visited = set()
    start = next(iter(ice))
    queue = deque([start])
    visited.add(start)
    while queue:
        cy, cx = queue.popleft()
        for dy, dx in dirs:
            n = (cy+dy, cx+dx)
            if n in ice and n not in visited:
                visited.add(n)
                queue.append(n)
    if len(visited) == len(ice):
        return 1
    return 2  # 2개 이상이면 바로 2 리턴

time = 0
while True:
    melting()
    time += 1
    c = count_chunks()
    if c >= 2:
        print(time)
        break
    if c == 0:
        print(0)
        break