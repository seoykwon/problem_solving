import sys
from collections import deque
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

N, M = map(int, input().split())
board = [list(input().rstrip()) for _ in range(N)]

for i in range(N):
    for j in range(M):
        if board[i][j] == 'R':
            rr, rc = i, j
            board[i][j] = '.'
        elif board[i][j] == 'B':
            br, bc = i, j
            board[i][j] = '.'

def roll(r, c, dr, dc):
    while True:
        nr, nc = r + dr, c + dc
        if board[nr][nc] == '#':
            break
        r, c = nr, nc
        if board[r][c] == 'O':
            break
    return r, c, board[r][c] == 'O'

visited = set()
queue = deque()
start = (rr, rc, br, bc)
visited.add(start)
queue.append((start, 0))

ans = -1
directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

while queue:
    (rr, rc, br, bc), cnt = queue.popleft()

    if cnt >= 10:
        continue

    for dr, dc in directions:
        nrr, nrc, r_hole = roll(rr, rc, dr, dc)
        nbr, nbc, b_hole = roll(br, bc, dr, dc)

        if b_hole:
            continue
        if r_hole:
            ans = cnt + 1
            queue.clear()
            break

        if nrr == nbr and nrc == nbc:
            r_dist = abs(nrr - rr) + abs(nrc - rc)
            b_dist = abs(nbr - br) + abs(nbc - bc)
            if r_dist > b_dist:
                nrr -= dr
                nrc -= dc
            else:
                nbr -= dr
                nbc -= dc

        state = (nrr, nrc, nbr, nbc)
        if state not in visited:
            visited.add(state)
            queue.append((state, cnt + 1))

print(ans)