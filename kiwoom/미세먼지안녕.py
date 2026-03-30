import sys
input = sys.stdin.readline

def solve():
    R, C, T = map(int, input().split())
    grid = []
    purifier = []  # 공기청정기 위치 [위, 아래]

    for r in range(R):
        row = list(map(int, input().split()))
        for c in range(C):
            if row[c] == -1:
                purifier.append(r)
        grid.append(row)

    up, down = purifier[0], purifier[1]

    def spread():
        # 확산량을 별도 배열에 저장 (동시에 일어나므로)
        delta = [[0]*C for _ in range(R)]

        for r in range(R):
            for c in range(C):
                if grid[r][c] <= 0:
                    continue
                amount = grid[r][c] // 5
                count = 0
                for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
                    nr, nc = r+dr, c+dc
                    if 0 <= nr < R and 0 <= nc < C and grid[nr][nc] != -1:
                        delta[nr][nc] += amount
                        count += 1
                # 확산 후 남은 양
                delta[r][c] -= amount * count

        for r in range(R):
            for c in range(C):
                if grid[r][c] != -1:
                    grid[r][c] += delta[r][c]

    def rotate(path):
        # path 순서대로 한 칸씩 앞으로 이동
        # path[0]은 공기청정기 바로 옆 (새 바람 = 0)
        # path[-1]은 공기청정기로 들어가는 칸 (정화)
        tmp = grid[path[-1][0]][path[-1][1]]  # 사라질 먼지 (정화)
        for i in range(len(path)-1, 0, -1):
            r, c = path[i]
            pr, pc = path[i-1]
            grid[r][c] = grid[pr][pc]
        grid[path[0][0]][path[0][1]] = 0  # 공기청정기에서 나오는 바람

    def purify():
        # 위쪽 공기청정기: 반시계방향
        path = []
        for c in range(1, C):         # 오른쪽 (up행)
            path.append((up, c))
        for r in range(up-1, -1, -1): # 위쪽 (C-1열)
            path.append((r, C-1))
        for c in range(C-2, -1, -1):  # 왼쪽 (0행)
            path.append((0, c))
        for r in range(1, up):        # 아래쪽 (0열)
            path.append((r, 0))
        rotate(path)

        # 아래쪽 공기청정기: 시계방향
        path = []
        for c in range(1, C):         # 오른쪽 (down행)
            path.append((down, c))
        for r in range(down+1, R):    # 아래쪽 (C-1열)
            path.append((r, C-1))
        for c in range(C-2, -1, -1):  # 왼쪽 (R-1행)
            path.append((R-1, c))
        for r in range(R-2, down, -1):# 위쪽 (0열)
            path.append((r, 0))
        rotate(path)

    for _ in range(T):
        spread()
        purify()

    # 공기청정기(-1) 제외하고 합산
    print(sum(grid[r][c] for r in range(R) for c in range(C) if grid[r][c] != -1))

solve()