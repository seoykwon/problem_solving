import sys
from collections import deque

input = sys.stdin.readline  # 빠른 입력을 위해 sys.stdin.readline 사용

# 방향 벡터 (북, 동, 남, 서)
dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

n, m, k = map(int, input().split())  # n: 행, m: 열, k: 이동 횟수
board = [list(map(int, input().split())) for _ in range(n)]  # n×m 보드 입력


def moveDice(state, pos, dir):
    # 현재 방향으로 이동할 다음 좌표 계산
    nx = pos[0] + dx[dir]
    ny = pos[1] + dy[dir]

    # 보드 밖으로 나가면 반대 방향(180도 반전)으로 이동
    if nx < 0 or ny < 0 or nx >= n or ny >= m:
        dir = (dir + 2) % 4
        nx = pos[0] + dx[dir]
        ny = pos[1] + dy[dir]

    if dir % 2 == 0:  # 북(0) 또는 남(2) 방향 이동
        if dir == 0:  # 북쪽 이동: 앞(북)에서 꺼내 뒤(남)에 추가
            state[0].append(state[0].popleft())
        else:         # 남쪽 이동: 뒤(남)에서 꺼내 앞(북)에 추가
            state[0].appendleft(state[0].pop())
        # 동서 축의 윗면(인덱스1)과 아랫면(인덱스3)을 북남 축과 동기화
        state[1][1], state[1][3] = state[0][1], state[0][3]
    else:             # 동(1) 또는 서(3) 방향 이동
        if dir == 3:  # 서쪽 이동: 앞(서)에서 꺼내 뒤(동)에 추가
            state[1].append(state[1].popleft())
        else:         # 동쪽 이동: 뒤(동)에서 꺼내 앞(서)에 추가
            state[1].appendleft(state[1].pop())
        # 북남 축의 윗면(인덱스1)과 아랫면(인덱스3)을 동서 축과 동기화
        state[0][1], state[0][3] = state[1][1], state[1][3]

    # 현재 위치 업데이트 후 새 좌표와 방향 반환
    pos[0], pos[1] = nx, ny
    return nx, ny, dir


def getC(x, y, B):
    # BFS로 (x,y)에서 연결된 보드값 B인 칸의 개수를 반환
    q = deque()
    q.append((x, y))
    cnt = 1  # 시작 칸 포함
    visited = [[False] * m for _ in range(n)]
    visited[x][y] = True

    while q:
        now = q.popleft()
        for i in range(4):  # 4방향 탐색
            nx = now[0] + dx[i]
            ny = now[1] + dy[i]
            if nx < 0 or ny < 0 or nx >= n or ny >= m:  # 보드 범위 초과
                continue
            if visited[nx][ny]:   # 이미 방문한 칸
                continue
            if board[nx][ny] != B:  # 값이 다른 칸
                continue
            cnt += 1
            q.append((nx, ny))
            visited[nx][ny] = True
    return cnt


# 주사위 초기 상태
# state[0]: 북남 축 deque → [북면, 윗면, 남면, 아랫면] = [2, 1, 5, 6]
# state[1]: 동서 축 deque → [서면, 윗면, 동면, 아랫면] = [4, 1, 3, 6]
diceState = [deque([2, 1, 5, 6]), deque([4, 1, 3, 6])]

dicePos = [0, 0]  # 주사위 초기 위치 (0행 0열)
diceDir = 1       # 초기 이동 방향: 동(1)
score = 0         # 누적 점수

while k > 0:
    # 주사위 이동 후 새 위치와 방향 갱신
    x, y, diceDir = moveDice(diceState, dicePos, diceDir)

    A = diceState[0][-1]   # 주사위 아랫면 값 (북남 축 deque의 마지막 원소)
    B = board[x][y]        # 현재 보드 칸의 값

    # 점수 += 보드값 × 연결된 같은 값 칸의 수
    score += B * getC(x, y, board[x][y])

    # 주사위 아랫면과 보드값 비교하여 다음 방향 결정
    if A > B:
        diceDir = (diceDir + 1) % 4   # 아랫면 > 보드값: 시계 방향(우회전)
    elif A < B:
        diceDir = (diceDir - 1) % 4   # 아랫면 < 보드값: 반시계 방향(좌회전)
    # A == B: 방향 유지

    k -= 1  # 남은 이동 횟수 감소

print(score)  # 최종 누적 점수 출력