import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque
import heapq

# 상하좌우
dy = [-1, 1, 0, 0]
dx = [0, 0, -1, 1]

def bfs(bd, N, warriors, mr, mc, pr, pc):
    q = deque()
    visited = [[False] * N for _ in range(N)]

    q.append([mr, mc, -1])
    visited[mr][mc] = True

    candidates = []

    res = -1

    while q:
        cr, cc, dir = q.popleft()

        if cr == pr and cc == pc:
            res = dir

        for d in range(4):
            nr = cr + dy[d]
            nc = cc + dx[d]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            if bd[nr][nc] == 0:
                continue

            # 이동
            if dir == -1:
                q.append([nr, nc, d])
                visited[nr][nc] = True
                continue
            
            if (nr, nc) in warriors:
                candidates.append([nr, nc])

            q.append([nr, nc, dir])
            visited[nr][nc] = True

    if res != -1:
        for r, c in candidates:
            del warriors[(r, c)]
        
        return res
    
    return res
        

def medusa_move(bd, N, warriors, mr, mc, pr, pc):
    # 도로를 따라 한 칸 이동
    dir = bfs(bd, N, warriors, mr, mc, pr, pc)

    if dir == -1:
        return [-1, -1]

    nr = mr + dy[dir]
    nc = mc + dx[dir]

    return [nr, nc]

def medusa_see(bd, N, warriors, mr, mc):
    # 상하좌우 중 전사를 가장 많이 볼 수 있는 방향 바라보기
    potential = []

    cr, cc = mr, mc

    DIR = [[[-1, -1], [-1, 1]], [[1, -1], [1, 1]], [[-1, -1], [1, -1]], [[-1, 1], [1, 1]]]

    for d in range(4):
        w = 0
        # row-rise
        valid_col = [True] * N
        left_r, left_c, right_r, right_c = cr, cc, cr, cc

        valid_row = [True] * N
        top_r, top_c, bottom_r, bottom_c = cr, cc, cr, cc

        warrior_list = []
        vision = [[False] * N for _ in range(N)]

        if d in [0, 1]:
            while True:
                if 0 <= left_r + DIR[d][0][0] < N and valid_col[left_c + DIR[d][0][1]]:
                    left_r = left_r + DIR[d][0][0]

                if 0 <= left_c + DIR[d][0][1] < N and valid_col[left_c + DIR[d][0][1]]:
                    left_c = left_c + DIR[d][0][1]

                if 0 <= right_r + DIR[d][1][0] < N and valid_col[right_c + DIR[d][1][1]]:
                    right_r = right_r + DIR[d][1][0]

                if 0 <= right_c + DIR[d][1][1] < N and valid_col[right_c + DIR[d][1][1]]:
                    right_c = right_c + DIR[d][1][1]

                for c in range(left_c, right_c + 1):
                    if (left_r, c) in warriors and valid_col[c]:
                        # warriors[(left_r, c)] = -2
                        warrior_list.append([left_r, c])
                        valid_col[c] = False
                        w += 1
                    vision[left_r][c] = True

                # 끝점에 전사가 존재
                if (left_r, left_c) in warriors:
                    lc = left_c
                    while lc >= 0:
                        valid_col[lc] = False
                        lc -= 1
                    left_c += 1

                if (right_r, right_c) in warriors:
                    rc = right_c
                    while rc < N:
                        valid_col[rc] = False
                        rc += 1
                    right_c -= 1

                if left_r == N - 1 or left_r == 0:
                    heapq.heappush(potential, (-w, d, warrior_list, vision))
                    break

        # column-wise  
        else:
            while True:
                if 0 <= top_r + DIR[d][0][0] < N and valid_row[top_r + DIR[d][0][0]]:
                    top_r = top_r + DIR[d][0][0]

                if 0 <= top_c + DIR[d][0][1] < N and valid_row[top_r + DIR[d][0][1]]:
                    top_c = top_c + DIR[d][0][1]

                if 0 <= bottom_r + DIR[d][1][0] < N and valid_row[bottom_r + DIR[d][1][0]]:
                    bottom_r = bottom_r + DIR[d][1][0]

                if 0 <= bottom_c + DIR[d][1][1] < N and valid_row[bottom_r + DIR[d][1][0]]:
                    bottom_c = bottom_c + DIR[d][1][1]

                for r in range(top_r, bottom_r + 1):
                    if (r, top_c) in warriors and valid_row[r]:
                        warrior_list.append([r, top_c])
                        valid_row[r] = False
                        w += 1
                    vision[r][top_c] = True

                # 끝점에 전사가 존재
                if (top_r, top_c) in warriors:
                    tr = top_r
                    while tr >= 0:
                        valid_row[tr] = False
                        tr -= 1
                    top_r += 1

                if (bottom_r, bottom_c) in warriors:
                    br = bottom_r
                    while br < N:
                        valid_row[br] = False
                        br += 1
                    bottom_r -= 1
                 
                if top_c == 0 or top_c == N - 1:
                    heapq.heappush(potential, (-w, d, warrior_list, vision))
                    break
    
    # 방향 고르고 전사들 돌로 만들기
    # -w, d, wlst, vbd = potential[0]
    neg_w, d, wlst, vbd = potential[0]

    w = neg_w

    for r, c in wlst:
        warriors[(r, c)] = -1

    return vbd

