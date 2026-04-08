# N: 보드 크기, M: 택배 수
N, M = map(int, input().split())
# N×N 보드 생성 (0으로 초기화)
board = [[0 for _ in range(N)] for _ in range(N)]

def print_board(bd):
    for i in range(N):
        for j in range(N):
            print(board[i][j], end=" ")
        print()
    print()

# 택배를 중력에 의해 최대한 아래로 떨어뜨리는 함수
def drop_box(bd, bx):
    # k: 택배번호, h: 높이, w: 너비, c: 시작열, tmp_row: 현재 행
    k, h, w, c, tmp_row = bx

    drop_row = tmp_row  # 떨어질 수 있는 가장 낮은 행 (초기값: 현재 위치)
    can_drop = True
    # 택배 바로 아래 행부터 보드 끝까지 탐색
    for i in range(tmp_row+h, N):
        # 택배가 차지하는 열 범위 검사
        for j in range(c, c+w):
            if bd[i][j] != 0:   # 막히는 칸 발견
                can_drop = False
                break
        if can_drop:
            drop_row = i-h+1    # 떨어질 수 있는 가장 낮은 시작행 갱신
        else:
            break               # 막히면 더 내려갈 필요 없음

    # 원래 위치 지우기
    for i in range(tmp_row, tmp_row+h):
        for j in range(c, c+w):
            bd[i][j] = 0
    # 새 위치에 택배 번호 기록
    for i in range(drop_row, drop_row+h):
        for j in range(c, c+w):
            bd[i][j] = k

    # 수정된 보드와 박스 정보 반환 (drop_row로 행 위치 업데이트)
    return bd, [k, h, w, c, drop_row]

boxes = {}  # 택배 정보 저장 딕셔너리 {택배번호: [k, h, w, c, r]}
for i in range(M):
    k, h, w, c = map(int, input().split())
    box = [k, h, w, c-1, 0]    # c-1: 0-indexed 변환, 0: 시작행

    # 보드 위에서 택배 투입 후 중력 적용
    board, box = drop_box(board, box)

    boxes[k] = box  # 딕셔너리에 저장

# 왼쪽으로 꺼낼 수 있는 택배 후보를 찾는 함수
def left_candidate(bd, bxs):
    candidate = []  # 꺼낼 수 있는 택배 번호 목록

    i = 0
    while True:
        if i >= N:
            break
        for j in range(N):  # 왼쪽에서 오른쪽으로 탐색
            if bd[i][j] != 0:   # 행에서 가장 왼쪽 택배 발견
                k, h, w, c, r = bxs[bd[i][j]]
                possible = True
                # 택배 높이 범위의 모든 행 검사
                for m in range(h):
                    # j 왼쪽에 다른 택배가 있으면 꺼낼 수 없음
                    if i+m < N and any(bd[i+m][:j]):
                        possible = False
                if possible:
                    candidate.append(k)
                    i += (h-1)  # 이미 확인한 행은 건너뜀
                break           # 한 행에서 가장 왼쪽 택배 하나만 확인
        i += 1

    candidate.sort()    # 번호 오름차순 정렬

    if candidate:
        return candidate[0]     # 가장 작은 번호 반환
    return None

# 오른쪽으로 꺼낼 수 있는 택배 후보를 찾는 함수
def right_candidate(bd, bxs):
    candidate = []

    i = 0
    while True:
        if i >= N:
            break
        for j in range(N-1, -1, -1):   # 오른쪽에서 왼쪽으로 탐색
            if bd[i][j] != 0:   # 행에서 가장 오른쪽 택배 발견
                k, h, w, c, r = bxs[bd[i][j]]
                possible = True
                for m in range(h):
                    # j 오른쪽에 다른 택배가 있으면 꺼낼 수 없음
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

# 택배를 보드와 딕셔너리에서 제거하는 함수
def delete_candidate(bd, bxs, key):
    k, h, w, c, r = bxs[key]

    # 보드에서 해당 택배 칸 초기화
    for i in range(r, r+h):
        for j in range(c, c+w):
            bd[i][j] = 0

    bxs.pop(key)    # 딕셔너리에서 삭제

    return bd, bxs

# 모든 택배가 하차될 때까지 반복
while boxes:
    # 왼쪽 하차
    left = left_candidate(board, boxes)
    if left:
        print(left)
    board, boxes = delete_candidate(board, boxes, left)

    # 남은 택배들 중력 재적용
    for key in boxes.keys():
        board, box = drop_box(board, boxes[key])
        boxes[key] = box

    # 오른쪽 하차
    right = right_candidate(board, boxes)
    if right:
        print(right)

    board, boxes = delete_candidate(board, boxes, right)

    # 남은 택배들 중력 재적용
    for key in boxes.keys():
        board, box = drop_box(board, boxes[key])
        boxes[key] = box