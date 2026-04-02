import sys
from itertools import combinations
from collections import deque

input = sys.stdin.readline

def solve():
    N, M = map(int, input().split())
    grid = []
    viruses = []
    empty_count = 0

    for i in range(N):
        row = list(map(int, input().split()))
        grid.append(row)
        for j in range(N):
            if row[j] == 2:
                viruses.append((i, j))
            elif row[j] == 0:
                empty_count += 1

    if empty_count == 0:
        print(0)
        return

    def bfs(selected):
        visited = [[-1]*N for _ in range(N)]
        q = deque()
        for idx in selected:
            r, c = viruses[idx]
            visited[r][c] = 0
            q.append((r, c, 0))

        max_time = 0
        filled = 0

        while q:
            r, c, t = q.popleft()
            for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
                nr, nc = r+dr, c+dc
                if 0 <= nr < N and 0 <= nc < N and visited[nr][nc] == -1 and grid[nr][nc] != 1:
                    visited[nr][nc] = t + 1
                    q.append((nr, nc, t+1))
                    if grid[nr][nc] == 0:
                        filled += 1
                        max_time = max(max_time, t+1)

        if filled == empty_count:
            return max_time
        return float('inf')

    ans = float('inf')
    for combo in combinations(range(len(viruses)), M):
        ans = min(ans, bfs(combo))

    print(-1 if ans == float('inf') else ans)

solve()