# 어른 상어
import copy
import sys
input = sys.stdin.readline

#  N: 격자크기, M: 상어 수, k: 냄새 지속 시간
N, M, k = map(int, input().split())
# arr: 현재 격자 상태 (각 칸에 어떤 상어가 있는지)
# shark: 각 상어의 정보 [번호, x, y, 방향]
# history: 각 칸의 남은 냄새 시간
# history_index: 냄새가 있는 칸의 좌표 목록
arr = []
shark = []
history = [[0] * N for _ in range(N)]
history_index = []

for i in range(N):
    arr.append(list(map(int, input().split())))
    for j in range(N):
        if arr[i][j] != 0:          # 상어가 있는 칸이라면
            history[i][j] = k       # 냄새 시간을 k로 초기화
            history_index.append((i, j))
            shark.append([arr[i][j], i, j]) # [번호, x, y] 저장

shark_dir = [0]+list(map(int, input().split()))
for i in range(len(shark)): # 각 상어 정보에 방향 추가 -> [번호, x, y, 방향]
    shark[i].append(shark_dir[arr[shark[i][1]][shark[i][2]]])

dx = [0, -1, 1, 0, 0]
dy = [0, 0, 0, -1, 1]

# 각 상어별로, 각 방향(1~4)에서의 이동 우선순위 저장
# shark_move_priority[상어번호][현재방향] = 시도할 방향 순서 리스트
shark_move_priority = [[]]
for _ in range(M):
    temp = [[]]
    for _ in range(4):
        temp.append(list(map(int, input().split())))
    shark_move_priority.append(temp)


def move_shark(temp):
    global M
    for i in range(len(shark)):
        # 쫒겨난 상어는 continue
        if shark[i] == [0, 0, 0, 0]:
            continue
        shark_num, x, y, dir = shark[i]
        isMoved = False
        # 빈공간으로 이동
        for ndir in shark_move_priority[shark_num][dir]:
            nx = x + dx[ndir]
            ny = y + dy[ndir]
            if 0 <= nx < N and 0 <= ny < N:
                if temp[nx][ny] == 0: # 냄새 없는 빈 칸이면
                    # 해당 공간에 다른 상어가 있다면
                    if arr[nx][ny] != 0:
                        M -= 1
                        # 두 상어의 크기를 비교해서 현재 상어가 더 쎄다면
                        if fight_shark(nx, ny, x, y):
                            for j in range(len(shark)):
                                num, _, _, _ = shark[j]
                                if num == arr[nx][ny]:
                                    shark[j] = [0, 0, 0, 0]
                                    break
                            arr[nx][ny] = shark_num
                            shark[i] = [shark_num, nx, ny, ndir]
                            update_history(nx, ny)
                            isMoved = True
                            break
                        # 현재 상어가 더 약하다면
                        else:
                            shark[i] = [0, 0, 0, 0]
                            isMoved = True
                            break
                    # 혼자만 해당 공간으로 이동했다면
                    else:
                        arr[nx][ny] = shark_num
                        shark[i] = [shark_num, nx, ny, ndir]
                        update_history(nx, ny)
                        isMoved = True
                        break
        # 빈공간이 없어서 이동을 못한 경우, 자기 채취가 있는 곳으로 이동
        if not isMoved:
            for ndir in shark_move_priority[shark_num][dir]:
                nx = x + dx[ndir]
                ny = y + dy[ndir]
                if 0 <= nx < N and 0 <= ny < N:
                    if temp[nx][ny] == shark_num:
                        arr[nx][ny] = shark_num
                        shark[i] = [shark_num, nx, ny, ndir]
                        update_history(nx, ny)
                        break


def fight_shark(x, y, a, b):
    if arr[x][y] > arr[a][b]:
        return True
    else:
        return False


def update_history(x, y):
    if (x, y) in history_index:
        history[x][y] = k+1
    else:
        history_index.append((x, y))
        history[x][y] = k+1


move = 0
while M != 1:
    if move > 1000:
        break
    # 이동
    temp = copy.deepcopy(arr)
    move_shark(temp)
    # 채취 지우기
    for i, j in history_index:
        if history[i][j] == 0:
            continue
        history[i][j] -= 1
        if history[i][j] == 0:
            arr[i][j] = 0
    move += 1
print(-1 if move > 1000 else move)