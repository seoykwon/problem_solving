import sys
import copy

input = sys.stdin.readline

M, S = map(int, input().split())

dx = [0, 0, -1, -1, -1, 0, 1, 1, 1]
dy = [0, -1, -1, 0, 1, 1, 1, 0, -1]

shark_dir = {0: (0, 0), 1: (-1, 0), 2: (0, -1), 3: (1, 0), 4: (0, 1)}

board = [[[] for _ in range(4 + 1)] for _ in range(4 + 1)]
smells = [[0] * 5 for _ in range(5)]

for i in range(M):
    fx, fy, d = map(int, input().split())
    board[fx][fy].append(d)

sx, sy = map(int, input().split())


def moveFishes(board):
    global smells
    newBoard = [[[] for _ in range(4 + 1)] for _ in range(4 + 1)]

    for i in range(1, 5):
        for j in range(1, 5):
            for fd in board[i][j]:
                nd = fd
                while True:
                    nx = i + dx[nd]
                    ny = j + dy[nd]
                    if nx < 1 or ny < 1 or nx >= 5 or ny >= 5:
                        nd = ((nd - 1) - 1) % 8 + 1
                        if nd == fd:
                            newBoard[i][j].append(fd)
                            break
                        continue
                    if smells[nx][ny] > 0:
                        nd = ((nd - 1) - 1) % 8 + 1
                        if nd == fd:
                            newBoard[i][j].append(fd)
                            break
                        continue
                    if sx == nx and sy == ny:
                        nd = ((nd - 1) - 1) % 8 + 1
                        if nd == fd:
                            newBoard[i][j].append(fd)
                            break
                        continue
                    newBoard[nx][ny].append(nd)
                    break

    return newBoard


def dfs(deep, x, y, method, sum, newBoard):
    global allMethods
    if deep == 3:
        allMethods.append((sum, method))
        return
    for i in range(1, 5):
        nx = x + shark_dir[i][0]
        ny = y + shark_dir[i][1]
        if nx < 1 or ny < 1 or nx >= 5 or ny >= 5:
            continue
        tmp = len(newBoard[nx][ny])
        tmpCopy = newBoard[nx][ny]
        newBoard[nx][ny] = []
        dfs(deep + 1, nx, ny, method + str(i), sum + tmp, newBoard)
        newBoard[nx][ny] = tmpCopy


def findMethods():
    global sx, sy
    x, y = sx, sy
    newBoard = copy.deepcopy(board)
    dfs(0, x, y, "", 0, newBoard)


for k in range(S):
    allMethods = []
    copy_board = copy.deepcopy(board)

    board = moveFishes(board)

    findMethods()

    allMethods.sort(key=lambda x: (-x[0], x[1]))
    thisMethod = allMethods[0][1]
    for d in thisMethod:
        nx = sx + shark_dir[int(d)][0]
        ny = sy + shark_dir[int(d)][1]
        if len(board[nx][ny]) > 0:
            smells[nx][ny] = 3
            board[nx][ny] = []
        sx, sy = nx, ny

    for i in range(1, 5):
        for j in range(1, 5):
            if smells[i][j] > 0:
                smells[i][j] -= 1

    for i in range(1, 5):
        for j in range(1, 5):
            board[i][j] += copy_board[i][j]

answer = 0
for i in range(1, 5):
    for j in range(1, 5):
        answer += len(board[i][j])
print(answer)