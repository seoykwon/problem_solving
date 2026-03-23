from collections import deque


def solve():
    N = int(input())
    K = int(input())

    board = [[0] * N for _ in range(N)]
    for _ in range(K):
        r, c = map(int, input().split())
        board[r - 1][c - 1] = 1  # 사과

    L = int(input())
    turns = {}
    for _ in range(L):
        line = input().split()
        t, d = int(line[0]), line[1]
        turns[t] = d

    # 방향: 0=오른쪽, 1=아래, 2=왼쪽, 3=위
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]

    direction = 0
    snake = deque()
    snake.append((0, 0))
    board[0][0] = 2  # 뱀 위치 표시

    time = 0

    while True:
        time += 1

        hr, hc = snake[-1]
        nr, nc = hr + dr[direction], hc + dc[direction]

        # 벽 충돌
        if not (0 <= nr < N and 0 <= nc < N):
            break

        # 자기 몸 충돌
        if board[nr][nc] == 2:
            break

        # 머리 전진
        snake.append((nr, nc))

        if board[nr][nc] == 1:
            # 사과 있음 → 꼬리 유지
            board[nr][nc] = 2
        else:
            # 사과 없음 → 꼬리 제거
            board[nr][nc] = 2
            tr, tc = snake.popleft()
            board[tr][tc] = 0

        # 방향 전환 체크
        if time in turns:
            if turns[time] == 'D':
                direction = (direction + 1) % 4  # 오른쪽 회전
            else:
                direction = (direction - 1) % 4  # 왼쪽 회전

    print(time)


solve()