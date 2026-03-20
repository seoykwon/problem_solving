import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

def bfs():
    queue = deque([(S, 0)])
    visited[S] = True

    while queue:
        cur, cnt = queue.popleft()
        if cur == G:
            return cnt

        for nn in (U, -D):
            nu = cur + nn

            if nu > F or nu < 1:
                continue
            if visited[nu]:
                continue

            visited[nu] = True
            queue.append((nu, cnt + 1))

    return "use the stairs"

F, S, G, U, D = map(int, input().split())
visited = [False] * (F + 1)

print(bfs())