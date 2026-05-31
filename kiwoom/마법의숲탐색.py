import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

# 북 동 남 서
EXIT = [(-1,0), (0, 1), (1, 0), (0, -1)]
# 남 서 동
DIR = [[(2, 0),(1, -1),(1, 1)], [(-1, -1),(0, -2),(1, -1)], [(-1, 1),(0, 2),(1, 1)]]

def mark(board, R, C, golems, id):
    _, _, r, c = golems[id]

    board[r][c] = id
    for d in range(4):
        nr, nc = r + EXIT[d][0], c + EXIT[d][1]

        if nr < 0 or nc < 0:
            break

        board[nr][nc] = id

def drop(id, board, R, C, K, golems):
    _, exit_d, r, c = golems[id]
    cr, cc = r, c
    while True:
        # 남쪽 이동
        flag = True
        for chk_r, chk_c in DIR[0]:
            if board[cr + chk_r][cc + chk_c] != 0:
                flag = False
        if flag:
            cr, cc = cr + EXIT[2][0], cc + EXIT[2][1]
            golems[id] = [id, exit_d, cr, cc]
        if not flag:
            break

    # 서쪽 이동
    flag = True
    for chk_r, chk_c in DIR[2]:
        if board[cr + chk_r][cc + chk_c] != 0:
            flag = False
    if flag:
        cr, cc = cr + EXIT[3][0], cc + EXIT[3][1]
        exit_d = (exit_d - 1) % 4
        golems[id] = [id, exit_d, cr, cc]

    while True:
        # 남쪽 이동
        flag = True
        for chk_r, chk_c in DIR[0]:
            if board[cr + chk_r][cc + chk_c] != 0:
                flag = False
        if flag:
            cr, cc = cr + EXIT[2][0], cc + EXIT[2][1]
            golems[id] = [id, exit_d, cr, cc]
        if not flag:
            break

    # 동쪽 이동
    flag = True
    for chk_r, chk_c in DIR[1]:
        if board[cr + chk_r][cc + chk_c] != 0:
            flag = False
    if flag:
        cr, cc = cr + EXIT[1][0], cc + EXIT[1][1]
        exit_d = (exit_d + 1) % 4
        golems[id] = [id, exit_d, cr, cc]

    while True:
        # 남쪽 이동
        flag = True
        for chk_r, chk_c in DIR[0]:
            if board[cr + chk_r][cc + chk_c] != 0:
                flag = False
        if flag:
            cr, cc = cr + EXIT[2][0], cc + EXIT[2][1]
            golems[id] = [id, exit_d, cr, cc]
        if not flag:
            break

    # 마킹
    mark(board, R, C, golems, id)

    # print(*board)

def solve():
    R, C, K = map(int, input().split())

    board = [[1]+[0]*C+[1] for _ in range(R + 4)]
    for c in range(C+2):
        board[R+3][c] = 1

    golems = {}
    for i in range(K):
        c, d = map(int, input().split())
        golems[i+2] = [i+2, d, 1, c]

    # 2부터 시작하는 골렘 아이디
    for id in golems.keys():
        drop(id, board, R, C, K, golems)

    print(*board)

solve()