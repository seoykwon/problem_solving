import sys
input = sys.stdin.readline


def checkBlock(color):
    global score
    if color == "green":
        board = green_board
    else:
        board = blue_board
    idx = 5
    while idx >= 0:
        if sum(board[idx]) == 4:
            board.pop(idx)
            board.insert(0, [0] * 4)
            score += 1
        else:
            idx -= 1


def greenBlock(t, x):
    if t == 1:
        for g in range(1, 6):
            if green_board[g][x] != 0:
                green_board[g - 1][x] = 1
                break
            if g == 5:
                green_board[g][x] = 1
    elif t == 2:
        for g in range(1, 6):
            if green_board[g][x] != 0 or green_board[g][x + 1] != 0:
                green_board[g - 1][x] = 1
                green_board[g - 1][x + 1] = 1
                break
            if g == 5:
                green_board[g][x] = 1
                green_board[g][x + 1] = 1
    else:
        for g in range(1, 5):
            if green_board[g][x] != 0 or green_board[g + 1][x] != 0:
                green_board[g - 1][x] = 1
                green_board[g][x] = 1
                break
            if g == 4:
                green_board[g][x] = 1
                green_board[g + 1][x] = 1

    checkBlock("green")

    # if → while 로 수정: 특별 칸이 완전히 비워질 때까지 반복
    while sum(green_board[0]) != 0 or sum(green_board[1]) != 0:
        green_board.pop()
        green_board.insert(0, [0] * 4)


def blueBlock(t, y):
    if t == 1:
        for b in range(1, 6):
            if blue_board[b][y] != 0:
                blue_board[b - 1][y] = 1
                break
            if b == 5:
                blue_board[b][y] = 1
    elif t == 2:
        for b in range(1, 5):
            if blue_board[b][y] != 0 or blue_board[b + 1][y] != 0:
                blue_board[b - 1][y] = 1
                blue_board[b][y] = 1
                break
            if b == 4:
                blue_board[b][y] = 1
                blue_board[b + 1][y] = 1
    else:
        for b in range(1, 6):
            if blue_board[b][y] != 0 or blue_board[b][y + 1] != 0:
                blue_board[b - 1][y] = 1
                blue_board[b - 1][y + 1] = 1
                break
            if b == 5:
                blue_board[b][y] = 1
                blue_board[b][y + 1] = 1

    checkBlock("blue")

    # if → while 로 수정: 특별 칸이 완전히 비워질 때까지 반복
    while sum(blue_board[0]) != 0 or sum(blue_board[1]) != 0:
        blue_board.pop()
        blue_board.insert(0, [0] * 4)


green_board = [[0] * 4 for _ in range(6)]
blue_board = [[0] * 4 for _ in range(6)]
score = 0

N = int(input())
for _ in range(N):
    t, y, x = list(map(int, input().split()))
    greenBlock(t, x)
    blueBlock(t, y)

print(score)
left_block = 0
for b in range(6):
    left_block += sum(green_board[b])
    left_block += sum(blue_board[b])
print(left_block)