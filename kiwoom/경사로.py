import sys
input = sys.stdin.readline

def can_pass(line, L):
    n = len(line)
    used = [False] * n
    
    for i in range(n - 1):
        diff = line[i+1] - line[i]
        
        if diff == 0:
            continue
        elif diff == 1:
            # 오르막: 왼쪽 L칸에 경사로
            start = i - L + 1
            if start < 0:
                return False
            for k in range(start, i + 1):
                if line[k] != line[i] or used[k]:
                    return False
            for k in range(start, i + 1):
                used[k] = True
        elif diff == -1:
            # 내리막: 오른쪽 L칸에 경사로
            end = i + L
            if end >= n:
                return False
            for k in range(i + 1, end + 1):
                if line[k] != line[i + 1] or used[k]:
                    return False
            for k in range(i + 1, end + 1):
                used[k] = True
        else:
            return False
    
    return True

N, L = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(N)]

count = 0
for i in range(N):
    if can_pass(grid[i], L):          # 행 검사
        count += 1
    col = [grid[r][i] for r in range(N)]
    if can_pass(col, L):              # 열 검사
        count += 1

print(count)