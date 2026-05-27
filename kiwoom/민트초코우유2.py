import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque
import heapq

f_order = [7, 6, 5, 3, 1, 2, 4]

def morning(N, faith):
    for i in range(N):
        for j in range(N):
            faith[i][j] += 1

# bfs(N, food, faith, visited, represent, group, i, j, g_id)
def bfs(N, food, faith, visited, represent, group, i, j, g_id):
    q = deque()
    visited[i][j] = True
    q.append((i, j))
    group[i][j] = g_id

    candidate = []
    heapq.heappush(candidate, (-faith[i][j], i, j))

    while q:
        cr, cc = q.popleft()

        for dr, dc in ((-1,0),(1,0),(0,-1),(0,1)):
            nr, nc = cr+dr, cc+dc

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            if food[nr][nc] != food[i][j]:
                continue
            q.append((nr, nc))
            visited[nr][nc] = True
            group[nr][nc] = g_id
            heapq.heappush(candidate, (-faith[nr][nc], nr, nc))

    _, hr, hc = heapq.heappop(candidate)
    sz = len(candidate)
    represent[g_id] = [hr, hc]

    faith[hr][hc] += sz

    while candidate:
        _, r, c = heapq.heappop(candidate)
        faith[r][c] -= 1

    return represent

# noon(N, food, faith, represent, group)
def noon(N, food, faith, represent, group):
    g_id = 1
    visited = [[False]*N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            if not visited[i][j]:
                bfs(N, food, faith, visited, represent, group, i, j, g_id)
                g_id += 1

    return represent

def solve():
    N, T = map(int, input().split())

    tmp = []
    for _ in range(N):
        tmp.append(list(map(str, input().strip())))

    food = [[0]*N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            if tmp[i][j] == 'T':
                food[i][j] = 4
            elif tmp[i][j] == 'C':
                food[i][j] = 2
            elif tmp[i][j] == 'M':
                food[i][j] = 1

    faith = []
    for _ in range(N):
        faith.append(list(map(int, input().split())))

    # print(*board)
    # print(*faith)
    # 1. 아침시간
    morning(N, faith)

    # 2. 점심시간
    represent = {}
    group = [[0]*N for _ in range(N)]
    represent = noon(N, food, faith, represent, group)

    print(*represent)

solve()

