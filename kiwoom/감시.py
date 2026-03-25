import sys
from copy import deepcopy
input = sys.stdin.readline

# 방향: 0=오른쪽, 1=아래, 2=왼쪽, 3=위
dr = [0, 1, 0, -1]
dc = [1, 0, -1, 0]

# CCTV 종류별 가능한 방향 조합
DIRS = {
    1: [[0], [1], [2], [3]],
    2: [[0,2], [1,3]],
    3: [[0,1], [1,2], [2,3], [3,0]],
    4: [[0,1,2], [1,2,3], [2,3,0], [3,0,1]],
    5: [[0,1,2,3]]
}

N, M = map(int, input().split())
office = [list(map(int, input().split())) for _ in range(N)]

# CCTV 위치 수집
cctvs = []
for r in range(N):
    for c in range(M):
        if 1 <= office[r][c] <= 5:
            cctvs.append((r, c, office[r][c]))

def mark(board, r, c, direction):
    """한 방향으로 벽 만날 때까지 '#' 표시"""
    nr, nc = r + dr[direction], c + dc[direction]
    while 0 <= nr < N and 0 <= nc < M and board[nr][nc] != 6:
        if board[nr][nc] == 0:
            board[nr][nc] = '#'
        nr += dr[direction]
        nc += dc[direction]

def count_blind(board):
    return sum(row.count(0) for row in board)

min_blind = float('inf')

def dfs(idx, board):
    global min_blind
    if idx == len(cctvs):
        min_blind = min(min_blind, count_blind(board))
        return
    
    r, c, ctype = cctvs[idx]
    for directions in DIRS[ctype]:
        new_board = deepcopy(board)
        for d in directions:
            mark(new_board, r, c, d)
        dfs(idx + 1, new_board)

dfs(0, office)
print(min_blind)