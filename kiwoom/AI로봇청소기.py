from collections import deque
import heapq
import copy

N, K, L = map(int, input().split())

grid = [[0] * N for _ in range(N)]
cgrid = [[0] * N for _ in range(N)]

for n in range(N):
    grid[n] = list(map(int, input().split()))

cleaner = []
for k in range(K):
    c = list(map(int, input().split()))
    c[0] -= 1
    c[1] -= 1
    cleaner.append(c)
    cgrid[c[0]][c[1]] = 1 ## 청소기


dx = [0, -1, 0, 1]
dy = [-1, 0, 1, 0]
def bfs_search(cx, cy):
    q = deque()
    q.append((cx, cy, 0))

    v = [[False] * N for _ in range(N)]
    v[cx][cy] = True

    min_cost = float("inf")

    m = []
    while q:
        x, y, cost = q.popleft()
        if cost > min_cost:
            continue
        if grid[x][y] > 0:
            if min_cost >= cost:
                min_cost = cost
                heapq.heappush(m, (min_cost, x, y))
                continue
        for xx, yy in zip(dx, dy):
            nx = x + xx
            ny = y + yy
            if 0 <= nx < N and 0 <= ny < N:
                if v[nx][ny]:
                    continue
                if grid[nx][ny] < 0:
                    continue
                if cgrid[nx][ny] == 1:
                    continue
                if grid[nx][ny] >= 0:
                    q.append((nx, ny, cost + 1))
                    v[nx][ny] = True

    if len(m) > 0:
        cgrid[cx][cy] = 0
        c, cx, cy = heapq.heappop(m)
        cgrid[cx][cy] = 1
        return cx, cy
    else:
        return cx, cy




for l in range(L):
    ### 청소기 이동
    ncleaner = []
    for c in cleaner:
        cx, cy = bfs_search(c[0], c[1])
        ncleaner.append((cx, cy))

    cleaner = ncleaner

    for c in cleaner:
        cx, cy = c
        ### 청소기 방향선정

        rr = []
        for i in range(4):
            clean = 0
            for j, (xx, yy) in enumerate(zip(dx, dy)):
                if i == j:
                    continue
                nx = cx + xx
                ny = cy + yy
                if 0 <= nx < N and 0 <= ny < N:
                    if grid[nx][ny] <= 0:
                        continue
                    if grid[nx][ny] >= 20:
                        clean += 20
                    else:
                        clean += grid[nx][ny]

            heapq.heappush(rr, (-clean, i))

        ### 청소
        _, r = heapq.heappop(rr)
        if grid[cx][cy] > 20:
            grid[cx][cy] -= 20
        else:
            grid[cx][cy] = 0
        for j, (xx, yy) in enumerate(zip(dx, dy)):
            if r == j:
                continue
            nx = cx + xx
            ny = cy + yy
            if 0 <= nx < N and 0 <= ny < N:
                if grid[nx][ny] <= 0:
                    continue
                if grid[nx][ny] >= 20:
                    grid[nx][ny] -= 20
                else:
                    grid[nx][ny] = 0


    ### 먼지 축적
    for i in range(N):
        for j in range(N):
            if grid[i][j] > 0:
                grid[i][j] += 5

    ### 먼지 확산
    ngrid = copy.deepcopy(grid)
    for x in range(N):
        for y in range(N):
            if grid[x][y] == 0:
                for xx, yy in zip(dx, dy):
                    nx = x + xx
                    ny = y + yy
                    if 0 <= nx < N and 0 <= ny < N:
                        if grid[nx][ny] > 0:
                            ngrid[x][y] += grid[nx][ny]

                ngrid[x][y] = ngrid[x][y] // 10

    grid = ngrid

    value = 0
    ### 출력
    for x in range(N):
        for y in range(N):
            if grid[x][y] > 0:
                value += grid[x][y]

    print(value)

