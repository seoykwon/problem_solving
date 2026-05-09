'''
0행렬
MxN 행렬의 한 원소가 0일 경우, 해당 원소가 속한 행과 열의 모든 원소를 0으로 설정하는 알고리즘을 작성하라
'''

# 풀이1 - Set 사용 O(M+N) 공간
def solve():
    M, N = map(int, input().split())
    board = [list(map(int, input().split())) for _ in range(M)]

    zero_rows = set()
    zero_cols = set()

    # 1단계: 0의 위치 기록
    for i in range(M):
        for j in range(N):
            if board[i][j] == 0:
                zero_rows.add(i)
                zero_cols.add(j)

    # 2단계: 해당 행/열 전부 0으로
    for i in range(M):
        for j in range(N):
            if i in zero_rows or j in zero_cols:
                board[i][j] = 0

    for row in board:
        print(row)

solve()

# 풀이2 - 첫 행/열을 마커로 사용 O(1) 공간
def solve():
    M, N = map(int, input().split())
    board = [list(map(int, input().split())) for _ in range(M)]

    # 첫 행/열 자체에 0이 있는지 먼저 체크
    first_row_zero = any(board[0][j] == 0 for j in range(N))
    first_col_zero = any(board[i][0] == 0 for i in range(M))

    # 첫 행/열을 마커로 활용
    for i in range(1, M):
        for j in range(1, N):
            if board[i][j] == 0:
                board[i][0] = 0 # 해당 행 마킹
                board[0][j] = 0 # 해당 열 마킹

    # 마커 보고 0으로 변경
    for i in range(1, M):
        for j in range(1, N):
            if board[i][0] == 0 or board[0][j] == 0:
                board[i][j] = 0

    # 첫 행/열 처리
    if first_row_zero:
        for j in range(N): board[0][j] = 0
    if first_col_zero:
        for i in range(M): board[i][0] = 0

    for row in board:
        print(row)

solve()