import sys
input = sys.stdin.readline

N, M = map(int, input().split())
board = [list(map(int, input().split())) for _ in range(N)]

visited = [[False]*M for _ in range(N)]
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]
ans = 0

def dfs(r, c, depth, total):
    global ans
    if depth == 4:
        ans = max(ans, total)
        return
    for i in range(4):
        nr, nc = r + dr[i], c + dc[i]
        if 0 <= nr < N and 0 <= nc < M and not visited[nr][nc]:
            visited[nr][nc] = True
            dfs(nr, nc, depth + 1, total + board[nr][nc])
            visited[nr][nc] = False

def check_T(r, c):
    global ans
    neighbors = []
    for i in range(4):
        nr, nc = r + dr[i], c + dc[i]
        if 0 <= nr < N and 0 <= nc < M:
            neighbors.append(board[nr][nc])
    if len(neighbors) >= 3:
        neighbors.sort(reverse=True)
        ans = max(ans, board[r][c] + sum(neighbors[:3]))

for r in range(N):
    for c in range(M):
        visited[r][c] = True
        dfs(r, c, 1, board[r][c])
        visited[r][c] = False
        check_T(r, c)

print(ans)