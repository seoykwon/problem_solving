from itertools import combinations
from collections import deque
import copy

N, M = map(int, input().split())
board = [list(map(int, input().split())) for _ in range(N)]

# 빈 칸과 바이러스 위치 수집
empty = []
viruses = []
for r in range(N):
    for c in range(M):
        if board[r][c] == 0:
            empty.append((r, c))
        elif board[r][c] == 2:
            viruses.append((r, c))

dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]

def bfs(grid):
    # 바이러스 전파 후 안전 영역 크기 반환
    temp = copy.deepcopy(grid)
    q = deque()
    for r, c in viruses:
        q.append((r, c))
    while q:
        r, c = q.popleft()
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if 0 <= nr < N and 0 <= nc < M and temp[nr][nc] == 0:
                temp[nr][nc] = 2
                q.append((nr, nc))
    # 안전 영역 = 0인 칸의 수
    return sum(row.count(0) for row in temp)

ans = 0

# 빈 칸 중 3개를 골라 벽 세우기
for walls in combinations(empty, 3):
    # 벽 세우기
    for r, c in walls:
        board[r][c] = 1
    # 안전 영역 계산
    ans = max(ans, bfs(board))
    # 벽 원복
    for r, c in walls:
        board[r][c] = 0

print(ans)