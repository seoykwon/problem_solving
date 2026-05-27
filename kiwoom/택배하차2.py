import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

N, M = map(int, input().split())
board = [[0 for _ in range(N)] for _ in range(N)]

def print_board(bd):
    for i in range(N):
        for j in range(N):
            print(board[i][j], end=" ")
        print()
    print()

def drop_box(bd, bx):
    k, h, w, c, tmp_row = bx

    drop_row = tmp_row
    can_drop = True

    for i in range(tmp_row+h, N):
        for j in range(c, c+w):
            if bd[i][j] != 0:
                can_drop = False
                break
        if can_drop:
            drop_row = i-h+1
        else:
            break

    for i in range(tmp_row, tmp_row+h):
        for j in range(c, c+w):
            bd[i][j] = k

    return bd, [k, h, w, c, drop_row]

boxes = {}
for i in range(M):
    k, h, w, c = map(int, input().split())
    box = [k, h, w, c-1, 0]

    board, box = drop_box(board, box)

    boxes[k] = box

def left_candidate(bd, bxs):
    candidate = []

    i = 0
    while True:
        if i >= N:
            break
        for j in range(N):
            if bd[i][j] != 0:
                k, h, w, c, r = bxs[bd[i][j]]
                possible = True

                for m in range(h):
                    if i+m < N and any(bd[i+m][:j]):
                        possible = False
                if possible:
                    candidate.append(k)
                    i += (h - 1)
                break
        i += 1

    candidate.sort()

    if candidate:
        return candidate[0]
    return None

def right_candidate(bd, bxs):
    candidate = []

    i = 0
    while True:
        if i >= N:
            break
        for j in range(N-1, -1, -1):
            if bd[i][j] != 0:
                k, h, w, c, r = bxs[bd[i][j]]
                possible = True

                for m in range(h):
                    if i+m < N and j+1 < N and any(bd[i+m][j+1:]):
                        possible = False
                    if possible:
                        candidate.append(k)
                        i += (h-1)
                    break
        i += 1

    candidate.sort()

    if candidate:
        return candidate[0]
    return None

def delete_candidate(bd, bxs, key):
    k, h, w, c, r = bxs[key]

    for i in range(r, r+h):
        for j in range(c, c+w):
            bd[i][j] = 0

    bxs.pop(key)

    return bd, bxs

while boxes:
    left = left_candidate(board, boxes)
    if left:
        print(left)
    board, boxes = delete_candidate(board, boxes, left)

    for key in boxes.keys():
        board, box = drop_box(board, boxes[key])
        boxes[key] = box

    right = right_candidate(board, boxes)
    if right:
        print(right)
    board, boxes = delete_candidate(board, boxes, right)

    for key in boxes.keys():
        board, box = drop_box(board, boxes[key])
        boxes[key] = box