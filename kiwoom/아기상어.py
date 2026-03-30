import sys
from collections import deque
input = sys.stdin.readline

def solve():
    N = int(input())
    grid = []
    shark_r, shark_c = 0, 0

    for i in range(N):
        row = list(map(int, input().split()))
        for j in range(N):
            if row[j] == 9:
                shark_r, shark_c = i, j
                row[j] = 0
        grid.append(row)

    shark_size = 2
    eaten = 0
    total_time = 0

    while True:
        visited = [[-1]*N for _ in range(N)]
        visited[shark_r][shark_c] = 0
        queue = deque([(shark_r, shark_c)])

        candidates = []
        min_dist = float('inf')

        while queue:
            r, c = queue.popleft()
            dist = visited[r][c]

            if dist > min_dist:
                break

            if grid[r][c] != 0 and grid[r][c] < shark_size:
                candidates.append((dist, r, c))
                min_dist = dist

            for dr, dc in [(-1,0), (0,-1), (0,1), (1,0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < N and 0 <= nc < N and visited[nr][nc] == -1:
                    if grid[nr][nc] <= shark_size:
                        visited[nr][nc] = dist + 1
                        queue.append((nr,nc))

        if not candidates:
            break

        candidates.sort(key=lambda x: (x[0], x[1], x[2]))
        dist, tr, tc = candidates[0]

        total_time += dist
        grid[tr][tc] = 0
        shark_r, shark_c = tr, tc
        eaten += 1

        if eaten == shark_size:
            shark_size += 1
            eaten = 0

    print(total_time)

solve()