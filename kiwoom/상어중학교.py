from collections import deque
import sys
input = sys.stdin.readline

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

def find_big_block(i, j, block_number):
    q = deque()
    q.append((i, j))

    normal = [[i, j]]
    rainbow = []

    while q:
        x, y = q.popleft()
        for d in range(4):
            nx = x + dx[d]
            ny = y + dy[d]

            if 0 <= nx < N and 0 <= ny < N:
                if block[nx][ny] == 0 and not visited[nx][ny]:
                    visited[nx][ny] = 1
                    q.append((nx, ny))
                    rainbow.append([nx, ny])

                elif block[nx][ny] == block_number and not visited[nx][ny]:
                    visited[nx][ny] = 1
                    q.append((nx, ny))
                    normal.append([nx, ny])

    for x, y in rainbow:
        visited[x][y] = 0

    return [len(normal+rainbow), len(rainbow), normal+rainbow]

def remove(group):
    global score
    for x, y in group[2]:
        block[x][y] = -2
    score += group[0] ** 2

def gravity():
    for i in range(N-2, -1, -1):
        for j in range(N):
            if block[i][j] != -1:
                g = i
                while g + 1 < N and block[g + 1][j] == -2:
                    block[g+1][j] = block[g][j]
                    block[g][j] = -2
                    g += 1

def rotate():
    global block
    block = [list(row) for row in reversed(list(zip(*block)))]

N, M = map(int, input().rstrip().split())
block = []
for _ in range(N):
    info = list(map(int, input().strip().split()))
    block.append(info)

score = 0
while True:
    visited = [[0] * N for _ in range(N)]
    group = []
    for i in range(N):
        for j in range(N):
            if block[i][j] >= 1 and not visited[i][j]:
                visited[i][j] = 1
                find_group = find_big_block(i, j, block[i][j])
                if find_group[0] >= 2:
                    group.append(find_group)

    group.sort(reverse=True)

    if not group:
        break

    remove(group[0])
    gravity()
    rotate()
    gravity()

print(score)