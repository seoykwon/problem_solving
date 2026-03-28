import sys
input = sys.stdin.readline

def solve():
    N = int(input())

    visited = [[False]*101 for _ in range(101)]

    dx = [1, 0, -1, 0]
    dy = [0, -1, 0, 1]

    for _ in range(N):
        x, y, d, g = map(int, input().split())

        dirs = [d]
        for _ in range(g):
            dirs = dirs + [(dd + 1) % 4 for dd in reversed(dirs)]

        visited[y][x] = True
        cx, cy = x, y
        for direction in dirs:
            cx += dx[direction]
            cy += dy[direction]
            visited[cy][cx] = True

    ans = 0
    for y in range(100):
        for x in range(100):
            if (visited[y][x] and visited[y][x+1] and visited[y+1][x] and visited[y+1][x+1]):
                ans += 1
    print(ans)

solve()