import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

# 우 하 좌 상
dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]

def move_turtle(N, M, turtle, board, turtle_set, result, time):
    # 아이디가 작은 순서대로 모든 바다거북이 최단경로 탐색
    # 앞선 거북이의 이동 결과 즉시 다음 거북이 경로 탐색에 반영
    for m in range(M):
        # 만약 이미 탈출한 바다거북이면
        if turtle[m][0] == -1:
            continue
        # 만약 화석이 된 거북이면
        if turtle[m][0] == -2:
            continue

        cur_turtle_r = turtle[m][0]
        cur_turtle_c = turtle[m][1]

        queue = deque()
        visited = [[False]*N for _ in range(N)]
        queue.append((N-1, N-1, 0))

        while queue:
            cr, cc, dist = queue.popleft()
            visited[cr][cc] = True

            if cr == cur_turtle_r and cc == cur_turtle_c:
                # 최단경로 존재
                turtle_set.discard((cur_turtle_r, cur_turtle_c))
                nd = (d + 2) % 4
                r = cur_turtle_r + dy[nd]
                c = cur_turtle_c + dx[nd]
                turtle[m][0] = r
                turtle[m][1] = c
                # 도착했을 시
                if r == N - 1 and c == N - 1:
                    result[m] = time
                    turtle[m][0] = -1
                    break

                turtle_set.add((turtle[m][0], turtle[m][1]))
                break

            for d in range(3, -1, -1):
                nr = cr + dy[d]
                nc = cc + dx[d]

                if nr < 0 or nc < 0 or nr >= N or nc >= N or visited[nr][nc]:
                    continue
                if board[nr][nc] == 1:
                    continue
                # 다른 바다거북 존재시 못 감
                if turtle_set.union((nr, nc)):
                    continue


def solve():
    N, M, K = map(int, input())

    board = []
    for _ in range(N):
        board.append(list(map(int, input().split())))

    turtle = []
    turtle_set = set()
    for m in range(M):
        r, c = map(int, input().split())
        turtle.append([r, c])
        turtle_set.add([r, c])

    vocalno = []
    for k in range(K):
        r, c = map(int, input().split())
        vocalno.append((r, c))

    result = [0] * M

    for time in range(0, 101):

        # 1단계 바다거북 이동
        move_turtle(N, M, turtle, board, turtle_set, result, time)

solve()