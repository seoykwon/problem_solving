import sys
# sys.stdin = open('input.txt', 'r')
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
            rep.append([-faith[ni][nj], ni, nj])

    # 대표자 선발, 신앙심 배부
    rep.sort()
    group_id[id] = [rep[0][1], rep[0][2]]
    rev_group_id[rep[0][1], rep[0][2]] = id
    l = len(rep)

    for (f, i, j) in rep:
        # 대표자
        # if (i, j) in group_id[id]:
        if [i, j] == group_id[id]:
            faith[i][j] += l - 1
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
    gN = grouping(N, food, group, group_id, faith, rev_group_id)

    return gN

def spread(i, j, valid, N, faith, group, group_id, food, rev_group_id):
    d = faith[i][j] % 4
    eagerness = faith[i][j] - 1
    faith[i][j] = 1

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
        x = eagerness
        if y < eagerness:
            food[ni][nj] = cf
            eagerness = max(0, eagerness - (y + 1))
            faith[ni][nj] += 1
            if (ni, nj) in rev_group_id.keys():
                valid[rev_group_id[(ni, nj)]] = False

        # 약한 전파
        elif eagerness <= y:
            food[ni][nj] |= cf
            faith[ni][nj] += x

            eagerness = 0

            if (ni, nj) in rev_group_id.keys():
                valid[rev_group_id[(ni, nj)]] = False

        
        if eagerness == 0:
            break

        dist += 1


def evening(gN, N, faith, food, group, group_id, rev_group_id):
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

    for (f, i, j) in single:
        if valid[group[i][j]]:
            spread(i, j, valid, N, faith, group, group_id, food, rev_group_id)

    for (f, i, j) in twice:
        if valid[group[i][j]]:
            spread(i, j, valid, N, faith, group, group_id, food, rev_group_id)

    for (f, i, j) in triple:
        if valid[group[i][j]]:
            spread(i, j, valid, N, faith, group, group_id, food, rev_group_id)
    

def print_faith(N, food, faith):
    result = [0] * 7

    for i in range(N):
        for j in range(N):
            # 민트초코우유: 7
            if food[i][j] == 7:
                result[0] += faith[i][j]

            # 민트초코: 6
            elif food[i][j] == 6:
                result[1] += faith[i][j]

            # 민트우유: 5
            elif food[i][j] == 5:
                result[2] += faith[i][j]

            # 초코우유: 3
            elif food[i][j] == 3:
                result[3] += faith[i][j]

            # 우유: 1
            elif food[i][j] == 1:
                result[4] += faith[i][j]

            # 초코: 2
            elif food[i][j] == 2:
                result[5] += faith[i][j]

            # 민트: 4
            elif food[i][j] == 4:
                result[6] += faith[i][j]

    print(result[0], result[1], result[2], result[3], result[4], result[5], result[6])

def solve():
    N, T = map(int, input().split())

    food = [[0] * N for _ in range(N)]
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
        print_faith(N, food, faith)

        T -= 1


solve()

'''
버그 종류가 다양했어요
이번 코드에서 나온 버그들은 성격이 다 달랐어요.

len 오타 → 단순 실수
i, j vs ni, nj → 집중력 문제
in group_id[id] → 파이썬 동작 방식 이해
%4 방향 계산 → 문제 독해 실수
^= vs |= → 비트 연산 논리 오류

디버깅 팁:
1. 함수별로 바로 검증하기
2. print를 아낌없이 찍기
'''

'''
남들은 어떻게 풀었나 확인해보기
'''

import sys
from collections import deque

input = sys.stdin.readline

# 위, 아래, 왼쪽, 오른쪽 방향 정의
DIR = [(-1, 0), (1, 0), (0, -1), (0, 1)]

def add_morning_belief(SIZE, B):
    """아침: 모든 학생의 신앙심 1 증가"""
    for r in range(SIZE):
        for c in range(SIZE):
            B[r][c] += 1

