import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque
import heapq

DIR = {1: 0, 2: 2, 3: 1, 4: 3}
# 상 좌 하 우
dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]

def explore(N, r, c, d, board, visited):
    cd = DIR[d]

    # visited = [[False]*N for _ in range(N)]
    q = deque()
    q.append([r, c])
    cr, cc = r, c

    cnt = 0

    while q:
        cr, cc = q.popleft()
        cnt += 1
        print(cr + 1, cc + 1)

        nr = cr + dy[cd]
        nc = cc + dx[cd]
        # if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc] or not board[nr][nc]:
        if 0 <= nr < N and 0 <= nc < N and not visited[nr][nc] and board[nr][nc] == 0:
            q.append([nr, nc])
            continue

        # 좌회전
        nr = cr + dy[(cd + 1) % 4]
        nc = cc + dx[(cd + 1) % 4]
        if 0 <= nr < N and 0 <= nc < N and not visited[nr][nc] and board[nr][nc] == 0:
            q.append([nr, nc])
            continue

        # 우회전
        nr = cr + dy[(cd + 3) % 4]
        nc = cc + dx[(cd + 3) % 4]
        if 0 <= nr < N and 0 <= nc < N and not visited[nr][nc] and board[nr][nc] == 0:
            q.append([nr, nc])
            continue

        # 180도회전
        nr = cr + dy[(cd + 2) % 4]
        nc = cc + dx[(cd + 2) % 4]
        if 0 <= nr < N and 0 <= nc < N and not visited[nr][nc] and board[nr][nc] == 0:
            q.append([nr, nc])
            continue

    return [cr, cc, cnt]

def move(board, N, r, c, visited):
    # 목적지 찾기
    cand = []
    q = deque()
    q.append([r, c, 0])
    used = [[False]*N for _ in range(N)]
    used[r][c] = True

    while q:
        cr, cc, dist = q.popleft()

        if not visited[cr][cc]:
            heapq.heappush(cand, (dist, cr, cc))

        for d in range(4):
            nr = cr + dy[d]
            nc = cc + dx[d]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if board[nr][nc]:
                continue
            if used[nr][nc]:
                continue
            q.append([nr, nc, dist + 1])
            used[nr][nc] = True

    tr, tc = -1, -1
    if cand:
        _, tr, tc = cand[0]

    # 목적지로부터 dist_board = [] 만들기
    dist_board = [[-1]*N for _ in range(N)]
    # dist_board[tr][tc] = 0

    dq = deque()
    dq.append([tr, tc, 0])

    while dq:
        cr, cc, dist = dq.popleft()
        dist_board[cr][cc] = dist

        for d in range(4):
            nr = cr + dy[d]
            nc = cc + dx[d]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if board[nr][nc]:
                continue
            if dist_board[nr][nc] != -1:
                continue
            dq.append([nr, nc, dist + 1])

    # dist_board = [] 사용해서 거리 1씩 줄어드는 길 찾아 출력하기
    q.append([r, c, -1])
    dir = -1

    while q:
        cr, cc, dir = q.popleft()

        for d in range(1, 5):
            nr = cr + dy[(d % 4)]
            nc = cc + dx[(d % 4)]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if board[nr][nc]:
                continue
            if dist_board[cr][cc] - dist_board[nr][nc] != 1:
                continue
            q.append([nr, nc, d])
            print(nr, nc)

    if tr == -1 and tc == -1:
        return [-1, -1, -1]
    else:
        return [tr, tc, dir]

def solve():
    N, r, c, d = map(int, input().split())

    # 0 = sea, 1 = rock
    board = []
    for _ in range(N):
        board.append(list(map(int, input().split())))

    r = r - 1
    c = c - 1

    total = sum(row.count(0) for row in board)

    cnt = 0
    visited = [[False] * N for _ in range(N)]

    while cnt <= total:
        r, c, ncnt = explore(N, r, c, d, board, visited)
        cnt += ncnt

        r, c, d = move(board, N, r, c, visited)

solve()

'''
🐛 버그 1: visited 배열이 전혀 갱신되지 않음
explore() 안에서 visited[cr][cc] = True를 한 번도 하지 않아서, 고래가 이미 방문한 칸을 방문 가능한 칸으로 계속 인식합니다.

🐛 버그 2: 방향 cd가 이동 후 갱신되지 않음
python# explore() 내부 - cd가 초기값 고정
nr = cr + dy[cd]        # 직진
nr = cr + dy[(cd+1)%4]  # 좌회전
# ... cd는 절대 바뀌지 않음!
이동 후 반드시 cd를 이동 방향으로 갱신해야 합니다. 현재 코드는 매 반복마다 동일한 방향으로만 시도합니다.

🐛 Bug 3: explore()에 BFS 큐를 쓰면 안 됨
deque를 사용하면 방향 정보가 사라집니다. Phase 1은 BFS가 아니라 방향을 추적하며 한 칸씩 이동하는 시뮬레이션입니다.
python# 잘못된 구조
q = deque()
q.append([r, c])
while q:
    cr, cc = q.popleft()
    # cd는 어떤 방향이었지?? → 알 수 없음
올바른 구조:
python# 방향을 유지하며 한 칸씩 이동
while True:
    for nd in [cd, (cd+1)%4, (cd+3)%4, (cd+2)%4]:
        nr, nc = r+dy[nd], c+dx[nd]
        if 유효한 미방문 바다:
            r, c, cd = nr, nc, nd  # 방향도 갱신
            visited[r][c] = True
            moved = True
            break
    if not moved: break

🐛 Bug 4: move()의 경로 탐색이 BFS로 퍼져나감
pythonwhile q:
    cr, cc, dir = q.popleft()
    for d in range(1, 5):
        ...
        q.append([nr, nc, d])  # break 없이 모든 방향 추가!
        print(nr, nc)          # 여러 갈래 경로 전부 출력됨
break가 없어서 하나의 경로가 아닌 BFS 트리 전체를 출력합니다. 우선순위에 맞는 첫 번째 다음 칸 선택 후 즉시 break해야 합니다.

🐛 Bug 5: move()에서 q를 오염된 채로 재사용
목적지 BFS용 q를 경로 탐색에도 그대로 씁니다. 첫 번째 while 루프 이후 q가 비어 있다고 보장되더라도, 같은 변수를 두 용도로 쓰는 것은 매우 위험합니다.

🐛 Bug 6: move() 반환 방향 인코딩이 불일치
경로 탐색 루프의 d (1~4 순환, 좌하우상 의미)와 문제 방향 인코딩 (1=상,2=하,3=좌,4=우)이 다릅니다. 반환값 dir을 explore()에서 DIR[d]로 변환하려 할 때 잘못된 값이 됩니다.

✅ 수정 방향 요약
위치문제수정explore()visited 갱신 없음visited[cr][cc] = True 추가explore()cd 갱신 없음이동 후 cd = ndexplore()BFS 큐 구조while + break 순차 루프로 교체move()경로 탐색 break 없음첫 유효 칸 선택 후 breakmove()방향 반환 오류cd 인덱스(0~3) → 문제 인코딩(1~4) 변환
'''

