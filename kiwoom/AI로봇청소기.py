import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque
import heapq
import copy

# 상 좌 하 우
dx = [0, -1, 0, 1]
dy = [-1, 0, 1, 0]

shape = {
    3: [0, 2, 3],
    2: [1, 2, 3],
    1: [0, 1, 2],
    0: [0, 1, 3],
}

def bfs(row, col):
    queue = deque()
    INF = float('inf')
    visited = [[INF]*N for _ in range(N)]
    queue.append((row, col, 0))
    visited[row][col] = 0
    mind = INF
    candidate = []

    while queue:
        cr, cc, d = queue.popleft()

        if board[cr][cc] > 0 and mind >= d:
            # 먼지가 있는 칸임
            mind = d
            heapq.heappush(candidate, (cr, cc))

        for dir in range(4):
            nr = cr + dy[dir]
            nc = cc + dx[dir]

            if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc] != INF:
                continue
            if (nr, nc) in robots:
                continue
            if board[nr][nc] == -1:
                continue
            
            visited[nr][nc] = d + 1
            queue.append((nr, nc, d + 1))
    
    if not candidate:
        return None
    return heapq.heappop(candidate)

def move_vacuum():
    # for (r, c) in robots:
    #     bfs(r, c)
    # set을 순회하면서 원소를 지우고 추가하면 런타임에러가 생김. 크기가 같아도 해시 재배치 때문에 터짐.
    for i in range(len(robots_list)):
        r, c = robots_list[i]
        new_pos = bfs(r, c)
        if new_pos:
            robots.discard((r, c))
            robots.add(new_pos)
            robots_list[i] = new_pos

# def cleaning():
    # global board
    
    # # set은 순서가 없는데..
    # for (r, c) in robots:
    #     mx = 0
    #     cand = []

    #     for d in range(3, -1, -1):
    #         total = board[r][c]

    #         for sd in shape[d]:
    #             nr = r + dy[sd]
    #             nc = c + dx[sd]

    #             if nr < 0 or nc < 0 or nr >= N or nc >= N:
    #                 continue
    #             total += board[nr][nc]
        
    #         mx = max(mx, total)

    #     for d in range(3, -1, -1):
    #         total = board[r][c]
            
    #         for sd in shape[d]:
    #             nr = r + dy[sd]
    #             nc = c + dx[sd]

    #             if nr < 0 or nc < 0 or nr >= N or nc >= N or board[nr][nc] == -1:
    #                 continue
    #             total += board[nr][nc]
            
    #         if total == mx:
    #             cand.append(d)
    #             break
        
    #     board[r][c] = max(0, board[r][c] - 20)
    #     for sd in shape[cand[0]]:
    #         nr = r + dy[sd]
    #         nc = c + dx[sd]

    #         if nr < 0 or nc < 0 or nr >= N or nc >= N or board[nr][nc] == -1:
    #             continue
    #         board[nr][nc] = max(0, board[nr][nc] - 20)

    #     cand.clear()

def cleaning():
    global board

    for (r, c) in robots_list:
        best_dir = -1
        best_total = -1

        for d in range(4):   # 0=상, 1=좌, 2=하, 3=우
            total = min(20, board[r][c])   # 현재 칸도 cap 적용 (먼지 없으면 0이니 안전)

            for sd in shape[d]:
                nr = r + dy[sd]
                nc = c + dx[sd]
                if nr < 0 or nc < 0 or nr >= N or nc >= N:
                    continue
                if board[nr][nc] == -1:
                    continue
                total += min(20, board[nr][nc])

            # 우선순위: 우(3) > 하(2) > 좌(1) > 상(0)
            # range(4)로 순방향 돌면서 >= 로 갱신하면 나중에 나온(= 우선순위 높은) d가 이김
            if total >= best_total:
                best_total = total
                best_dir = d

        # 청소 실행
        board[r][c] = max(0, board[r][c] - 20)
        for sd in shape[best_dir]:
            nr = r + dy[sd]
            nc = c + dx[sd]
            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if board[nr][nc] == -1:
                continue
            board[nr][nc] = max(0, board[nr][nc] - 20)

def dusting():
    global board
    for i in range(N):
        for j in range(N):
            if board[i][j] > 0:
                board[i][j] += 5

