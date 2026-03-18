import sys
# sys.stdin = open("input.txt", 'r')
input = sys.stdin.readline

from collections import deque

ans = 0

def bfs(cn, visited):
    global ans
    q = deque([(cn, 1)])
    visited[cn] = True

    while q:
        cur, cnt = q.popleft()


        for next in graph[cur]:
            if visited[next]:
                continue
            ans += 1
            visited[next] = True
            q.append((next, cnt + 1))

n = int(input())
pair = int(input())

graph = [[] for _ in range(n + 1)]

for i in range(pair):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

visited = [False] * (n + 1)

bfs(1, visited)

print(ans)