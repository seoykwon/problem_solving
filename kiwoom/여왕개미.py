import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

import heapq

Q = int(input())
N = 0
cntNode = 0

pos = {}
rev_pos = {}
valid = {}
valid[0] = True # 여왕 개미
prev = {}
next = {}
distance = [] # heap

def reset_visited(dispatch):
    global visited

    visited = [False] * (N)

    for d, a in dispatch:
        visited[a] = True

for _ in range(Q):
    query = list(map(int, input().split()))
    op = query[0]

    if op == 100:
        # 마을 건설
        N = query[1]
        cntNode = N
        lst = query[2:]
        for i in range(N):
            x = lst[i]
            pos[i + 1] = x
            rev_pos[x] = i + 1
            valid[i + 1] = True

            if i > 0:
                prev[i + 1] = i
                dist = pos[i + 1] - pos[i]
                heapq.heappush(distance, (-(dist), i, i + 1))
            else:
                # i == 0, the very beginning
                prev[i + 1] = -1
                dist = pos[1]
                heapq.heappush(distance, (-(dist), 0, i+1))

        # next도 연결해주기
        for i in range(N, 1, -1):
            next[i - 1] = i

    if op == 200:
        # 개미집 건설
        p = query[1]
        cntNode += 1

        pos[N + 1] = p
        rev_pos[p] = N + 1
        valid[N + 1] = True
        next[N + 1] = -1
        idx = N
        while True:
            if valid[idx]:
                prev[N + 1] = idx
                next[idx] = N + 1 # next도 연결해주기
                dist = pos[N + 1] - pos[idx]
                heapq.heappush(distance, (-(dist), idx, N + 1))
                break
            idx -= 1
        N += 1

    if op == 300:
        # 개미집 철거
        q = query[1]
        cntNode -= 1

        valid[q] = False
        # 철거된 개미집이 맨 앞 (맨 왼쪽)
        if prev[q] == -1:
            nxt = next[q]
            prev[nxt] = -1

        # 철거된 개미집이 맨 뒤 (맨 오른쪽)
        elif next[q] == -1:
            pv = prev[q]
            next[pv] = -1

        # 철거된 개미집이 중간 위치
        else:
            a = prev[q]
            b = next[q]

            prev[b] = a
            next[a] = b

    if op == 400:
        # 개미집 정찰
        r = query[1]
        # 여왕 개미의 위치 = 0 도 선택할 수 있음
        visited = [False] * N
        # r 개밀들이 안전한 집으로 탐색한 집들 개수
        cnt = 0
        # heap에서 next 값과 valid 값을 체크하면 유효한 거리인지 알 수 있음
        dispatch = []
        tracker = 0
        while distance:
            antd, a, b = heapq.heappop(distance)
            if valid[a] == False:
                continue
            if next[a] != b:
                continue
            dispatch.append([antd, a])
            # visited[a] = True

            if tracker == r:
                break
        cnt += len(dispatch)

        lo = 0
        hi = pos[N]

        while lo < hi:
            reset_visited(dispatch)

            mid = (lo + hi) // 2 # 소요 시간
            # 어떻게 r 개미들을 적절한 위치에 배치해서 갯수를 세지? -> dispatch 사용
            for d, a in dispatch:
                for walk in range(1, mid):
                    if rev_pos[a + walk] and valid[rev_pos[a + walk]] and visited[rev_pos[a + walk]] == False:
                        visited[rev_pos[a + walk]] = True
                        cnt += 1

            if cnt < N:
                lo = mid + 1
            if cnt >= N:
                hi = mid

        print(hi)