def spread_dust():
    board2 = copy.deepcopy(board)

    for i in range(N):
        for j in range(N):
            if board[i][j] == 0:
                total = 0
                for d in range(4):
                    ni = i + dy[d]
                    nj = j + dx[d]

                    if ni < 0 or nj < 0 or ni >= N or nj >= N or board[ni][nj] == -1:
                        continue
                    if board[ni][nj] > 0:
                        total += board[ni][nj]
                
                board2[i][j] += (total // 10)

    for i in range(N):
        for j in range(N):
            if board2[i][j] > 0 and board[i][j] == 0:
                board[i][j] += board2[i][j]

def solve():
    for _ in range(L):
        # 1. 청소기 이동
        move_vacuum()

        # 2. cleaning
        cleaning()

        # 3. dusting
        dusting()

        # 4. spread_dust
        spread_dust()

        # 5. print
        print(sum(v for row in board for v in row if v > 0))

N, K, L = map(int, input().split())

# -1 = 물건
board = []
for _ in range(N):
    board.append(list(map(int, input().split())))

robots = set()
robots_list = []
# 청소기의 순서를 어떻게 관리하지? 딕셔너리?
for _ in range(K):
    r, c = map(int, input().split())
    robots.add((r-1, c-1))
    robots_list.append((r-1, c-1))

solve()

'''
내가 이 문제 풀면서 저지른 실수들
1: 조건문 반전
    BFS 방문 체크: if visited[nr][nc] == INF: continue -> != INF
    cleaning 장애물 체크: if board[nr][nc] != -1: continue -> == -1
    방문 상태를 나타내는 값/방문 여부의 참과 거짓을 헷갈린다
    continue 조건 쓸 때 이 조건이 참이면 건너뛴다

2. 변수 초기화 위치
    cleaning의 mx = 0을 로봇 루프 바깥에 둠
    2번째 로봇부터 오답 + IndexError
    이 변수의 생애주기는 어디서 어디까지? 주석 달기

3. 자료구조 선택 실수
    순서가 중요한 로봇을 set에 저장 -> 문제 요구사항 위반
    순회 중인 set을 수정 -> 런타임 에러

    자료구조 고르기 전에 체크:
        순서가 중요한가 -> list
        중복 막아야 하는가 -> set/dict
        키로 값 찾는가 -> dict
        순뢰 중에 수정할 것인가 -> 원본 유지, 사본 수정

4. 경계 검사 순서
    경계 검사는 항상 인덱싱 전에
    if board[ni][nj] == -1 or ni < 0 or ...:   # ❌ 인덱싱 먼저
    
    if ni < 0 or nj < 0 or ni >= N or nj >= N:
        continue
    if board[ni][nj] == -1:
        continue
        
5. 의미 값 충돌
    청소량 비교 시 board[nr][nc] 원본값 사용. 실제로 청소되는 양은 min(20, board[nr][nc])
    spread_dust에서 먼지 있던 칸까지 +=

6. 타이핑 실수
    int('inf') -> valueError. 
    float('inf')가 맞다

7. 같은 일 두 번 하지 않기
    best_dir, best_total = -1, -1
    for d in range(4):
        total = compute(d)
        if total >= best_total:   # >= 로 나중 방향 우선
            best_total, best_dir = total, d

메타 패턴
실수들을 가만히 보면 큰 줄기 세 개로 묶여요:

조건문을 말로 풀어 읽지 않음 (A, D) — "이 if가 참이면 무슨 일이 일어나는가?"를 한 번만 읊으면 대부분 걸러짐.
변수의 생애주기/의미를 정의 안 함 (B, E, G) — 처음에 "이게 뭐지"를 명확히 하면 반은 풀림.
자료구조를 "느낌"으로 고름 (C) — 요구사항 체크리스트로 고르기.

다음에 구현 문제 풀 때 5분 사전 설계가 왜 중요한지 여기서 나와요. 문제 읽자마자 코드 치는 대신:

칠 종이/메모장에 각 변수가 무엇을 의미하는지 한 줄씩 적기
각 함수의 입/출력과 부수효과 적기 (예: "bfs는 새 위치를 반환한다. robots는 건드리지 않는다")
자료구조 선택 이유 적기

이 세 가지만 하면 이 문제에서 만든 버그의 80%는 안 생겼을 거예요.
'''