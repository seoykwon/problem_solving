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

    # tmp_row에서 어디까지 낮아질 수 있는지 최대 tmp_row 체크
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

    # bd 값 이동
    for i in range(tmp_row, tmp_row+h):
        for j in range(c, c+w):
            bd[i][j] = 0
    for i in range(drop_row, drop_row+h):
        for j in range(c, c+w):
            bd[i][j] = k

    # bx 값 수정
    return bd, [k, h, w, c, drop_row]

boxes = {}
for i in range(M):
    k, h, w, c = map(int, input().split())
    box = [k, h, w, c-1, 0]

    # 1. 택배 투입
    board, box = drop_box(board, box) # 보드 위에서 떨어뜨리기

    boxes[k] = box # 딕셔너리에 저장

def left_candidate(bd, bxs):
    # 1 왼쪽으로 이동했을 때 다른 택배와 부딪히지 않고 뺄 수 있는 택배 먼저 하차
    # 2 여러개 이면, 작은 거 먼저 하차
    candidate = []

    i, j = 0, 0
    while True:
        if i >= N:
            break
        for j in range(N):
            if bd[i][j] != 0: # 행에서 가장 왼쪽 택배 발견
                k, h, w, c, r = bxs[bd[i][j]]
                possible = True
                for m in range(h): # 택배가 차지하는 모든 행 검사
                    if i+m < N and any(bd[i+m][:j]): # 왼쪽에 뭔가 있으면
                        possible = False
                        # print(f"{i+m}번째 행 체크: {bd[i+m][:j]}")
                    # elif i+m < N:
                        # print(f"{i+m}번째 행은 {bd[i+m]}")
                if possible:
                    candidate.append(k)
                    # print(f"{k} 추가함")
                    i += (h-1) # 택배 높이만큼 행 건너뛰기
                break
        i += 1

    candidate.sort()

    if candidate:
        return candidate[0]
    return None

def right_candidate(bd, bxs):
    # 1 오른쪽으로 이동했을 때 다른 택배와 부딪히지 않고 뺄 수 있는 택배 먼저 하차
    # 2 여러개이면, 작은 거 먼저 하차
    candidate = []

    i, j = 0, N-1
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

