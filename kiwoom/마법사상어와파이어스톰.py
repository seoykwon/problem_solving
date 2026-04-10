import sys
from collections import deque

input = sys.stdin.readline


# 얼음 덩어리 크기 측정 BFS
def bfs(start_x, start_y):
    global tmpSize
    tmpSize += 1  # 시작 칸 포함

    que = deque()
    que.append([start_x, start_y])
    visited[start_x][start_y] = True

    while que:
        x, y = que.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]

            if nx < 0 or nx >= s or ny < 0 or ny >= s:
                continue

            if arr[nx][ny] > 0 and not visited[nx][ny]:
                visited[nx][ny] = True
                que.append([nx, ny])
                tmpSize += 1  # 연결된 얼음 칸마다 +1


# (x, y)에서 시작하는 l×l 구간을 시계방향 90도 회전
def rotate(x, y, l):
    # 해당 구간만 잘라내기
    sub = [arr[i][y:y+l] for i in range(x, x+l)]

    # zip(*sub[::-1]) : 시계방향 90도 회전
    rotated = list(zip(*sub[::-1]))

    # 회전 결과를 원본 배열에 덮어쓰기
    for i in range(l):
        for j in range(l):
            arr[x+i][y+j] = rotated[i][j]


# 인접 얼음이 3개 미만인 칸의 얼음을 1 감소
def isNear():
    meltList = []  # 녹을 칸들을 먼저 모아두기 (동시처리를 위해)

    for i in range(s):
        for j in range(s):
            cnt = 0  # 인접한 얼음 수
            for k in range(4):
                nx = i + dx[k]
                ny = j + dy[k]

                if nx < 0 or nx >= s or ny < 0 or ny >= s:
                    continue

                if arr[nx][ny] > 0:
                    cnt += 1

            # 인접 얼음 3개 미만 + 현재 칸에 얼음 있으면 녹을 목록에 추가
            if cnt < 3:
                if arr[i][j] > 0:  # 음수 방지
                    meltList.append([i, j])

    # 모아둔 칸 한꺼번에 -1 (순회 중 바로 빼면 동시처리 불가)
    for x, y in meltList:
        arr[x][y] -= 1


# 입력
n, q = map(int, input().split())
s = 2 ** n  # 격자 크기

dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]  # 상우하좌

arr = [list(map(int, input().split())) for _ in range(s)]  # 얼음 격자
command = list(map(int, input().split()))                   # q개의 명령(L값)

# Step 1: 명령마다 회전 + 녹이기
for i in range(q):
    length = 2 ** (command[i])  # 회전할 구간 크기

    # L=0이면 1×1 구간 → 회전 의미없음, 녹이기만 수행
    if length == 1:
        isNear()
        continue

    # 격자를 length×length 단위로 나눠 각 구간 회전
    for j in range(0, s, length):
        for k in range(0, s, length):
            rotate(j, k, length)

    isNear()  # 모든 구간 회전 끝난 후 녹이기

# Step 2: 얼음 덩어리 탐색
visited = [[False] * s for _ in range(s)]

maxSize = []
for i in range(s):
    for j in range(s):
        # 방문 안 한 얼음 칸 발견 시 BFS로 덩어리 크기 측정
        if arr[i][j] > 0 and not visited[i][j]:
            tmpSize = 0
            bfs(i, j)
            maxSize.append(tmpSize)

# 출력
answer1 = 0
answer2 = 0

for x in arr:
    answer1 += sum(x)  # 남은 얼음 총합

if maxSize:
    answer2 = max(maxSize)  # 가장 큰 덩어리 크기

print(answer1)
print(answer2)