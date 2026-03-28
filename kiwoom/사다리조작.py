import sys
input = sys.stdin.readline

def solve():
    N, M, H = map(int, input().split())

    grid = [[0]*N for _ in range(H)]
    for _ in range(M):
        a, b = map(int, input().split())
        grid[a-1][b-1] = 1

    ID = tuple(range(N))

    def compose(p, q):
        # 순열 합성: p 적용 후 q 적용
        return tuple(q[x] for x in p)

    def inv_perm(p):
        # 역순열 계산
        res = [0]*N
        for i, v in enumerate(p): res[v] = i
        return tuple(res)

    def make_step(h, extras=()):
        # h번 행의 순열 계산 (extras: 추가로 놓을 가로선 열 번호들)
        row = list(grid[h])
        for b in extras: row[b] = 1
        step = list(range(N))
        b = 0
        while b < N-1:
            if row[b]: step[b] = b+1; step[b+1] = b; b += 2
            else: b += 1
        return tuple(step)

    steps = [make_step(h) for h in range(H)]

    # seg[a][b] = a번 행부터 b-1번 행까지 적용한 순열
    seg = [[ID]*(H+1) for _ in range(H+1)]
    for a in range(H+1):
        for b in range(a, H):
            seg[a][b+1] = compose(seg[a][b], steps[b])

    # 이미 정답인 경우
    if seg[0][H] == ID:
        print(0); return

    # 후보 위치: (행, 열, 해당 행 순열) - 행, 열 순으로 정렬됨
    cands = []
    for h in range(H):
        for b in range(N-1):
            if not grid[h][b]:
                if (b == 0 or not grid[h][b-1]) and (b == N-2 or not grid[h][b+1]):
                    cands.append((h, b, make_step(h, (b,))))
    L = len(cands)

    # lefts[i]  = seg[0][hi] ∘ ns_i  : 0행~hi행까지 가로선 i 포함한 순열
    # rights[i] = ns_i ∘ seg[hi+1][H]: hi행~끝까지 가로선 i 포함한 순열
    lefts  = [compose(seg[0][h], ns) for h, b, ns in cands]
    rights = [compose(ns, seg[h+1][H]) for h, b, ns in cands]

    # full_perm[i]: 가로선 i 하나만 추가했을 때의 전체 순열
    full_perm = [compose(lefts[i], seg[cands[i][0]+1][H]) for i in range(L)]

    # ── 1개 추가 ──────────────────────────────────────────────
    for i in range(L):
        if full_perm[i] == ID:
            print(1); return

    # ── 2개 추가 ──────────────────────────────────────────────
    for i in range(L):
        hi, bi, _ = cands[i]
        for j in range(i+1, L):
            hj, bj, nsj = cands[j]
            if hj == hi:
                # 같은 행: 두 가로선 동시 적용
                if abs(bi-bj) == 1: continue
                full = compose(compose(seg[0][hi], make_step(hi,(bi,bj))), seg[hi+1][H])
            else:
                # 다른 행 (hi < hj): lefts[i] ∘ seg[hi+1][hj] ∘ rights[j]
                full = compose(lefts[i], compose(seg[hi+1][hj], rights[j]))
            if full == ID:
                print(2); return

    # ── 3개 추가를 위한 사전 계산 ──────────────────────────────
    # left_to[i][h]  = 0행~h-1행까지 가로선 i 포함한 순열  (hi < h 일 때)
    # right_from[k][h] = h행~끝까지 가로선 k 포함한 순열   (h <= hk+1 일 때)
    left_to    = [[None]*(H+2) for _ in range(L)]
    right_from = [[None]*(H+2) for _ in range(L)]

    for i in range(L):
        hi = cands[i][0]
        for h in range(hi+1, H+1):
            left_to[i][h] = compose(lefts[i], seg[hi+1][h])

    for k in range(L):
        hk = cands[k][0]
        for h in range(0, hk+2):
            right_from[k][h] = compose(seg[h][hk], rights[k])

    # ── 3개 추가, Case 1: 3개 모두 다른 행 → O(L²) 딕셔너리 방식 ──
    # j를 중간 행으로 고정:
    #   left_dict[perm] = i  (hi < hj인 모든 i에 대해 left_to[i][hj] → i)
    #   각 k (hk > hj): rhs = ns_j ∘ right_from[k][hj+1]
    #   compose(left_to[i][hj], rhs) == ID  ↔  left_to[i][hj] == inv(rhs)
    for j in range(L):
        hj, bj, nsj = cands[j]
        left_dict = {}
        for i in range(L):
            if cands[i][0] < hj:
                left_dict[left_to[i][hj]] = i      # hi < hj인 i의 상태 저장
        if not left_dict: continue
        for k in range(L):
            hk = cands[k][0]
            if hk <= hj: continue
            rhs = compose(nsj, right_from[k][hj+1])
            if inv_perm(rhs) in left_dict:
                print(3); return

    # ── 3개 추가, Case 2: 정확히 2개가 같은 행, 1개는 다른 행 ──
    for i in range(L):
        hi, bi, _ = cands[i]
        for j in range(i+1, L):
            hj, bj, _ = cands[j]
            if hj != hi: break              # 정렬되어 있으므로 더 이상 같은 행 없음
            if abs(bi-bj) == 1: continue   # 인접 충돌
            combined = make_step(hi, (bi, bj))
            left_ij  = compose(seg[0][hi], combined)       # 0행~hi행 (쌍 포함)
            right_ij = compose(combined, seg[hi+1][H])     # hi행~끝 (쌍 포함)
            for k in range(L):
                hk = cands[k][0]
                if hk == hi: continue       # 같은 행 건너뜀
                if hk > hi:
                    # left_ij ∘ right_from[k][hi+1]
                    full = compose(left_ij, right_from[k][hi+1])
                else:
                    # left_to[k][hi] ∘ right_ij
                    full = compose(left_to[k][hi], right_ij)
                if full == ID:
                    print(3); return

    # ── 3개 추가, Case 3: 3개 모두 같은 행 ──
    for h in range(H):
        rbs = [b for hh, b, _ in cands if hh == h]
        for ii in range(len(rbs)):
            for jj in range(ii+1, len(rbs)):
                if abs(rbs[ii]-rbs[jj]) == 1: continue
                for kk in range(jj+1, len(rbs)):
                    if abs(rbs[ii]-rbs[kk])==1 or abs(rbs[jj]-rbs[kk])==1: continue
                    full = compose(compose(seg[0][h],
                                   make_step(h,(rbs[ii],rbs[jj],rbs[kk]))),
                                   seg[h+1][H])
                    if full == ID:
                        print(3); return

    print(-1)

solve()