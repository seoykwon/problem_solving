import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

menu = {'TCM': 7, 'TC': 6, 'TM': 5, 'CM': 3, 'M': 1, 'C': 2, 'T': 4}

# 위 아래 왼쪽 오른쪽
dy = [-1, 1, 0, 0]
dx = [0, 0, -1, 1]

def morning(N, faith):
    for i in range(N):
        for j in range(N):
            faith[i][j] += 1

def bfs(N, food, group, group_id, id, visited, i, j, faith, rev_group_id):
    q = deque()

    q.append([i, j])
    visited[i][j] = True
    cf = food[i][j]
    group[i][j] = id

    rep = []
    rep.append([-faith[i][j], i, j])

    while q:
        ci, cj = q.popleft()

        for d in range(4):
            ni = ci + dy[d]
            nj = cj + dx[d]

            if ni < 0 or nj < 0 or ni >= N or nj >= N:
                continue
            if visited[ni][nj]:
                continue
            if food[ni][nj] != cf:
                continue

            q.append([ni, nj])
            visited[ni][nj] = True
            group[ni][nj] = id
            rep.append([-faith[ni][nj], i, j])

    # 대표자 선발, 신앙심 배부
    rep.sort()
    group_id[id] = [rep[0][1], rep[0][2]]
    rev_group_id[rep[0][1], rep[0][2]] = id
    l = len(rep)

    for i, j in rep:
        # 대표자
        if (i, j) in group_id[id]:
            faith[i][j] += len - 1
        else:
            faith[i][j] -= 1


def grouping(N, food, group, group_id, faith, rev_group_id):
    visited = [[False] * N for _ in range(N)]
    id = 1

    for i in range(N):
        for j in range(N):
            if not visited[i][j]:
                bfs(N, food, group, group_id, id, visited, i, j, faith, rev_group_id)
                id += 1

    return id

def noon(N, faith, food, group, group_id, rev_group_id):
    # 인접한 학생과 신봉 음식 같으면 -> 그룹 형성
    # 대표자 (신앙심, r 작은 사람, c 작은 사람) 순서로 선정
    # 신앙심 업데이트

    # gN = max ID 값
    gN = grouping(N, food, group, group_id, rev_group_id)

    return gN

def spread(i, j, valid, N, faith, group, group_id, food):
    eagerness = f - 1
    faith[i][j] = 1

    d = eagerness % 4
    dist = 1
    cf = food[i][j]
    while True:
        ni = i + (dy[d] * dist)
        nj = j + (dx[d] * dist)

        if ni < 0 or nj < 0 or ni >= N or nj >= N:
            break
        if food[ni][nj] == cf:
            dist += 1
            continue
        # 전파 대상이 전파자와 신봉 음식 다른 경우 = 전파 진행
        # 강한 전파
        y = faith[ni][nj]
        x = faith[i][j]
        if y < x:
            food[ni][nj] = cf
            eagerness = max(0, eagerness - (y + 1))
            faith[ni][nj] += 1

        # 약한 전파
        elif x <= y:
            food[ni][nj] ^= cf
            faith[ni][nj] += x

            eagerness = 0
        
        if eagerness == 0:
            break


def evening(gN, N, faith, food, group, group_id):
    # 전파 당한 대표자 표기
    valid = [True] * gN

    # 전파 그룹 순서대로 진행, 같은 그룹 내에서는 (신앙심, 행 번호, 열번호)
    single = []
    twice = []
    triple = []

    for (i, j) in group_id.values():
        if food[i][j] == 1 or food[i][j] == 2 or food[i][j] == 4:
            single.append([-faith[i][j], i, j])
        elif food[i][j] == 6 or food[i][j] == 5 or food[i][j] == 3:
            twice.append([-faith[i][j], i, j])
        else:
            triple.append([-faith[i][j], i, j])

    single.sort()
    twice.sort()
    triple.sort()

    for k, (f, i, j) in single.items():
        if valid[k]:
            spread(i, j, valid, N, faith, group, group_id, food)

    for k, (f, i, j) in twice.items():
        if valid[k]:
            spread(i, j, valid, N, faith, group, group_id, food)

    for k, (f, i, j) in triple.items():
        if valid[k]:
            spread(i, j, valid, N, faith, group, group_id, food)
    

def print_faith():


def solve():
    N, T = map(int, input().split())

    food = []
    tmp = []
    for _ in range(N):
        tmp.append(list(map(str, input().strip())))

    for i in range(N):
        for j in range(N):
            food[i][j] = menu[tmp[i][j]]

    faith = []

    for _ in range(N):
        faith.append(list(map(int, input().split())))

    while T:
        morning(N, faith)

        group = [[0] * N for _ in range(N)]
        group_id = {} # (id) : 대표자(i, j) -> menubd[i][j]
        rev_group_id = {}

        gN = noon(N, faith, food, group, group_id, rev_group_id)

        evening(gN, N, faith, food, group, group_id, rev_group_id)

        # 7개 신앙심 프린트
        print_faith()

        T -= 1


solve()