"""

"""

"""
1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
2. 온도가 조절됨
3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
4. 초콜릿을 하나 먹는다.
5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
"""

from collections import deque
from copy import deepcopy

N, M, K = map(int, input().split()) #세로줄, 가로줄, 조사하는 칸의 온도 기준점
# 0:빈칸, 1:방향 오른쪽인 온풍기 2:방향 왼쪽인 온풍기, 3:방향 위인 온풍기, 4: 방향 아래인 온풍기, 5:온도 조사하는 칸
pan = [ list(map(int, input().split())) for _ in range(N) ] # 온풍기와 K정보
air = [ [0] * M for _ in range(N) ] # 온도 정보
W = int(input())
# 벽의 정보(x, y, t) -> t=0 (x,y)~(x-1,y)에 벽 / t=1 (x,y)~(x,y+1)에 벽
wall_hor = [ [False] * M for _ in range(N) ] # 벽의 가로
wall_ver = [ [False] * M for _ in range(N) ] # 벽의 세로

# [X, 동, 서, 북, 남]
dx = [0, 0, 0, -1, 1]
dy = [0, 1, -1, 0, 0]

# 벽 세우기(가로 정보 2차원 배열, 세로 정보 2차원 배열)
for _ in range(W):
    x, y, t = map(int, input().split())
    x, y = x-1, y-1
    if t == 0:
        wall_hor[x][y] = True
    elif t == 1:
        wall_ver[x][y] = True


# 벽 체크
def up_ok(i, j, k):
    if wall_hor[i][j] == True:
        return False
    if not (0 <= i+dx[k] < N and 0 <= j+dy[k] < M):
        return False
    return True

def left_ok(i, j, k):
    if (0 <= i+dx[k] < N and 0 <= j+dy[k] < M):
        if wall_ver[i+dx[k]][j+dy[k]] == False:
            return True
    return False

def down_ok(i, j, k):
    if (0 <= i+dx[k] < N and 0 <= j+dy[k] < M):
        if wall_hor[i+dx[k]][j+dy[k]] == False:
            return True
    return False

def right_ok(i, j, k):
    if wall_ver[i][j] == True:
        return False
    if not (0 <= i+dx[k] < N and 0 <= j+dy[k] < M):
        return False
    return True


def air_move():

    air_pos = [] # 온풍기의 위치(x, y, d)
    for i in range(N):
        for j in range(M):
            if 1 <= pan[i][j] <= 4:
                air_pos.append((i, j, pan[i][j]))

    # 온풍기가 2대 이상 있을 수도 있다. 이 경우 각각의 온풍기에 의해서 상승한 온도를 모두 합한 값이 해당 칸의 상승한 온도이다.
    for x, y, d in air_pos:

        tmp = [[0] * M for _ in range(N)]  # 새로운 배열을 만들어 온도 정보를 따로 저장
        x, y = x + dx[d], y + dy[d]
        tmp[x][y] = 5

        q = deque([(x, y, 5)])
        while q:
            px, py, tem = q.popleft()

            if tem == 0:
                break

            if d == 1: # 동쪽이면 북동, 동, 남동으로 뻗침
                if up_ok(px, py, 3):
                    if right_ok(px-1, py, 1):
                        q.append((px-1, py+1, tem-1))
                        tmp[px-1][py+1] = tem-1
                if right_ok(px, py, 1):
                    q.append((px, py+1, tem-1))
                    tmp[px][py+1] = tem-1
                if down_ok(px, py, 4):
                    if right_ok(px+1, py, 1):
                        q.append((px+1, py+1, tem-1))
                        tmp[px+1][py+1] = tem-1

            elif d == 2: # 서쪽이면 북서, 서, 남서로 뻗침
                if up_ok(px, py, 3):
                    if left_ok(px-1, py, 2):
                        q.append((px-1, py-1, tem-1))
                        tmp[px-1][py-1] = tem-1
                if left_ok(px, py, 2):
                    q.append((px, py-1, tem-1))
                    tmp[px][py-1] = tem-1
                if down_ok(px, py, 4):
                    if left_ok(px+1, py, 2):
                        q.append((px+1, py-1, tem-1))
                        tmp[px+1][py-1] = tem-1

            elif d == 3: # 북쪽이면 북서, 북, 북동으로 뻗침
                if left_ok(px, py, 2):
                    if up_ok(px, py-1, 3):
                        q.append((px-1, py-1, tem-1))
                        tmp[px-1][py-1] = tem-1
                if up_ok(px, py, 3):
                    q.append((px-1, py, tem-1))
                    tmp[px-1][py] = tem-1
                if right_ok(px, py, 1):
                    if up_ok(px, py+1, 3):
                        q.append((px-1, py+1, tem-1))
                        tmp[px-1][py+1] = tem-1

            elif d == 4: # 남쪽이면 남서, 남, 남동으로 뻗침
                if left_ok(px, py, 2):
                    if down_ok(px, py-1, 4):
                        q.append((px+1, py-1, tem-1))
                        tmp[px+1][py-1] = tem-1
                if down_ok(px, py, 4):
                    q.append((px+1, py, tem-1))
                    tmp[px+1][py] = tem-1
                if right_ok(px, py, 1):
                    if down_ok(px, py+1, 4):
                        q.append((px+1, py+1, tem-1))
                        tmp[px+1][py+1] = tem-1

        for i in range(N):
            for j in range(M):
                air[i][j] += tmp[i][j]



