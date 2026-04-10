import sys

input = sys.stdin.readline
N = int(input())
graph = []

for i in range(N):
    tmp = list(map(int, input().split()))
    graph.append(tmp)

# x, y 에따라 가능한 d1, d2의 조합 모두 체크
case_list = []
for d1 in range(1, N):
    for d2 in range(1, N):
        for x in range(1, N - (d1 + d2) + 1):
            for y in range(1 + d1, N - d2 + 1):
                case_list.append([x - 1, y - 1, d1, d2])


def init_one():
    for i in range(x + d1):
        for j in range(N):

            if visited[i][j] == 1 or visited[i][j] == 5:
                break

            visited[i][j] = 1

    return


def init_two():
    for i in range(x + d2):
        for j in range(N - 1, -1, -1):

            if visited[i][j] == 1 or visited[i][j] == 5: break

            visited[i][j] = 2
    return


def init_three():
    for i in range(N - 1, x + d1, -1):
        for j in range(N):

            if visited[i][j] == 4 or visited[i][j] == 5: break

            visited[i][j] = 3

    return


def init_four():
    for i in range(N - 1, x + d2, -1):
        for j in range(N - 1, -1, -1):

            if visited[i][j] == 4 or visited[i][j] == 5: break

            visited[i][j] = 4
    return


def init_five():
    for i in range(N):
        for j in range(N):
            if visited[i][j] == 0:
                visited[i][j] = 5
    return


def check_sum():
    sum_list = [0, 0, 0, 0, 0]

    for i in range(N):
        for j in range(N):
            if visited[i][j] == 1:
                sum_list[0] += graph[i][j]

            if visited[i][j] == 2:
                sum_list[1] += graph[i][j]

            if visited[i][j] == 3:
                sum_list[2] += graph[i][j]

            if visited[i][j] == 4:
                sum_list[3] += graph[i][j]

            if visited[i][j] == 5:
                sum_list[4] += graph[i][j]

    return sum_list


answer = sys.maxsize
# 경계선 기준 상하 좌우로 쭉 1, 2, 3, 4 해놓고
for x, y, d1, d2 in case_list:
    visited = [[0 for _ in range(N)] for _ in range(N)]

    for i in range(d1 + 1):
        nx, ny = x + i, y - i
        if not (0 <= nx < N and 0 <= ny < N): continue

        visited[nx][ny] = 5

    for i in range(d2 + 1):
        nx, ny = x + i, y + i
        if not (0 <= nx < N and 0 <= ny < N): continue

        visited[nx][ny] = 5

    for i in range(d2 + 1):
        nx, ny = x + d1 + i, y - d1 + i
        if not (0 <= nx < N and 0 <= ny < N): continue

        visited[nx][ny] = 5

    for i in range(d1 + 1):
        nx, ny = x + d2 + i, y + d2 - i
        if not (0 <= nx < N and 0 <= ny < N): continue

        visited[nx][ny] = 5

    cnt = 1
    while True:
        nx, ny = x - cnt, y
        if not (0 <= nx < N and 0 <= ny < N): break

        visited[nx][ny] = 1

        cnt += 1

    cnt = 1
    while True:
        nx, ny = x + d2, y + d2 + cnt
        if not (0 <= nx < N and 0 <= ny < N): break

        visited[nx][ny] = 2
        cnt += 1

    cnt = -1
    while True:
        nx, ny = x + d1, y - d1 + cnt
        if not (0 <= nx < N and 0 <= ny < N): break

        visited[nx][ny] = 3
        cnt -= 1

    cnt = 1
    while True:
        nx, ny = x + d1 + d2 + cnt, y - d1 + d2
        if not (0 <= nx < N and 0 <= ny < N): break

        visited[nx][ny] = 4
        cnt += 1

    # 1은 왼쪽부터 쭉 오른쪽으로는 1, 5가 나올 때, 아래로는 3이 나올 때
    init_one()
    # 2는 오른쪽부터 쭉 왼쪽으로는 1, 5가 나올 때, 아래로는 2가 나올 때
    init_two()
    # 3은 왼쪽부터 쭉 오른쪽으로는 4, 5가 나올 때, 위로는 3이 나올 때
    init_three()
    # 4는 오른쪽부터 쭉 왼쪽으로는 4, 5가 나올 때 위로는 4가 나올 때
    init_four()
    # 0인 곳은 5로 채운다
    init_five()

    # 1, 2, 3, 4, 5의 sum을 체운다
    sum_list = check_sum()

    # 가장 많은 곳과 가장 적은 곳의 인구 차이의 최솟값을 구한다.
    diff = max(sum_list) - min(sum_list)

    answer = min(answer, diff)

print(answer)