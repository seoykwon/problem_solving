import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

'''
1단계: 인접 탐험 
    (상하좌우 인접 칸 중 방문하지 않은 바다 칸이 있다면)
    1. 현재 바라보는 방향으로 직진
    2. 좌회전 (90도 반시계 방향 회전) 후 직진
    3. 우회전 (90도 시계 방향 회전) 후 직진
    4. 180도 회전 후 직진
2단계: 가장 가까운 바다로 이동
    인접한 칸 모두에 방문 가능한 바다가 없다면, 아직 방문하지 않은 바다 칸 중 가장 가까운 칸
    ?? 가장 가까운 칸을 어떻게 찾지?
    1. 거리는 상하좌우로 인접한 칸을 한 칸씩 이동하여 도달하는 데 필요한 최소 이동 횟수
        암초는 지나갈 수 없지만, 이미 방문한 바다는 지나갈 수 있음
        N <= 50이어서 완전 탐색 돌려도 되는 건가? 그리고 거리 계산식
    2. 가장 가까운 칸이 여러 개라면 행 번호가 가장 작은 칸 선택, 행 번호 같으면 열 번호가 가장 작은 칸
    3. 선택한 칸까지 최단 거리 이동 (BFS?) 매 이동마다 선택한 칸까지의 거리가 1줄어드는 인접한 칸 중 하나로 이동
        그러한 칸이 여러 개면 좌, 하, 우, 상 우선순위
    4. 도착 후 바라보는 방향 마지막 이동 방향으로 갱신

N*N 보드에서 각 칸과의 거리는 보통 맨해튼 거리로 계산
d = |x1 - x2| + |y1 - y2|
'''

from collections import deque

# 1 = 상, 2 = 하, 3 = 좌, 4 = 우
# dx = [0, 0, 0, -1, 1]
# dy = [0, -1, 1, 0, 0]

dir_dict = {1: 3, 2: 1, 3: 0, 4: 2}

# 좌 하 우 상
dir = [[0, -1], [1, 0], [0, 1], [-1, 0]]

def neighbors(visited):
    
    queue = deque()
    direction = dir_dict[d]
    queue.append((r, c, direction))
    rr, rc, rdist = 0, 0, d

    while queue:
        cr, cc, dist = queue.popleft()
        visited[cr][cc] = True
        rr, rc, rdist = cr, cc, dist
        print(cr, " ", cc)

        # 1. 현재 방향
        nr = cr + dir[dist]
        nc = cc + dir[dist]

        if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc] or board[nr][nc]:
            continue
        visited[nr][nc] = True
        queue.append((nr, nc, dist))

        # 2. 좌회전
        dist = (dist + 1) % 4
        nr = cr + dir[dist]
        nc = cc + dir[dist]

        if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc] or board[nr][nc]:
            continue
        visited[nr][nc] = True
        queue.append((nr, nc, dist))

        # 3. 우회전
        dist = (dist + 2) % 4
        nr = cr + dir[dist]
        nc = cc + dir[dist]

        if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc] or board[nr][nc]:
            continue
        visited[nr][nc] = True
        queue.append((nr, nc, dist))

        # 4. 반대 방향
        dist = (dist - 1) % 4
        nr = cr + dir[dist]
        nc = cc + dir[dist]

        if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc] or board[nr][nc]:
            continue
        visited[nr][nc] = True
        queue.append((nr, nc, dist))

    return (rr, rc, rdist)
    

def moving(r, c, d, visited):
    # 아직 방문하지 않은 바다 칸 중 현재 위치에서 가장 가까운 칸
    INF = float('inf')
    manhattan = [[INF]*N for _ in range(N)]
    nr, nc, nd = INF, INF, INF
    dist = INF

    for i in range(N):
        for j in range(N):
            if not visited[i][j] and board[i][j] != 1:
                tmp_dist = abs(i - r) + abs(j - c)
                manhattan[i][j] = tmp_dist
                if tmp_dist < dist:
                    dist = tmp_dist
                    nr = i
                    nc = j
                    nd = tmp_dist

    # 선택한 칸까지 최단 거리로 이동
    # 선택한 칸까지의 거리가 1 줄어드는 인접한 칸 이동
    queue = deque()
    queue.append((r, c, dist))
    visited2 = visited[:]

    while queue:
        cr, cc, cd = queue.popleft()
        visited2[cr][cc] = True
        if cr == nr and cc == nc:
            return (cr, cc)

        print(cr, " ", cc)

        for direction in range(4):
            nnr = cr + dir[direction][0]
            nnc = cc + dir[direction][1]

            if nnr < 0 or nnc < 0 or nnr >= N or nnc >= N or visited2[nnr][nnc]:
                continue
            
            tmp_dist = abs(cr - nnr) + abs(cc - nnc)
            if tmp_dist < cd:
                visited2[nnr][nnc] = True
                queue.append((nnr, nnc, tmp_dist))



def solve():
    visited = [[False]*N for _ in range(N)]
    while True:
        r, c, d = neighbors(visited)

        r, c = moving(r, c, d)

        flag = True
        for i in range(N):
            for j in range(N):
                if not visited[i][j] and board[i][j] != 1:
                    flag = False
        if flag:
            break


N, r, c, d = map(int, input().split())

board = []

for _ in range(N):
    board.append(list(map(int, input())))

solve()