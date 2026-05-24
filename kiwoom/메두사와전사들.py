import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

# 상하좌우 우선순위
DX = [0, 0, -1, 1]
DY = [-1, 1, 0, 0]

def medusa_move(N, M, mr, mc, pr, pc, bd):
    # backtracking graph로 미리 노선 그리기
    backtracking_graph = [[False for _ in range(N)] for _ in range(N)]
    backtracking_graph[mr][mc] = True

    q = deque()

    q.append([(mr, mc)])

    while q:
        cr, cc = q.popleft()

        for d in range(4):
            nr = cr + DY[d]
            nc = cc + DX[d]

            if nr < 0 or nr >= N or nc < 0 or nc >= N:
                continue
            if bd[nr][nc] == 1:
                continue
            if not backtracking_graph[nr][nc]:
                backtracking_graph[nr][nc] = (cr, cc)
                q.append((nr, nc))

    reversed_path = []
    reversed_path.append((pr, pc))
    cr, cc = pr, pc

    while True:
        if nr == mr and nc == mc:
            break

        nr, nc = backtracking_graph[cr][cc]

        reversed_path.append((nr, nc))

        cr, cc = nr, nc

    path = reversed_path[::-1]

    return path

def solve():
    N, M = map(int, input().split())
    mr, mc, pr, pc = map(int, input().split())

    wlst = list(map(int, input().split()))

    warriors = {}
    for i in range(0, M, 2):
        wr = wlst[i]
        wc = wlst[i + 1]
        warriors[(wr, wc)] += 1

    board = []
    for _ in range(N):
        board.append(list(map(int, input().split())))
    
    path = medusa_move(N, M, mr, mc, pr, pc, board)

solve()