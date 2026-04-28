import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

def bfs(i, r, c, turtle, N):
    q = deque()
    visited = [[0] * N for _ in range(N)]
    q.append([r, c, -1])
    res = -1

    while q:
        cr, cc, d = q.popleft()
        visited[cr][cc] = True

        if cr == N - 1 and cc == N - 1:
            res = d

        for dir in range(4):
            nr = cr + dy[dir]
            nc = cc + dx[dir]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            # 산호초, 다른 바다거북, 화석
            if board[nr][nc] == 1 or (nr, nc) in turtle_pos or board[nr][nc] == -2:
                continue

            visited[nr][nc] = True
            if d == -1:
                q.append([nr, nc, dir])
                continue
            q.append([nr, nc, d])
    return res

def move_turtle(board, turtle, turtle_pos, N, time):
    to_delete = []
    for i, (r, c) in turtle.items():
        dir = bfs(i, r, c, turtle, N)

        if dir == -1:
            continue
        nr = r + dy[dir]
        nc = c + dx[dir]

        if nr == N - 1 and nc == N - 1:
            result[i-1] = time
            to_delete.append(i)
            del turtle_pos[(r, c)]
            continue

        turtle[i] = [nr, nc]
        del turtle_pos[(r, c)]
        turtle_pos[(nr, nc)] = i

    for elem in to_delete:
        del turtle[elem]
        # del turtle_pos[(N-1, N-1)]

def inc_vol(volcano):
    for key in volcano:
        volcano[key] += 10

def erupt_vol(volcano, vol_mx, board, turtle, turtle_pos, N):
    # 1. 열기 전파
    heat = [[0]*N for _ in range(N)]
    erupted = deque()
    next_erupt = deque()

    for (r, c), val in volcano.items():
        p = vol_mx[(r, c)]
        if val >= p:
            erupted.append((r, c))
            heat[r][c] += p
            for d in range(4):
                cur = p
                for dist in range(1, N):
                    cur = cur // 2
                    if cur <= 0:
                        break
                    nr = r + dy[d] * dist
                    nc = c + dx[d] * dist

                    if nr < 0 or nc < 0 or nr >= N or nc >= N:
                        continue
                    if board[nr][nc] == 1:
                        break

                    if (nr, nc) in volcano:
                        # 연쇄 반응
                        if volcano[(nr, nc)] + cur >= vol_mx[(nr, nc)] and (nr, nc) not in erupted:
                            next_erupt.append((nr, nc))
                    heat[nr][nc] += cur

    # 2. 연쇄 반응
    while next_erupt:
        r, c = next_erupt.popleft()
        if (r, c) in erupted:
            continue
        p = vol_mx[(r, c)]
        erupted.append((r, c))
        heat[r][c] += p
        for d in range(4):
            cur = p
            for dist in range(1, N):
                cur = cur // 2
                if cur <= 0:
                    break
                nr = r + dy[d] * dist
                nc = c + dx[d] * dist

                if nr < 0 or nc < 0 or nr >= N or nc >= N:
                    continue
                if board[nr][nc] == 1:
                    break
                if (nr, nc) in volcano:
                    # 연쇄 반응
                    if volcano[(nr, nc)] + cur >= vol_mx[(nr, nc)] and (nr, nc) not in erupted:
                        next_erupt.append((nr, nc))
                heat[nr][nc] += cur

    # 3. 화석화
    to_delete = []
    for (r, c), i in turtle_pos.items():
        curheat = heat[r][c]
        if curheat >= 20:
            board[r][c] = -2
            to_delete.append(i)

    if to_delete:
        for i in to_delete:
            r, c = turtle[i]
            del turtle[i]
            del turtle_pos[(r, c)]

    return erupted

def reset(erupted, volcano):
    while erupted:
        r, c = erupted.popleft()
        volcano[(r, c)] = 0

N, T, V = map(int, input().split())

board = []
result = [-1] * T

for _ in range(N):
    board.append(list(map(int, input().split())))

turtle = {}
turtle_pos = {}
for i in range(1, T+1):
    r, c = map(int, input().split())
    turtle[i] = [r, c]
    turtle_pos[(r, c)] = i

volcano = {}
vol_mx = {}
for _ in range(V):
    r, c, p = map(int, input().split())
    volcano[(r, c)] = 0
    vol_mx[(r, c)] = p

for time in range(1, 101):
    move_turtle(board, turtle, turtle_pos, N, time)

    inc_vol(volcano)

    # 바다거북 화석화 되면 turtle 자료구조에는 다 지우고, 보드에 -2로 표기
    erupted = erupt_vol(volcano, vol_mx, board, turtle, turtle_pos, N)

    reset(erupted, volcano)

for i in range(T):
    print(result[i])