def set_noon_group(SIZE, F, B):
    """점심: 동일 음식끼리 그룹 형성 및 대표 선정, 신앙심 재분배"""
    visited = [[False] * SIZE for _ in range(SIZE)]
    groups = [] # (그룹 좌표 리스트, 그룹 음식 set) 저장

    for r in range(SIZE):
        for c in range(SIZE):
            if not visited[r][c]:
                curr_f = F[r][c]
                q = deque([(r, c)])
                visited[r][c] = True
                group_coords = [(r, c)]

                while q:
                    cr, cc = q.popleft()
                    for dr, dc in DIR:
                        mr = cr + dr
                        mc = cc + dc
                        # 음식이 '완전히' 같은 경우만 그룹화 (set 비교)
                        if 0 <= mr < SIZE and 0 <= mc < SIZE and not visited[mr][mc] and F[mr][mc] == curr_f:
                            visited[mr][mc] = True
                            group_coords.append((mr, mc))
                            q.append((mr, mc))
                groups.append((group_coords, curr_f))

    group_info = [] # 전파 단계에서 사용할 대표 정보 저장
    for group_coords, food_set in groups:
        # 대표 선정 기준: 1. 신앙심 큰 순 2. 행 작은 순 3. 열 작은 순
        # sort의 key를 사용해 한 번에 정렬
        group_coords.sort(key=lambda x: (-B[x[0]][x[1]], x[0], x[1]))
        head_r, head_c = group_coords[0]

        # 신앙심 재분배: 대표는 (원래수-1)만큼 얻고, 나머지는 1씩 감소
        transfer_amount = len(group_coords) - 1
        for gr, gc in group_coords:
            if (gr, gc) == (head_r, head_c):
                B[gr][gc] += transfer_amount
            else:
                B[gr][gc] -= 1

        group_info.append({'head': (head_r, head_c), 'food': food_set})
    
    return group_info

def spread_foot_at_dinner(SIZE, F, B, group_info):
    """저녁: 단계별 전파 진행"""
    # 1. 진짜 순서 결정용 리스트 생성
    # 정렬 기준: 1. 음식 종류 수 2. 대표 신앙심 높은 순 3. 행 작은 순 4. 열 작은 순
    group_info.sort(key=lambda x: (
        len(x['food']),
        -B[x['head'][0]][x['head'][1]],
        x['head'][0],
        x['head'][1]
    ))

    is_defensive = [[False] * SIZE for _ in range(SIZE)]

    for g in group_info:
        hr, hc = g['head']

        # 방어 상태 확인: 당일 이미 전파를 받은 대표는 전파하지 않음
        if is_defensive[hr][hc]:
            continue

        eager = B[hr][hc] - 1
        direction_idx = B[hr][hc] % 4
        dr, dc = DIR[direction_idx]
        B[hr][hc] = 1 # 전파자는 신앙심 1만 남음

        curr_food = g['food']
        tr, tc = hr, hc

        while eager > 0:
            tr += dr
            tc += dc

            # 격자 밖으로 나가면 종료
            if not (0 <= tr < SIZE and 0 <= tc < SIZE):
                break

            # 대상과 음식이 완전히 같으면 전파 없이 다음 칸으로 이동
            if F[tr][tc] == curr_food:
                continue

            # 전파 발생 (전파 받은 대상은 즉시 방어상태)
            is_defensive[tr][tc] = True
            y = B[tr][tc]

            if eager > y: # 강한 전파
                B[tr][tc] += 1
                eager -= (y + 1)
                F[tr][tc] = set(curr_food) # 완전히 동화
                if eager == 0: break
            else: # 약한 전파
                B[tr][tc] += eager
                F[tr][tc] = F[tr][tc] | curr_food # 기본 음식들 합침
                eager = 0 # 간절함 소진되어 종료

def solve():
    input_data = input().split()
    if not input_data: return
    N, T = map(int, input_data)

    # 초기 음식 상태 (set으로 저장)
    F = [[set(char) for char in input().strip()] for _ in range(N)]

    # 초기 신앙심
    B = [list(map(int, input().split())) for _ in range(N)]

    for _ in range(T):
        add_morning_belief(N, B)
        group_info = set_noon_group(N, F, B)
        spread_foot_at_dinner(N, F, B, group_info)

        # 결과 출력을 위한 음식 순서 정의
        order = ['CMT', 'CT', 'MT', 'CM', 'M', 'C', 'T']
        sum_belief = {k: 0 for k in order}

        for r in range(N):
            for c in range(N):
                key = "".join(sorted(list(F[r][c])))
                if key in sum_belief:
                    sum_belief[key] += B[r][c]

        # 순서대로 출력
        print(*(sum_belief[k] for k in order))

if __name__ == "__main__":
    solve()

# 남의 코드 2
from collections import deque

N, T = map(int, input().split())

# 음식 정보
F = [list(input().strip()) for _ in range(N)]

B = [list(map(int, input().split())) for _ in range(N)]

