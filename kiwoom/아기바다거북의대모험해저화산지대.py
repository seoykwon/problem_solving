import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

'''
버그1: turtle_dict 거북이 이동 후 갱신 안 됨
버그2: 연쇄 반응에서 이미 분출한 화산을 또 처리함
버그3: result 0번 탈출 판별 오류. time = 0에 탈출한 거북이도 있다.
버그4: 연쇄 반응이 한 번만 체크됨. 화산 B가 화산 A의 열기를 받아 폭발했을 때,
        화산 B의 열기가 화산 C를 또 터뜨릴 수 있지만, 이미 C를 지나쳐버렸다면 
        다시 체크하지 않는다. 
        연쇄 반응은 BFS/큐 방식으로 처리해야 한다.
'''
'''
1. 작은 예제로 직접 손으로 추적
코드 돌리기 전에 2x2, 3x3 같은 최소 케이스를 손으로 한 단계씩 계산해서 기대값을 먼저 구해두는 게 좋습니다. 오늘처럼 dx[d] 오타는 출력이 아예 이상하게 나오기 때문에 금방 잡힙니다.

2. 단계별로 중간값 출력
pythonprint("earth:", earth)
print("turtle 위치:", turtle)
print("erupted:", erupted)
함수 끝마다 이렇게 찍어보면 어느 단계에서 틀렸는지 빠르게 좁힐 수 있습니다.

3. 버그 유형을 패턴으로 외우기
경험상 삼성 코드트리류 문제에서 자주 나오는 버그는 정해져 있습니다.

자료구조 갱신 누락 (오늘의 turtle_dict)
방향 배열 오타 (dx/dy 혼용)
초기값 오류 (오늘의 result = 0)
연쇄 처리 순서 문제 (오늘의 BFS)

4. 구현 전에 자료구조 흐름 정리
turtle, turtle_set, turtle_dict 세 개가 항상 동기화되어야 한다는 걸 코딩 전에 주석으로 먼저 써두면 갱신 누락을 예방할 수 있습니다.
'''
from collections import deque
import math

# 우 하 좌 상
dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]

def move_turtle(N, M, turtle, board, turtle_set, result, time, turtle_dict):
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
                turtle_dict.pop((cur_turtle_r, cur_turtle_c))
                nd = (dist + 2) % 4
                r = cur_turtle_r + dy[nd]
                c = cur_turtle_c + dx[nd]
                turtle[m][0] = r
                turtle[m][1] = c
                # 거북이 위치 갱신

                # 도착했을 시
                if r == N - 1 and c == N - 1:
                    result[m] = time
                    turtle[m][0] = -1
                    break

                turtle_set.add((turtle[m][0], turtle[m][1]))
                turtle_dict[(r, c)] = m
                break

            for d in range(3, -1, -1):
                nr = cr + dy[d]
                nc = cc + dx[d]

                if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc]:
                    continue
                if board[nr][nc] == 1:
                    continue
                # 다른 바다거북 존재시 못 감
                # 자기 위치에는 갈 수 있어야 함
                if (nr, nc) in turtle_set and (nr, nc) != (cur_turtle_r, cur_turtle_c):
                    continue

                visited[nr][nc] = True
                queue.append((nr, nc, d))

def vol_pressure(volcano_cur):
    for key in volcano_cur:
        volcano_cur[key] += 10

def erupt_vol(volcano_cur, volcano_max, N, board, turtle, turtle_dict):
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
    # for (r, c), v in volcano_cur.items():
    #     if (r, c) in erupted:
    #         continue
    #
    #     if volcano_cur[(r, c)] + earth[r][c] >= volcano_max[(r, c)]:
    #         erupted.add((r, c))
    #         heat = volcano_cur[(r, c)] + earth[r][c] - volcano_max[(r, c)]
    #         earth[r][c] += heat
    #
    #         for d in range(4):
    #             prev_heat = heat
    #             for dist in range(1, N):
    #                 nr = r + (dy[d] * dist)
    #                 nc = c + (dx[d] * dist)
    #
    #                 if nr < 0 or nc < 0 or nr >= N or nc >= N:
    #                     break
    #                 if board[nr][nc] == 1:
    #                     break
    #
    #                 prev_heat = prev_heat // 2
    #                 if prev_heat <= 0:
    #                     break
    #
    #                 earth[nr][nc] += prev_heat

    # 나중에 발생한 폭발로 인한 영향을 이미 지나친 화산에 반영할 수 없음
    # 1단계 이후 연쇄 반응 시작점 탐색
    chain_queue = deque()
    # for (r, c) in erupted:
    #     chain_queue.append((r, c))
    for (r, c) in volcano_cur:
        if (r, c) not in erupted:
            if volcano_cur[(r, c)] + earth[r][c] >= volcano_max[(r, c)]:
                erupted.add((r, c))
                chain_queue.append((r, c))

    while chain_queue:
        er, ec = chain_queue.popleft()
        heat = volcano_cur[(er, ec)] + earth[er][ec] - volcano_max[(er, ec)]
        if heat < 0:
            continue

        for d in range(4):
            prev_heat = heat
            for dist in range(1, N):
                nr = er + dy[d] * dist
                nc = ec + dx[d] * dist
                if nr < 0 or nc < 0 or nr >= N or nc >= N:
                    break
                if board[nr][nc] == 1:
                    break
                prev_heat = prev_heat // 2
                if prev_heat <= 0:
                    break
                earth[nr][nc] += prev_heat

                # 새로 폭발하는 화산 체크
                if (nr, nc) in volcano_cur and (nr, nc) not in erupted:
                    if volcano_cur[(nr, nc)] + earth[nr][nc] >= volcano_max[(nr, nc)]:
                        erupted.add((nr, nc))
                        chain_queue.append((nr, nc))

    # 3. 바다거북의 위기 (화석화)
    for (r, c), m in turtle_dict.items():
        if earth[r][c] >= 20:
            # m = turtle_dict.get((r, c))
            turtle[m][0] = -2

    return erupted

def reset(erupted, volcano_cur):
    # 바다 위의 모든 열기 정보 사라짐 (earth는 지역 변수로 초기화됨)
    # 이번에 분출 일으킨 화산 모두 0으로 초기화
    for key in erupted:
        volcano_cur[key] = 0

def solve():
    N, M, K = map(int, input().split())

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

    result = [-1] * M

    for time in range(0, 101):

        # 1단계 바다거북 이동
        move_turtle(N, M, turtle, board, turtle_set, result, time, turtle_dict)

        # 2단계 화산 압력 증가
        vol_pressure(volcano_cur)

        # 3단계 화산 분출 및 연쇄 반응
        erupted = erupt_vol(volcano_cur, volcano_max, N, board, turtle, turtle_dict)

        # 4단계 환경 초기화
        reset(erupted, volcano_cur)

    for i in range(M):
        print(result[i])

solve()