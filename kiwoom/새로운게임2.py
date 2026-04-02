import sys
input = sys.stdin.readline

def solve():
    N, K = map(int, input().split())

    board = []
    for i in range(N):
        board.append(list(map(int, input().split())))

    pieces = []
    for i in range(K):
        r, c, d = map(int, input().split())
        pieces.append([r-1, c-1, d])

    board_stack = [[[] for _ in range(N)] for _ in range(N)]
    for i in range(K):
        r, c, _ = pieces[i]
        board_stack[r][c].append(i+1)

    DR = {1: 0, 2: 0, 3: -1, 4: 1}
    DC = {1: 1, 2: -1, 3: 0, 4: 0}
    OPP = {1: 2, 2: 1, 3: 4, 4: 3}

    def in_bounds(r, c):
        return 0 <= r < N and 0 <= c < N

    for turn in range(1, 1001):
        for pid in range(1, K+1):
            r, c, d = pieces[pid-1]
            stack = board_stack[r][c]

            if pid not in stack:
                continue

            pos = stack.index(pid)
            moving = stack[pos:]

            nr, nc = r + DR[d], c + DC[d]

            if not in_bounds(nr, nc) or board[nr][nc] == 2:
                d = OPP[d]
                pieces[pid-1][2] = d
                nr, nc = r + DR[d], c + DC[d]
                if not in_bounds(nr, nc) or board[nr][nc] == 2:
                    continue

            color = board[nr][nc]

            board_stack[r][c] = stack[:pos]

            if color == 0:
                board_stack[nr][nc].extend(moving)
            else:
                board_stack[nr][nc].extend(moving[::-1])

            for p in moving:
                pieces[p-1][0] = nr
                pieces[p-1][1] = nc

            if len(board_stack[nr][nc]) >= 4:
                print(turn)
                return

    print(-1)

solve()