exp = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def morning():
    """
    1. 아침 시간: 모든 학생의 신앙심(B)을 1씩 증가
    """
    for r in range(N):
        for c in range(N):
            B[r][c] += 1


def lunch():
    """
    2. 점심 시간:
    - 인접 & 신봉 음식이 완전히 같은 학생끼리 그룹 형성 (BFS/DFS)
    - 그룹 내 대표자 선정 (신앙심 최댓값 -> r 최소 -> c 최소)
    - 신앙심 분배: 그룹원은 대표자에게 1씩 주고, 대표자는 (그룹원 수 - 1)만큼 획득
    """
    visited = [[False] * N for _ in range(N)]
    reps = []  # 대표자 담아
    # 1. 그룹핑
    for i in range(N):
        for j in range(N):
            if not visited[i][j]:
                q = deque([(i, j)])
                visited[i][j] = True
                group = [(i, j)]  # 이 그룹에 속한 학생의 좌표 모음

                # 2. 대표 선출
                rep_r, rep_c = i, j  # 대표자 후보 위치 초기화
                max_b = B[i][j]

                while q:
                    r, c = q.popleft()
                    for dr, dc in exp:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < N and 0 <= nc < N and not visited[nr][nc]:
                            if F[r][c] == F[nr][nc]:
                                visited[nr][nc] = True
                                q.append((nr, nc))
                                group.append((nr, nc))

                                # 대장 조건 갱신 검사
                                cand_b = B[nr][nc]
                                if cand_b > max_b:
                                    max_b = cand_b
                                    rep_r, rep_c = nr, nc
                                elif cand_b == max_b:
                                    if nr < rep_r:
                                        rep_r, rep_c = nr, nc
                                    elif nr == rep_r and nc < rep_c:
                                        rep_r, rep_c = nr, nc
                # 3. 신앙심 분배
                group_size = len(group)
                if group_size > 1:
                    for gr, gc in group:
                        if (gr, gc) == (rep_r, rep_c):
                            B[gr][gc] += (group_size - 1)
                        else:
                            B[gr][gc] -= 1
                reps.append((rep_r, rep_c))
    return reps


def evening(reps):
    """
    3. 저녁 시간:
    - 전파 순서 결정 (단일 -> 이중 -> 삼중 조합 순, 그 안에서는 신앙심 -> r -> c 순)
    - 전파자들의 전파 시뮬레이션 진행
      * 방어 상태(당일 전파받은 대표자) 처리 주의
      * 강한 전파 (x > y) / 약한 전파 (x <= y) 로직 구현
    """
    sorted_reps = []
    for r, c in reps:
        food_len = len(F[r][c])
        b_val = B[r][c]
        sorted_reps.append((food_len, -b_val, r, c))
    sorted_reps.sort()

    defended = set()

    for food_len, neg_b, r, c in sorted_reps:
        if (r, c) in defended:
            continue

        orig_b = B[r][c]
        if orig_b <= 1:
            continue
        x = orig_b - 1
        B[r][c] = 1

        d = orig_b % 4
        my_food = F[r][c]

        nr, nc = r, c

        while x > 0:
            dr, dc = exp[d]
            nr += dr
            nc += dc

            if not (0 <= nr < N and 0 <= nc < N):
                break
            tg_food = F[nr][nc]

            if my_food == tg_food:
                continue

            y = B[nr][nc]

            if x > y:
                F[nr][nc] = my_food
                B[nr][nc] = y + 1
                x -= (y + 1)
                defended.add((nr, nc))
            else:
                combined_food = "".join(sorted(set(my_food) | set(tg_food)))
                F[nr][nc] = combined_food

                B[nr][nc] = y + x
                x = 0
                defended.add((nr, nc))
                break


def print_result():
    """
    각 날이 끝난 후, 지정된 순서대로 신앙심 총합 출력
    순서: 민트초코우유(TCM), 민트초코(TC), 민트우유(TM), 초코우유(CM), 우유(M), 초코(C), 민트(T)
    """
    targets = ["CMT", "CT", "MT", "CM", "M", "C", "T"]

    score_dict = {food: 0 for food in targets}

    for r in range(N):
        for c in range(N):
            food = F[r][c]
            if food in score_dict:
                score_dict[food] += B[r][c]

    result_str = " ".join(str(score_dict[food]) for food in targets)
    print(result_str)


for day in range(1, T + 1):
    morning()
    reps = lunch()
    evening(reps)
    print_result()
