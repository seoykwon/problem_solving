from collections import deque
import sys
input = sys.stdin.readline

def dfs(graph, v, visited):
    visited[v] = True
    print(v, end=' ')
    for next_v in graph[v]:
        if not visited[next_v]:
            dfs(graph, next_v, visited)

