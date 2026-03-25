import sys
input = sys.stdin.readline

def check(board, N, H):
    for start in range(1, N + 1):
        pos = start
        for h in range(1, H + 1):
            if board[h][pos] == 1:
                pos += 1
            elif pos > 1 and board[h][pos - 1] == 1:
                pos -= 1
        if pos != start:
            return False
    return True

def backtrack(board, N, H, count, start_h, start_b):
    if count == 0:
        return check(board, N, H)
    
    for h in range(start_h, H + 1):
        b_start = start_b if h == start_h else 1
        for b in range(b_start, N):
            if board[h][b] == 0 and (b == 1 or board[h][b - 1] == 0) and (b == N - 1 or board[h][b + 1] == 0):
                board[h][b] = 1
                next_b = b + 2
                next_h = h if next_b < N else h + 1
                actual_next_b = next_b if next_b < N else 1
                if backtrack(board, N, H, count - 1, next_h, actual_next_b):
                    board[h][b] = 0
                    return True
                board[h][b] = 0
    return False
    
def solve():
    N, M, H = map(int, input().split())
    board = [[0] * (N + 1) for _ in range(H + 1)]

    for _ in range(M):
        a, b = map(int, input().split())
        board[a][b] = 1

    if check(board, N, H):
        print(0)
        return
    
    for cnt in range(1, 4):
        if backtrack(board, N, H, cnt, 1, 1):
            print(cnt)
            return
    print(-1)

solve()
