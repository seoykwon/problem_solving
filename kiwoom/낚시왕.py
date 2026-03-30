import sys
input = sys.stdin.readline

def solve():
    R, C, M = map(int, input().split())

    sharks = {}
    for _ in range(M):
        r, c, s, d, z = map(int, input().split())
        sharks[(r-1, c-1)] = (s, d, z) # 0-indexed

    def move(r, c, s, d):
        # 행(상/하) 이동
        if d == 1 or d == 2:
            N = R
            p = r
            going_positive = (d == 2)
        else:
            N = C
            p = c
            going_positive = (d == 3)

        if N == 1:
            return r, c, d
        
        period = 2 * (N - 1)
        steps = s % period

        # -방향이면 대칭 반전해서 +방향으로 통일
        if not going_positive:
            p = (N - 1) - p

        p = (p + steps) % period

        if p < N:
            forward = True
        else:
            p = period - p
            forward = False

        # 원래 -방향이었으면 다시 반전
        if not going_positive:
            forward = not forward
            p = (N - 1) - p

        if d == 1 or d == 2:
            r = p
            d = 2 if forward else 1
        else:
            c = p
            d = 3 if forward else 4

        return r, c, d
    
    total = 0

    for king_col in range(C):
        # 현재 열에서 가장 위 상어 잡기
        for r in range(R):
            if (r, king_col) in sharks:
                total += sharks[(r, king_col)][2]
                del sharks[(r, king_col)]
                break

        # 상어 이동 (O(1) 수식)
        new_sharks = {}
        for (r, c), (s, d, z) in sharks.items():
            nr, nc, nd = move(r, c, s, d)
            if (nr, nc) not in new_sharks or new_sharks[(nr, nc)][2] < z:
                new_sharks[(nr, nc)] = (s, nd, z)

        sharks = new_sharks

    print(total)

solve()