import sys
from collections import deque
input = sys.stdin.readline

# 내부 방향: 0=상, 1=좌, 2=하, 3=우
dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]

# 문제 방향 → 내부 인덱스 변환
DIR = {1: 0, 2: 2, 3: 1, 4: 3}

def solve():
    N, r, c, d = map(int, input().split())
    board = []
    for _ in range(N):
        board.append(list(map(int, input().split())))

    r -= 1
    c -= 1
    cd = DIR[d]

    visited = [[False]*N for _ in range(N)]
    visited[r][c] = True
    print(r+1, c+1)

    total = sum(row.count(0) for row in board)
    count = 1

    while count < total:
        # ===== 1단계: 인접 탐험 =====
        # [버그 수정] BFS 큐 제거 → 방향을 추적하며 한 칸씩 이동하는 루프로 교체
        moved = True
        while moved:
            moved = False
            # 직진 → 좌회전(CCW, +1) → 우회전(CW, +3) → 180도(+2)
            for nd in [cd, (cd+1)%4, (cd+3)%4, (cd+2)%4]:
                nr, nc = r + dy[nd], c + dx[nd]
                if 0 <= nr < N and 0 <= nc < N and board[nr][nc] == 0 and not visited[nr][nc]:
                    # [버그 수정] 이동 후 방향(cd) 갱신
                    r, c, cd = nr, nc, nd
                    # [버그 수정] visited 갱신 추가
                    visited[r][c] = True
                    count += 1
                    print(r+1, c+1)
                    moved = True
                    break
            if count >= total:
                break

        if count >= total:
            break

        # ===== 2단계: 가장 가까운 바다로 이동 =====
        # [버그 수정] 방문한 칸만 통해 BFS (문제 조건: 이미 방문한 바다는 지나갈 수 있음)
        dist = [[-1]*N for _ in range(N)]
        dist[r][c] = 0
        q = deque([(r, c)])
        candidates = []
        min_dist = float('inf')

        while q:
            cr, cc = q.popleft()
            if dist[cr][cc] > min_dist:
                break
            for nd in range(4):
                nr, nc = cr + dy[nd], cc + dx[nd]
                if not (0 <= nr < N and 0 <= nc < N):
                    continue
                if board[nr][nc] == 1 or dist[nr][nc] != -1:
                    continue
                dist[nr][nc] = dist[cr][cc] + 1
                if not visited[nr][nc]:
                    # 미방문 칸 = 후보 (여기서 멈춤, 큐에 넣지 않음)
                    if dist[nr][nc] < min_dist:
                        min_dist = dist[nr][nc]
                        candidates = [(nr, nc)]
                    elif dist[nr][nc] == min_dist:
                        candidates.append((nr, nc))
                else:
                    # 방문한 칸만 BFS 확장
                    q.append((nr, nc))

        if not candidates:
            break

        # 행 번호 → 열 번호 순 정렬
        candidates.sort()
        tr, tc = candidates[0]

        # 목적지에서 역방향 BFS로 거리맵 생성 (방문한 칸만 통과)
        dist2 = [[-1]*N for _ in range(N)]
        dist2[tr][tc] = 0
        q = deque([(tr, tc)])

        while q:
            cr, cc = q.popleft()
            for nd in range(4):
                nr, nc = cr + dy[nd], cc + dx[nd]
                if not (0 <= nr < N and 0 <= nc < N):
                    continue
                if board[nr][nc] == 1 or dist2[nr][nc] != -1:
                    continue
                if visited[nr][nc]:  # 방문한 칸만 확장
                    dist2[nr][nc] = dist2[cr][cc] + 1
                    q.append((nr, nc))

        # [버그 수정] 경로 따라가기: 좌→하→우→상 우선순위, break 추가
        move_order = [1, 2, 3, 0]  # 좌, 하, 우, 상

        while r != tr or c != tc:
            for nd in move_order:
                nr, nc = r + dy[nd], c + dx[nd]
                if (0 <= nr < N and 0 <= nc < N
                        and board[nr][nc] == 0
                        and dist2[nr][nc] == dist2[r][c] - 1):
                    r, c, cd = nr, nc, nd
                    break  # [버그 수정] break 없어서 모든 경로 탐색하던 것 수정

        # 목적지만 새로 방문 처리 (중간 경로는 이미 방문한 칸)
        visited[r][c] = True
        count += 1
        print(r+1, c+1)

solve()






