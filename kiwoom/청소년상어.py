import copy
import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

board = [[] for _ in range(4)]

dx = [-1, -1, 0, 1, 1, 1, 0, -1]
dy = [0, -1, -1, -1, 0, 1, 1, 1]

for i in range(4):
    data = list(map(int, input().split()))
    fish = []
    for j in range(4):
        # 물고기 번호, 방향
        fish.append([data[2 * j], data[2 * j + 1] - 1])
    board[i] = fish

max_score = 0


def dfs(sx, sy, score, board):
    global max_score
    score += board[sx][sy][0]
    max_score = max(max_score, score)
    board[sx][sy][0] = 0

    # 물고기 움직임
    # 물고기 1번부터 16번까지 찾기
    for f in range(1, 17):
        f_x, f_y = -1, -1
        # board 뒤져서 찾기
        for x in range(4):
            for y in range(4):
                if board[x][y][0] == f:
                    f_x, f_y = x, y
                    break
        # 물고기 없으면 다음 물고기 찾기
        if f_x == -1 and f_y == -1:
            continue
        # 방향: 지금 물고기 방향
        f_d = board[f_x][f_y][1]
        # 방향에 맞춰서 물고기 자리 바꾸기, 바꿀 자리 없으면 다음 방향으로
        for i in range(8):
            nd = (f_d + i) % 8  # 처음엔 자기 방향으로 나옴
            nx = f_x + dx[nd]
            ny = f_y + dy[nd]
            # 물고기 이동할 수 있는 자리인지 체크
            if not (0 <= nx < 4 and 0 <= ny < 4) or (nx == sx and ny == sy):
                continue
            board[f_x][f_y][1] = nd  # 이동 가능한 방향을 찾은걸로 갱신
            # ㄹㅇ 자리 바꿈
            board[f_x][f_y], board[nx][ny] = board[nx][ny], board[f_x][f_y]
            break

    # 상어 먹음
    s_d = board[sx][sy][1] # 상어 방향
    # 최대 4번까지 현재 방향의 자리 탐색 가능
    for i in range(1, 5):
        nx = sx + dx[s_d] * i
        ny = sy + dy[s_d] * i
        # 이동 가능한 자리인지 체크한 뒤 dfs
        if (0 <= nx < 4 and 0 <= ny < 4) and board[nx][ny][0] > 0:
            dfs(nx, ny, score, copy.deepcopy(board))


dfs(0, 0, 0, board)
print(max_score)