import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque
import math

# 우 하 좌 상
dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]

def move_turtle(N, M, turtle, board, turtle_set, result, time):
    # 아이디가 작은 순서대로 모든 바다거북이 최단경로 탐색
    # 앞선 거북이의 이동 결과 즉시 다음 거북이 경로 탐색에 반영
    for m in range(M):
        # 만약 이미 탈출한 바다거북이면
        if turtle[m][0] == -1:
            continue
        # 만약 화석이 된 거북이면
        if turtle[m][0] == -2:
            continue

        cur_turtle_r = turtle[m][0]
        cur_turtle_c = turtle[m][1]

        queue = deque()
        visited = [[False]*N for _ in range(N)]
        queue.append((N-1, N-1, 0))

        while queue:
            cr, cc, dist = queue.popleft()
            visited[cr][cc] = True

            if cr == cur_turtle_r and cc == cur_turtle_c:
                # 최단경로 존재
                turtle_set.discard((cur_turtle_r, cur_turtle_c))
                nd = (d + 2) % 4
                r = cur_turtle_r + dy[nd]
                c = cur_turtle_c + dx[nd]
                turtle[m][0] = r
                turtle[m][1] = c
                # 도착했을 시
                if r == N - 1 and c == N - 1:
                    result[m] = time
                    turtle[m][0] = -1
                    break

                turtle_set.add((turtle[m][0], turtle[m][1]))
                break

            for d in range(3, -1, -1):
                nr = cr + dy[d]
                nc = cc + dx[d]

                if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc]:
                    continue
                if board[nr][nc] == 1:
                    continue
                # 다른 바다거북 존재시 못 감
                if turtle_set.union((nr, nc)):
                    continue

                visited[nr][nc] = True
                queue.append((nr, nc))

def vol_pressure(volcano_cur):
    for key in volcano_cur:
        volcano_cur[key] += 10

def erupt_vol(volcano_cur, volcano_max, N, board, turtle, turtle_set):
    earth = [[0]*N for _ in range(N)]
    erupted = set()
    # 1. 열기 전파
    for key in volcano_cur:
        if volcano_cur[key] >= volcano_max[key]:
            erupted.add(key)
            heat = volcano_cur[key] - volcano_max[key]
            # 열기는 상하좌우 4방향으로 뻗어 나감
            r, c = map(int, key)
            earth[r][c] += heat

            for d in range(4):
                prev_heat = heat
                for dist in range(1, N):
                    nr = r + (dy[d] * dist)
                    nc = c + (dx[d] * dist)

                    if nr < 0 or nc < 0 or nr >= N or nc >= N:
                        break
                    if board[nr][nc] == 1:
                        break

                    prev_heat = prev_heat // 2
                    if prev_heat <= 0:
                        break

                    earth[nr][nc] += prev_heat

    # 2. 연쇄 반응
    for (r, c), v in volcano_cur.items():
        if volcano_cur[(r, c)] + earth[r][c] >= volcano_max[(r, c)]:
            erupted.add((r, c))
            heat = volcano_cur[(r, c)] + earth[r][c] - volcano_max[(r, c)]
            earth[r][c] += heat

            for d in range(4):
                prev_heat = heat
                for dist in range(1, N):
                    nr = r + (dy[d] * dist)
                    nc = c + (dx[d] * dist)

                    if nr < 0 or nc < 0 or nr >= N or nc >= N:
                        break
                    if board[nr][nc] == 1:
                        break

                    prev_heat = prev_heat // 2
                    if prev_heat <= 0:
                        break

                    earth[nr][nc] += prev_heat

    # 3. 바다거북의 위기 (화석화)
    for (r, c) in turtle_set:
        if earth[r][c] >= 20:
            m = turtle_dict.get((r, c))
            turtle[m][0] = -2

    return erupted

def reset(erupted, volcano_cur):
    # 바다 위의 모든 열기 정보 사라짐 (earth는 지역 변수로 초기화됨)
    # 이번에 분출 일으킨 화산 모두 0으로 초기화
    for key in erupted:
        volcano_cur[key] = 0

def solve():
    N, M, K = map(int, input())

    board = []
    for _ in range(N):
        board.append(list(map(int, input().split())))

    turtle = []
    turtle_set = set()
    turtle_dict = {}
    for m in range(M):
        r, c = map(int, input().split())
        turtle.append([r, c])
        turtle_set.add((r, c))
        turtle_dict[(r, c)] = m

    volcano_cur = {}
    volcano_max = {}
    for k in range(K):
        r, c, p = map(int, input().split())
        volcano_cur[(r, c)] = 0
        volcano_max[(r, c)] = p

    result = [0] * M

    for time in range(0, 101):

        # 1단계 바다거북 이동
        move_turtle(N, M, turtle, board, turtle_set, result, time)

        # 2단계 화산 압력 증가
        vol_pressure(volcano_cur)

        # 3단계 화산 분출 및 연쇄 반응
        erupted = erupt_vol(volcano_cur, volcano_max, N, board, turtle, turtle_set)

        # 4단계 환경 초기화
        reset(erupted, volcano_cur)

solve()