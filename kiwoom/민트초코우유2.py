import sys
# sys.stdin = open('input.txt', 'r')
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
    faith[r][c] = 1
    eagerness = sf - 1
    d = sf % 4
    defense = set()

    DIR = [(-1,0),(1,0),(0,-1),(0,1)]
    nr, nc = r, c

    while True:
        nr, nc = nr + DIR[d][0], nc + DIR[d][1]

        if nr < 0 or nc < 0 or nr >= N or nc >= N:
            break
        if food[nr][nc] == food[r][c]:
            continue

        # 강한 전파 x > y
        if eagerness > faith[nr][nc]:
            food[nr][nc] = food[r][c]
            eagerness = max(0, eagerness - (faith[nr][nc] + 1))
            faith[nr][nc] += 1
        # 약한 전파
        elif eagerness <= faith[nr][nc]:
            food[nr][nc] |= food[r][c]
            faith[nr][nc] += eagerness
            eagerness = 0

        # 방어상태
        if (nr, nc) in rset:
            defense.add((nr, nc))
        if eagerness == 0:
            break

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
        df |= spread(cr, cc, faith, food, N, rset)

    while double:
        _, cr, cc = heapq.heappop(double)
        if (cr, cc) in df:
            continue
        df |= spread(cr, cc, faith, food, N, rset)

    while triple:
        _, cr, cc = heapq.heappop(triple)
        if (cr, cc) in df:
            continue
        df |= spread(cr, cc, faith, food, N, rset)

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

'''
핵심 버그: 저녁(night)의 방어 집합 df를 덮어쓰고 있음
night()를 보면 df를 맨 위에서 딱 한 번 초기화해놓고, 정작 전파할 때마다 이렇게 통째로 갈아끼우고 있어:
pythondf = set()          # ← 누적하려고 한 번만 초기화한 흔적

while single:
    ...
    if (cr, cc) in df:
        continue
    df = spread(...)   # ← 매번 덮어씀! (이전 방어 정보 소멸)
df를 루프 밖에서 한 번만 만들어둔 것 자체가 "밤 전체에 걸쳐 방어 상태를 누적하려는 의도"인데, 실제 코드는 df = spread(...)로 직전 전파에서 만난 대표자 집합만 남겨. 그러면 전파자 사이에 다른 전파가 한 번이라도 끼면 앞에서 쌓인 방어 정보가 다 날아가.
깨지는 시나리오
single 큐에 대표자 A, C, B 순서로 처리된다고 하면:

A 전파 → 직진하다 대표자 B를 공격(전파) → spread가 {B} 반환 → df = {B}
C 전파 → 아무 대표자도 안 만남 → spread가 {} 반환 → df = {} (B 방어 정보 증발)
B 차례 → 원래 A한테 당했으니 방어 상태라 건너뛰어야 하는데, df가 비어 있어서 B가 그대로 전파해버림 → 오답

single/double/triple 세 루프가 같은 df를 공유하니까, 단일 신봉 대표자가 만들어둔 방어 상태가 2종·3종 단계까지 살아남아야 하는데 그게 다 사라지는 거지.
수정
세 군데 df = spread(...)를 전부 누적으로 바꾸면 돼:
pythondf |= spread(cr, cc, faith, food, N, rset)
# 또는
df.update(spread(cr, cc, faith, food, N, rset))
'''