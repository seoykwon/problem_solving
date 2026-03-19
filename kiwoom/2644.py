import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

def bfs(start, des):
    queue = deque([(start, 0)])
    visited[start] = True

    while queue:
        cur, dist = queue.popleft()
        if cur == des:
            return dist

        for i in child[cur]:
            if visited[i]:
                continue

            queue.append((i, dist + 1))
            visited[i] = True

    return -1


n = int(input())
child = [[] for _ in range(n + 1)]
a, b = map(int, input().split())
m = int(input())
for i in range(m):
    x, y = map(int, input().split())
    child[x].append(y)
    child[y].append(x)

visited = [False] * (n + 1)

ans = bfs(a, b)

if ans == 0:
    print(-1)
else:
    print(ans)