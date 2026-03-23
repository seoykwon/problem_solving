import sys
import copy
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

N = int(input())
board = [list(map(int, input().split())) for _ in range(N)]

def move(board, d):
    # 보드를 항상 왼쪽으로 미는 로직 하나로 처리하기 위해
    # 방향에 따라 보드를 회전시킨 뒤, 왼쪽으로 밀고, 다시 되돌림
    board = rotate(board, d)
    board = push_left(board)
    board = rotate(board, (4 - d) % 4)
    return board

def rotate(board, times):
    # 시계방향 90도 회전을 times번
    for _ in range(times):
        board = [list(row) for row in zip(*board[::-1])]
    return board

def push_left(board):
    new_board = []
    for row in board:
        # 0 제거
        tiles = [x for x in row if x != 0]
        merged = []
        skip = False
        for i in range(len(tiles)):
            if skip:
                skip = False
                continue
            if i + 1 < len(tiles) and tiles[i] == tiles[i+1]:
                merged.append(tiles[i] * 2)
                skip = True
            else:
                merged.append(tiles[i])
        # 0 채우기
        merged += [0] * (N - len(merged))
        new_board.append(merged)
    return new_board

ans = 0

def dfs(board, depth):
    global ans
    for row in board:
        ans = max(ans, max(row))
    if depth == 5:
        return
    for d in range(4):
        dfs(move([row[:] for row in board], d), depth + 1)

dfs(board, 0)
print(ans)