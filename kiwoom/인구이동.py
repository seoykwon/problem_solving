from collections import deque

def solve():
    N, L, R = map(int, input().split())
    A = []
    for _ in range(N):
        A.append(list(map(int, input().split())))
    
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]
    
    days = 0
    
    while True:
        visited = [[-1] * N for _ in range(N)]
        unions = []
        uid = 0
        
        for i in range(N):
            for j in range(N):
                if visited[i][j] == -1:
                    q = deque()
                    q.append((i, j))
                    visited[i][j] = uid
                    members = [(i, j)]
                    
                    while q:
                        x, y = q.popleft()
                        for d in range(4):
                            nx, ny = x + dx[d], y + dy[d]
                            if 0 <= nx < N and 0 <= ny < N and visited[nx][ny] == -1:
                                diff = abs(A[x][y] - A[nx][ny])
                                if L <= diff <= R:
                                    visited[nx][ny] = uid
                                    q.append((nx, ny))
                                    members.append((nx, ny))
                    
                    unions.append(members)
                    uid += 1
        
        moved = False
        for members in unions:
            if len(members) > 1:
                moved = True
                total = sum(A[x][y] for x, y in members)
                avg = total // len(members)
                for x, y in members:
                    A[x][y] = avg
        
        if not moved:
            break
        days += 1
    
    print(days)

solve()