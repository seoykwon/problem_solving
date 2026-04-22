import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

import heapq

# 인자로 특정 박스 정보를 받으면 안 됨.
# 전역적으로 모든 보드에 중력이 일어나야 하기 때문임
def gravity(board):
    l = len(box)
    for li in range(l):
        k, h, w, c, r = box[li]
        if valid[k] == False:
            continue

        flag = True
        update_r = r
        for i in range(r + h, N):
            for j in range(c, c + w + 1):
                if board[i][j] != 0:
                    flag = False
                    break
            if flag:
                update_r += 1
        
        for i in range(r, h+1):
            for j in range(c, c+w+1):
                board[i][j] = 0
        
        for i in range(update_r, update_r+h+1):
            for j in range(c, c+w+1):
                board[i][j] = k
        
        box[li] = [k, h, w, c, update_r]
        spotbox[k] = [h, w, c, update_r]


def put_box(box1, board):
    k, h, w, c, _ = box1
    for i in range(h):
        for j in range(c, w+1):
            board[i][j] = k
    
    gravity(board)


def left_box(board):
    '''
    쌓인 택배 중에 잡고 왼쪽으로 이동했을 때 다른 택배와 부딪히지 않고 뺄 수 있는 택배를 먼저 하차
    그러한 택배가 여러개이면, 택배 번호(k)가 작은 택배를 먼저 하차
    '''
    cand = []
    for i in range(N):
        # i행의 가장 왼쪽에 있는 택배 k 찾기
        for j in range(N):
            if board[i][j] != 0:
                # 그 택배에 해당하는 아래 칸 왼쪽에 택배 없는지 확인
                tmp_k = board[i][j]
                h, w, c, r = spotbox[tmp_k]
                flag = True
                for i2 in range(i+1, i+h+1):
                    for j2 in range(c-1, -1, -1):
                        if board[i2][j2] != 0:
                            flag = False
                            break
                if flag:
                    heapq.heappush(cand, (tmp_k))
    
    if cand:
        k2 = heapq.heappop(cand)

        h, w, c, r = spotbox[k2]
        valid[k2] = False

        for i in range(r, r+h+1):
            for j in range(c, c+w+1):
                board[i][j] = 0
    
    cand.clear()

def right_box(board):
    cand = []

    for i in range(N):
        for j in range(N-1, -1, -1):
            if board[i][j] != 0:
                # 그 택배에 해당하는 아래칸 오른쪽에 다른 택배 없는지 확인
                tmp_k = board[i][j]
                h, w, c, r = spotbox[tmp_k]
                flag = True
                for i2 in range(i+1, i+r+1):
                    for j2 in range(N-1, c+w, -1):
                        if board[i2][j2] != 0:
                            flag = False
                            break
                if flag:
                    heapq.heappush(cand, tmp_k)
    
    if cand:
        k2 = heapq.heappop(cand)
        h, w, c, r = spotbox[k2]
        valid[k2] = False

        for i in range(r, r+h+1):
            for j in range(c, c+w+1):
                board[i][j] = 0

N, M = map(int, input().split())

board = [[0]*N for _ in range(N)]
box = []
spotbox = dict()
valid = []

for i in range(M):
    k, h, w, c = map(int, input().split())
    box.append([k, h, w, c, 0])
    spotbox[k] = [h, w, c, 0]
    valid[k] = True

    put_box(box[i], board)

    left_box(board)
    gravity(board)

    right_box(board)
    gravity(board)

'''
버그 수정
1. 출력 코드 없음
2. valid 초기화
3. 범위 인덱스 오류

주요 버그
1. valid = [] — 빈 리스트인데 valid[k] = True로 접근 → IndexError. 딕셔너리로 바꿔야 합니다.
2. put_box의 열 범위 — range(c, w+1)는 range(c, c+w)여야 합니다. 예를 들어 c=5, w=3이면 range(5, 4)가 되어 아무것도 채워지지 않아요.
3. gravity의 +1 오류들

range(c, c+w+1) → range(c, c+w)
range(r, h+1) → range(r, r+h) (이전 위치를 지울 때)
range(update_r, update_r+h+1) → range(update_r, update_r+h)

박스가 h행 w열을 차지하면 행은 r~r+h-1, 열은 c~c+w-1입니다. 모든 +1이 off-by-one이에요.
4. left_box/right_box의 충돌 검사 범위 — 박스의 실제 행 범위는 r부터 r+h-1인데, 코드는 i+1부터 i+h+1을 봅니다. i는 보드 스캔 중의 현재 행이고 박스의 r과 다를 수 있어요. spotbox에 저장된 r을 써야 합니다.
5. right_box의 i+r+1 — h여야 할 자리에 r이 들어갔습니다. 그리고 range(N-1, c+w, -1)은 c+w 열을 빠뜨려요.
6. 출력 누락 — 하차된 번호를 모으고 print하는 부분이 아예 없습니다.
7. 중력 순서 — 박스를 입력 순으로 떨어뜨리면, 아래 박스가 나중에 떨어질 때 위 박스가 이미 이전 자리에 있어 문제가 생길 수 있어요. "안정 상태가 될 때까지 반복" 방식이 안전합니다.
8. 반복 종료 조건 — 문제에서 "모두 하차할 때까지 2, 3 반복"이므로 M개 입력이 끝나도 남은 박스가 있으면 계속 하차해야 합니다.
'''


# --------------------
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