def tem_adjust():

    tmp = deepcopy(air)

    for i in range(N):
        for j in range(M):
            if right_ok(i, j, 1): # 동쪽
                mx = i + dx[1]
                my = j + dy[1]
                tem_dif = abs(air[i][j] - air[mx][my]) // 4

                if air[i][j] > air[mx][my]:
                    tmp[i][j] -= tem_dif
                elif air[i][j] < air[mx][my]:
                    tmp[i][j] += tem_dif

            if left_ok(i, j, 2): # 서쪽
                mx = i + dx[2]
                my = j + dy[2]
                tem_dif = abs(air[i][j] - air[mx][my]) // 4

                if air[i][j] > air[mx][my]:
                    tmp[i][j] -= tem_dif
                elif air[i][j] < air[mx][my]:
                    tmp[i][j] += tem_dif

            if up_ok(i, j, 3): # 북쪽
                mx = i + dx[3]
                my = j + dy[3]
                tem_dif = abs(air[i][j] - air[mx][my]) // 4

                if air[i][j] > air[mx][my]:
                    tmp[i][j] -= tem_dif
                elif air[i][j] < air[mx][my]:
                    tmp[i][j] += tem_dif

            if down_ok(i, j, 4): # 남쪽
                mx = i + dx[4]
                my = j + dy[4]
                tem_dif = abs(air[i][j] - air[mx][my]) // 4

                if air[i][j] > air[mx][my]:
                    tmp[i][j] -= tem_dif
                elif air[i][j] < air[mx][my]:
                    tmp[i][j] += tem_dif

    return tmp


def tem_down():

    # 4방향을 돌렸을 때 한번이라도 범위를 벗어난다면 그것은 테두리의 있는 좌표임.
    for i in range(N):
        for j in range(M):
            cnt = 0 # 범위를 벗어나는 개수
            for k in range(1, 4+1):
                mx = i + dx[k]
                my = j + dy[k]

                if not (0 <= mx < N and 0 <= my < M):
                    cnt += 1

            if cnt != 0:
                if air[i][j] > 0:
                    air[i][j] -= 1


def tem_search():

    for i in range(N):
        for j in range(M):
            if pan[i][j] == 5:
                if air[i][j] < K:
                    return False

    return True


chocolate = 0
while True:

    # 1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
    air_move()

    # for i in air:
    #     print(i)
    # print()

    # 2. 온도 조절
    air = tem_adjust()

    # for i in air:
    #     print(i)
    # print()

    # 3. 온도가 1이상인 가장 바깥쪽의 온도 1 감소
    tem_down()

    # for i in air:
    #     print(i)
    # print()

    # 4. 초콜릿 1 증가
    chocolate += 1

    # 5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
    if tem_search():
        break

    # ★ 이거 안해주면 계속 검사하기 때문에 시간초과 나온다 ★
    if chocolate > 100:
        chocolate = 101
        break


# 만약, 먹는 초콜릿의 개수가 100을 넘어가면 101을 출력
print(chocolate)

# 이렇게 하지말고, 반복문 내에서 체크해야 시간초과 안뜸
# print(101 if chocolate > 100 else chocolate)
