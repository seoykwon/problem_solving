import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

def bfs():
    q = deque()

    # 익은 토마토 모두 큐에 넣기
    for h in range(H):
        for n in range(N):
            for m in range(M):
                if box[h][n][m] == 1:
                    q.append((h, n, m, 0))

    dirs = [
        (0, 0, 1), (0, 0, -1),
        (0, 1, 0), (0, -1, 0),
        (1, 0, 0), (-1, 0, 0)
    ]

    ans = 0
    while q:
        ch, cn, cm, cnt = q.popleft()
        ans = max(ans, cnt)

        for dh, dn, dm in dirs:
            nh, nn, nm = ch + dh, cn + dn, cm + dm

            if nh < 0 or nn < 0 or nm < 0 or nh >= H or nn >= N or nm >= M:
                continue
            if box[nh][nn][nm] != 0:
                continue

            box[nh][nn][nm] = 1
            q.append((nh, nn, nm, cnt + 1))

    for h in range(H):
        for n in range(N):
            for m in range(M):
                if box[h][n][m] == 0:
                    return -1
                
    return ans

M, N, H = map(int, input().split())
box = []

for h in range(H):
    layer = []
    for n in range(N):
        layer.append(list(map(int, input().split())))
    box.append(layer)

print(bfs())