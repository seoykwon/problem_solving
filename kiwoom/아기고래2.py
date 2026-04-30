# import sys
# sys.stdin = open('input.txt', 'r')
# input = sys.stdin.readline

# from collections import deque
# import heapq

# dir = {1: 0, 2: 2, 3: 1, 4: 3}
# dy = [-1, 0, 1, 0]
# dx = [0, -1, 0, 1]

# def check(N, board, r, c):
#     visited = [[0]*N for _ in range(N)]
#     flag = False
#     # 인접한 칸에 방문 가능한 바다가 없을 때
#     for s in range(4):
#         nr = r + dy[s]
#         nc = c + dx[s]

#         if nr < 0 or nc < 0 or nr >= N or nc >= N:
#             continue
#         if board[nr][nc] == 0 and not visited[nr][nc]:
#             flag = True

#     if flag:
#         return True
#     return False

# def explore(N, r, c, d, board):
#     q = deque()
#     visited = [[[0]*N for _ in range(N)]]
#     visited[r][c] = True
    
#     while check(N, board, r, c):
#         cd = dir[d]
#         nr = 0
#         nc = 0
#         print(r, c)

#         # 1. 현재 바라보는 방향으로 직진
#         nr = r + dy[cd]
#         nc = c + dx[cd]

#         if nr > 0 and nc > 0 and nr < N and nc < N and not visited[nr][nc]:
#             visited[nr][nc] = True
#             q.append([nr, nc])
#             r = nr
#             c = nc
#             continue

#         # 2. 좌회전 후 직진
#         nr = r + dy[(cd + 1) % 4]
#         nc = c + dx[(cd + 1) % 4]

#         if nr > 0 and nc > 0 and nr < N and nc < N and not visited[nr][nc]:
#             visited[nr][nc] = True
#             q.append([nr, nc])
#             r = nr
#             c = nc
#             continue

#         # 3. 우회전 후 직진
#         nr = r + dy[(cd + 3) % 4]
#         nc = c + dx[(cd + 3) % 4]

#         if nr > 0 and nc > 0 and nr < N and nc < N and not visited[nr][nc]:
#             visited[nr][nc] = True
#             q.append([nr, nc])
#             r = nr
#             c = nc
#             continue

#         # 4. 180도 회전 후 직진
#         nr = r + dy[(cd + 2) % 4]
#         nc = c + dx[(cd + 2) % 4]

#         if nr > 0 and nc > 0 and nr < N and nc < N and not visited[nr][nc]:
#             visited[nr][nc] = True
#             q.append([nr, nc])
#             r = nr
#             c = nc
#             continue

#         r = nr
#         c = nc

#     return [r, c]

# def bfs(N, r, c, board):
#     q = deque()
#     visited = [[0]*N for _ in range(N)]

#     q.append([r, c, 0, 0])
#     visited[r][c] = 1

#     cand = []

#     while q:
#         cr, cc, dist, direction = q.popleft()

#         if board[cr][cc] == 0:
#             heapq.heappush(cand, (dist, cr, cc, direction))

#         for w in range(4):
#             nr = cr + dy[w]
#             nc = cc + dx[w]

#             if nr < 0 or nc < 0 or nr >= N or nc >= N:
#                 continue
#             if visited[nr][nc]:
#                 continue
#             if board[nr][nc] == 0:
#                 q.append([nr, nc, dist+1, w])
#                 visited[nr][nc] = True

#     _, nr, nc, d = cand[0]

#     return [nr, nc, d]


# def move(N, r, c, board):
#     bfs(N, r, c, board)


# def solve(N, r, c, d, board):
    
#     # 1. 인접 탐험
#     nr, nc = explore(N, r, c, d, board)

#     # 2. 가장 가까운 바다로 이동
#     nr, nc, d = move(N, nr, nc, board)
#     print(nr, nc)


# N, r, c, d = map(int, input().split())

# board = []
# for _ in range(N):
#     board.append(list(map(int, input().split())))

# solve(N, r, c, d, board)

import sys
from collections import deque
input = sys.stdin.readline

DIR = {1: 0, 2: 2, 3: 1, 4: 3}
dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]

def main():
    N, r, c, d = map(int, input().split())
    r -= 1; c -= 1
    board = [list(map(int, input().split())) for _ in range(N)]

    visited = [[False]*N for _ in range(N)]
    visited[r][c] = True
    cd = DIR[d]

    out = [(r+1, c+1)]
    total_sea = sum(row.count(0) for row in board)
    cnt = 1

    while cnt < total_sea:
        while True:
            moved = False
            for off in (0, 1, 3, 2):
                nd = (cd + off) % 4
                nr, nc = r + dy[nd], c + dx[nd]
                if 0 <= nr < N and 0 <= nc < N and board[nr][nc] == 0 and not visited[nr][nc]:
                    r, c, cd = nr, nc, nd
                    visited[r][c] = True
                    cnt += 1
                    out.append((r+1, c+1))
                    moved = True
                    break
            if not moved:
                break

        if cnt >= total_sea:
            break

        dist = [[-1]*N for _ in range(N)]
        dist[r][c] = 0
        q = deque([(r, c)])
        cands = []
        while q:
            cr, cc = q.popleft()
            if not visited[cr][cc]:
                cands.append((dist[cr][cc], cr, cc))
            for k in range(4):
                nr, nc = cr + dy[k], cc + dx[k]
                if 0 <= nr < N and 0 <= nc < N and board[nr][nc] == 0 and dist[nr][nc] == -1:
                    dist[nr][nc] = dist[cr][cc] + 1
                    q.append((nr, nc))

        cands.sort()
        _, tr, tc = cands[0]

        dt = [[-1]*N for _ in range(N)]
        dt[tr][tc] = 0
        q = deque([(tr, tc)])
        while q:
            cr, cc = q.popleft()
            for k in range(4):
                nr, nc = cr + dy[k], cc + dx[k]
                if 0 <= nr < N and 0 <= nc < N and board[nr][nc] == 0 and dt[nr][nc] == -1:
                    dt[nr][nc] = dt[nr][nc] + 1
                    q.append((nr, nc))

        prio = (1, 2, 3, 0)
        last = cd
        while (r, c) != (tr, tc):
            for k in prio:
                nr, nc = r + dy[k], c + dx[k]
                if 0 <= nr < N and 0 <= nc < N and dt[nr][nc] == dt[r][c] - 1:
                    r, c, last = nr, nc, k
                    break
        cd = last
        visited[r][c] = True
        cnt += 1
        out.append((r+1, c+1))

    for a, b in out:
        print(a, b)

main()