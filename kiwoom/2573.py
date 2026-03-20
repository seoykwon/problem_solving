import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

dirs = [(-1, 0), (0, -1), (1, 0), (0, 1)]
N, M = map(int, input())
board = []

for i in range(N):
    board.append(list(map(int, input.split())))

def melting():
    global board
    for i in range(N):
        for j in range(N):
            if board[i][j] != 0:
                for dy, dx in dirs:
                    ny = i + dy
                    nx = j + dx

                    if ny >= N or nx >= N or ny < 0 or nx < 0:
                        continue
                    if board[i][j] == 0:
                        continue
                    if board[ny][nx] == 0:
                        board[i][j] -= 1

def bfs(sy, sx, visited):
    queue = deque([(sy, sx)])
    visited[sy][sx] = True

    while queue:
        cy, cx = queue.popleft()

        for dy, dx in dirs:
            ny = cy + dy
            nx = cx + dx

            if ny >= N or nx >= N or ny < 0 or nx < 0:
                continue
            if visited[ny][nx] or board[ny][nx] == 0:
                continue
            visited[ny][nx] = True
            queue.append((ny, nx))
            
time = 0
while True:
    time += 1
    visited = [[False] * N for _ in range(N)]
    flag = 0

    for i in range(N):
        for j in range(N):
            if board[i][j] != 0:
                bfs(i, j, visited)
                flag = 1
            if visited[i][j] == False and board[i][j] != 0 and flag == 1:
                print(time)
                break
    
    melting()