'''
# 디버깅 기록 — 아기 바다거북의 대모험

**문제:** 아기 바다거북의 대모험: 해저 화산 지대  
**날짜:** 2026-04-28

---

## 버그 1: `enumerate(dict)` 잘못 사용

**위치:** `inc_vol()`

```python
# 🐛 Before
for i, (key, val) in enumerate(volcano):
    volcano[key] = val + 10

# ✅ After
for key in volcano:
    volcano[key] += 10
```

**원인:** `enumerate(dict)`는 `(인덱스, 키)` 쌍을 반환함. 딕셔너리의 키-값 쌍을 순회하려면 `.items()` 써야 함.

---

## 버그 2: `enumerate(dict)` 잘못 사용 (2)

**위치:** `erupt_vol()` — 화석화 단계

```python
# 🐛 Before
for (r, c), i in enumerate(turtle_pos):

# ✅ After
for (r, c), i in turtle_pos.items():
```

**원인:** 버그 1과 동일. 딕셔너리 반복에 `enumerate` 사용.

---

## 버그 3: `to_delete = []`가 루프 안에 위치

**위치:** `erupt_vol()` — 화석화 단계

```python
# 🐛 Before
for (r, c), i in turtle_pos.items():
    to_delete = []   # 매 반복마다 초기화됨
    ...
    to_delete.append(i)

# ✅ After
to_delete = []
for (r, c), i in turtle_pos.items():
    ...
```

**원인:** 리스트 초기화 위치 실수. 루프 안에 두면 매 반복마다 리스트가 비워짐.

---

## 버그 4: 거북이 도착 시 `turtle_pos` 잘못 삭제

**위치:** `move_turtle()`

```python
# 🐛 Before
for elem in to_delete:
    del turtle[elem]
    del turtle_pos[(N-1, N-1)]  # 이미 없을 수도 있고, 다른 거북이가 있을 수도 있음

# ✅ After
if nr == N - 1 and nc == N - 1:
    result[i-1] = time
    to_delete.append(i)
    del turtle_pos[(r, c)]  # 도착 시점에 이전 위치를 즉시 삭제
    continue
```

**원인:** 도착한 거북이의 *이전 위치*를 지워야 하는데, 목적지 좌표를 삭제하려 함.

---

## 버그 5: 열기가 거리에 따라 감소하지 않음 (핵심 로직 버그)

**위치:** `erupt_vol()` — 열기 전파, 연쇄 반응 모두 해당

```python
# 🐛 Before
for dist in range(1, N):
    nr = r + dy[d] * dist
    nc = c + dx[d] * dist
    ...
    np = heat[r][c] / 2  # dist와 무관하게 항상 P/2 고정

# ✅ After
cur = p
for dist in range(1, N):
    cur = cur // 2       # 매 칸마다 이전 칸의 절반
    if cur <= 0:
        break
    nr = r + dy[d] * dist
    ...
    heat[nr][nc] += cur
```

**원인:** 문제 조건 "한 칸 이동할 때마다 이전 칸 열기의 절반"을 잘못 구현. `heat[r][c] / 2`는 항상 출발지 기준으로 고정된 값이 됨.

---

## 버그 6: 정수 나눗셈 대신 실수 나눗셈 사용

**위치:** `erupt_vol()` — 열기 전파

```python
# 🐛 Before
np = heat[r][c] / 2   # float → 19.5, 9.75 같은 값

# ✅ After
cur = cur // 2        # 소수점 내림 (문제 조건: ⌊열기/2⌋)
```

**원인:** 문제에서 `⌊열기/2⌋` (정수 내림)을 명시했으나 `/` 연산자 사용.

---

## 버그 7: board 초기화 시 행이 2배로 생성됨

**위치:** 메인 코드

```python
# 🐛 Before
board = [[0]*N for _ in range(N)]  # N줄 생성 후
...
for _ in range(N):
    board.append(...)              # 또 N줄 추가 → 총 2N줄

# ✅ After
board = []
for _ in range(N):
    board.append(list(map(int, input().split())))
```

**원인:** board를 미리 만들어두고 다시 append해서 행이 두 배가 됨.

---

## 화석화 판정 시 마그마 압력 이중 합산

**위치:** `erupt_vol()` — 화석화 단계

```python
# 🐛 Before
if (r, c) in volcano:
    curheat = volcano[(r, c)] + heat[r][c]  # 마그마 압력을 중복으로 더함
                                             # (분출한 화산은 이미 heat에 P가 포함됨)
else:
    curheat = heat[r][c]

# ✅ After
curheat = heat[r][c]  # heat 배열에 이미 모든 열기가 집계되어 있음
```

**원인:** 분출한 화산의 경우 `heat[r][c]`에 이미 P가 더해져 있는데, `volcano[(r,c)]`를 또 더해 이중 계산됨.

---

## 정리: 실수 패턴

| 유형 | 빈도 | 핵심 교훈 |
|------|------|-----------|
| 딕셔너리 `.items()` 누락 | 2회 | `enumerate(dict)` 쓰지 말 것 |
| 루프 내 리스트 초기화 | 1회 | 누적용 변수는 루프 밖에 선언 |
| 자료구조 포인터 오류 | 1회 | 삭제할 키가 "현재 위치"인지 "목적지"인지 확인 |
| 핵심 수식 오구현 | 2회 | 수식 있는 부분은 손 트레이싱 필수 |
| 자료구조 이중 초기화 | 1회 | 변수 선언 위치 주의 |
'''