def calc(mr, mc, N):
    bd = [[-1] * N for _ in range(N)]

    # q = deque()
    # q.append([mr, mc, 0])
    # bd[mr][mc] = 0

    # while q:
    #     cr, cc, d = q.popleft()

    #     for d in range(4):
    #         nr = cr + dy[d]
    #         nc = cc + dx[d]

    #         if nr < 0 or nc < 0 or nr >= N or nc >= N:
    #             continue
    #         if bd[nr][nc] != -1:
    #             continue
    #         q.append([nr, nc, d + 1])
    #         bd[nr][nc] = d + 1
    for i in range(N):
        for j in range(N):
            bd[i][j] = abs(i - mr) + abs(j - mc)
    
    return bd


def hop1(wr, wc, mr, mc, N, vision_bd, dbd):
    # 상하좌우
    # 메두사와 거리를 줄일 수 있는 방향으로 
    q = deque()
    visited = [[False] * N for _ in range(N)]

    q.append([wr, wc, -1])
    visited[wr][wc] = True

    while q:
        cr, cc, dir = q.popleft()

        if cr == mr and cc == mc:
            return dir
        
        for d in range(4):
            nr = cr + dy[d]
            nc = cc + dx[d]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            if dbd[nr][nc] != dbd[cr][cc] - 1:
                continue
            if vision_bd[nr][nc]:
                continue

            if dir == -1:
                dir = d
            
            q.append([nr, nc, dir])
            visited[nr][nc] = True


ddy = [0, 0, -1, 1]
ddx = [-1, 1, 0, 0]
def hop2(wr, wc, mr, mc, N, vision_bd, dbd):
    # 좌우상하
    # 메두사와 거리를 줄일 수 있는 방향으로 
    q = deque()
    visited = [[False] * N for _ in range(N)]

    q.append([wr, wc, -1])
    visited[wr][wc] = True

    while q:
        cr, cc, dir = q.popleft()

        if cr == mr and cc == mc:
            return dir
        
        for d in range(4):
            nr = cr + ddy[d]
            nc = cc + ddx[d]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            if dbd[nr][nc] != dbd[cr][cc] - 1:
                continue
            if vision_bd[nr][nc]:
                continue

            if dir == -1:
                dir = d
            
            q.append([nr, nc, dir])
            visited[nr][nc] = True
    

def warrior_move(warriors, mr, mc, N, vision_bd):
    dist_bd = calc(mr, mc, N)

    to_delete = []
    to_add = []

    for wr, wc in warriors.keys():
        if warriors[(wr, wc)] == -1:
            continue

        dir = hop1(wr, wc, mr, mc, N, vision_bd, dist_bd)

        nr = wr + dy[dir]
        nc = wc + dx[dir]

        dir = hop2(nr, nc, mr, mc, N, vision_bd, dist_bd)

        nr = nr + ddy[dir]
        nc = nc + ddx[dir]

        to_delete.append([wr, wc])
        to_add.append([nr, nc])

    for wr, wc, nr, nc in zip(to_delete, to_add):
        v = warriors.pop([wr, wc])
        warriors[(nr, nc)] = v

def warrior_attack(mr, mc, warriors):
    # 메두사와 같은 칸에 도달한 전사 사라짐
    to_delete = []

    for r, c in warriors.keys():
        if r == mr and c == mc:
            to_delete.append([r, c])

    for r, c in to_delete:
        del warriors[(r, c)]

def solve():
    N, M = map(int, input().split())

    mr, mc, pr, pc = map(int, input().split())

    warriors = {}
    # 사라진 전사는 딕셔너리에서 삭제함
    # 인덱스가 -1면 임시적으로 돌이 된 전사
    # for i in range(1, M + 1):
    #     r, c = map(int, input().split())
    #     warriors[(r, c)] = i
    wlst = list(map(int, input().split()))

    for i in range(0, 2 * M, 2):
        r = wlst[i]
        c = wlst[i + 1]
        warriors[(r, c)] = i

    board = []
    for _ in range(N):
        board.append(list(map(int, input().split())))

    while warriors:
        # 1. 메두사 이동
        mr, mc = medusa_move(board, N, warriors, mr, mc, pr, pc)

        # 메두사의 집에서 공원까지 이어지는 도로 존재하지 않음
        if mr == -1 and mc == -1:
            print(-1)
            break

        # 2. 메두사의 시선
        vision_bd = medusa_see(board, N, warriors, mr, mc)

        # 3. 전사들의 이동
        warrior_move(warriors, mr, mc, N, vision_bd)

        # 4. 전사의 공격
        warrior_attack(mr, mc, warriors)

        to_modify = []
        for (r, c), v in warriors.items():
            if v == -1:
                to_modify.append([r, c])

        for r, c in to_modify:
            warriors[(r, c)] = 1

solve()