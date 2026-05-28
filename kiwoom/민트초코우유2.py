import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque
import heapq

# f_order = [7, 6, 5, 3, 1, 2, 4]

def morning(N, faith):
    for i in range(N):
        for j in range(N):
            faith[i][j] += 1

# bfs(N, food, faith, visited, represent, group, i, j, g_id)
def bfs(N, food, faith, visited, represent, group, i, j, g_id, rset):
    q = deque()
    visited[i][j] = True
    q.append((i, j))
    group[i][j] = g_id

    candidate = []
    heapq.heappush(candidate, (-faith[i][j], i, j))

    while q:
        cr, cc = q.popleft()

        for dr, dc in ((-1,0),(1,0),(0,-1),(0,1)):
            nr, nc = cr+dr, cc+dc

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            if food[nr][nc] != food[i][j]:
                continue
            q.append((nr, nc))
            visited[nr][nc] = True
            group[nr][nc] = g_id
            heapq.heappush(candidate, (-faith[nr][nc], nr, nc))

    _, hr, hc = heapq.heappop(candidate)
    sz = len(candidate)
    represent[g_id] = [hr, hc]
    rset.add((hr, hc))

    faith[hr][hc] += sz

    while candidate:
        _, r, c = heapq.heappop(candidate)
        faith[r][c] -= 1

    return represent

# noon(N, food, faith, represent, group)
def noon(N, food, faith, represent, group, rset):
    g_id = 1
    visited = [[False]*N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            if not visited[i][j]:
                bfs(N, food, faith, visited, represent, group, i, j, g_id, rset)
                g_id += 1

    return represent

def spread(r, c, faith, food, N, rset):
    sf = faith[r][c]
    eagerness = sf - 1
    d = sf % 4
    defense = set()

    DIR = [[-1,0],[1,0],[0,-1],[0,1]]
    nr, nc = r, c

    while True:
        nr, nc = nr + DIR[d][0], nc + DIR[d][1]

        if nr < 0 or nc < 0 or nr >= N or nc >= N:
            break
        if food[nr][nc] == food[r][c]:
            continue

        # 강한 전파 x > y
        if sf > faith[nr][nc]:
            food[nr][nc] = food[r][c]
            eagerness = max(0, eagerness - (faith[nr][nc] + 1))
            faith[nr][nc] += 1
        # 약한 전파
        elif sf <= faith[nr][nc]:
            food[nr][nc] |= food[r][c]
            eagerness = 0
            faith[nr][nc] += sf
        # 방어상태
        if (nr, nc) in rset:
            defense.add((nr, nc))

    return defense


def night(N, food, faith, represent, group, rset):
    single = []
    double = []
    triple = []

    for k, (rr, rc) in represent.items():
        if food[rr][rc] in (4, 2, 1):
            heapq.heappush(single, (-faith[rr][rc], rr, rc))
        elif food[rr][rc] in (6, 5, 3):
            heapq.heappush(double, (-faith[rr][rc], rr, rc))
        elif food[rr][rc] == 7:
            heapq.heappush(triple, (-faith[rr][rc], rr, rc))

    df = set()

    while single:
        _, cr, cc = heapq.heappop(single)
        if (cr, cc) in df:
            continue
        df = spread(cr, cc, faith, food, N, rset)

    while double:
        _, cr, cc = heapq.heappop(double)
        if (cr, cc) in df:
            continue
        df = spread(cr, cc, faith, food, N, rset)

    while triple:
        _, cr, cc = heapq.heappop(triple)
        if (cr, cc) in df:
            continue
        df = spread(cr, cc, faith, food, N, rset)

def print_result(N, food, faith):
    f_order = {7:0, 6:1, 5:2, 3:3, 1:4, 2:5, 4:6}
    ans = [0]*7

    for i in range(N):
        for j in range(N):
            idx = f_order[food[i][j]]
            ans[idx] += faith[i][j]

    print(*ans)

def solve():
    N, T = map(int, input().split())

    tmp = []
    for _ in range(N):
        tmp.append(list(map(str, input().strip())))

    food = [[0]*N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            if tmp[i][j] == 'T':
                food[i][j] = 4
            elif tmp[i][j] == 'C':
                food[i][j] = 2
            elif tmp[i][j] == 'M':
                food[i][j] = 1

    faith = []
    for _ in range(N):
        faith.append(list(map(int, input().split())))

    # print(*board)
    # print(*faith)
    while T:
        # 1. 아침시간
        morning(N, faith)

        # 2. 점심시간
        represent = {}
        rset = set()
        group = [[0]*N for _ in range(N)]
        represent = noon(N, food, faith, represent, group, rset)


        night(N, food, faith, represent, group, rset)

        # print(*represent)
        print_result(N, food, faith)

        T -= 1

solve()

