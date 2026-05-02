import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

import heapq
from collections import deque

dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]
# 상 좌 하 우

def bfs(r, c, board, N, robots):
    q = deque()
    visited = [[0]*N for _ in range(N)]
    
    q.append([r, c, 0])
    visited[r][c] = True
    cand = []

    while q:
        cr, cc, dist = q.popleft()
        visited[cr][cc] = True

        if board[cr][cc] > 0:
            heapq.heappush(cand, (dist, cr, cc))

        for d in range(4):
            nr = cr + dy[d]
            nc = cc + dx[d]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            if (nr, nc) in robots:
                continue
            if board[nr][nc] == -1:
                continue
                
            visited[nr][nc] = True
            q.append([nr, nc, dist + 1])
    
    if cand:
        return [cand[0][1], cand[0][2]]
    
    return [-1, -1]



def move_vacuum(N, board, robots):
    # 각각의 로봇 청소기는 순서대로 이동 거리가 가장 가까운 오염된 격자로 이동
    # 물건이 위치한 격자나 청소기가 있는 격자로는 지나갈 수 없음
    # 이동 거리는 상하좌우로 인접한 격자를 한 칸씩 이동하여 도달하는 데 필요한 최소 이동 횟수
    # 가장 가까운 격자가 여러 개 -> 행 번호가 작은, 열 번호가 작은
    # to_delete = []
    # to_add = []
    items = sorted(robots.items(), key = lambda x: x[1]) # 인덱스 순
    for (r, c), idx in items:
        nr, nc = bfs(r, c, board, N, robots)

        if (nr, nc) != (-1, -1):
            del robots[(r, c)]
            robots[(nr, nc)] = idx
            # to_delete.append([r, c, robots[(r, c)]])
            # to_add.append([nr, nc, robots[(r, c)]])

def vacuum(N, board, robots):
    # 상 좌 하 우
    shape = {0: [0, 2, 3],
             1: [1, 2, 3],
             2: [0, 1, 2],
             3: [0, 1, 3]}
    
    # for (r, c), idx in robots.items():
    for (r, c), idx in sorted(robots.items(), key=lambda x: x[1]):
        cand = []
        for s in range(4):
            total = 0
            # total += board[r][c]
            if board[r][c] > 0:
                total += min(board[r][c], 20)

            for d in shape[s]:
                nr = r + dy[d]
                nc = c + dx[d]

                if 0 <= nr < N and 0 <= nc < N and board[nr][nc] > 0:
                    total += min(board[nr][nc], 20)
            
            heapq.heappush(cand, (-(total), s))
        
        res = cand[0]
        board[r][c] = max(0, board[r][c] - 20)
        for d in shape[res[1]]:
            nr = r + dy[d]
            nc = c + dx[d]

            if 0 <= nr < N and 0 <= nc < N and board[nr][nc] > 0:
                board[nr][nc] = max(0, board[nr][nc] - 20)

def dusting(N, board):
    for i in range(N):
        for j in range(N):
            if board[i][j] > 0:
                board[i][j] += 5

def spread_dusts(N, board):
    tmp_board = [[0]*N for _ in range(N)]

    for i in range(N):
        for j in range(N):
            total = 0
            if board[i][j] == 0:
                for d in range(4):
                    ni = i + dy[d]
                    nj = j + dx[d]

                    if 0 <= ni < N and 0 <= nj < N and board[ni][nj] > 0:
                        total += board[ni][nj]

                tmp_board[i][j] += (total // 10)

    for i in range(N):
        for j in range(N):
            board[i][j] += tmp_board[i][j]

def print_dust(N, board):
    total = 0
    for i in range(N):
        for j in range(N):
            if board[i][j] > 0:
                total += board[i][j]
    print(total)

def solve(N, R, board, robots):
    # 1. move vacuum
    move_vacuum(N, board, robots)

    # 2. vacuum
    vacuum(N, board, robots)

    # 3. pile up dusts
    dusting(N, board)

    # 4. spread dusts
    spread_dusts(N, board)

    # 5. print
    print_dust(N, board)

N, R, L = map(int, input().split())

# 먼지의 양 p, -1인 경우는 물건 위치
board = []
for _ in range(N):
    board.append(list(map(int, input().split())))

robots = {}
for i in range(1, R + 1):
    r, c = map(int, input().split())
    robots[(r-1, c-1)] = i

for l in range(L):
    solve(N, R, board, robots)

'''
# AI 로봇청소기 - 내가 한 실수들

## 1. 치명적: `dict.items()` unpacking 오류
`robots.items()`는 `((r, c), idx)` 형태인데 `(r, c)`로만 unpacking하려 함.

```python
# ❌ 잘못된 코드
for (r, c) in robots.items():
    # r = (r, c) 튜플, c = idx 정수가 되어 즉시 크래시
```

```python
# ✅ 수정
for (r, c), idx in robots.items():
# 또는
for (r, c) in list(robots.keys()):
```

---

## 2. 치명적: `move_vacuum`이 robots dict를 갱신하지 않음
`to_delete`, `to_add` 리스트만 만들어놓고 정작 `robots`에 적용하는 코드가 없음.
→ 로봇이 한 번도 이동하지 않음.

```python
# ❌ 잘못된 코드
to_delete.append([r, c, robots[(r, c)]])
to_add.append([nr, nc, robots[(r, c)]])
# ... 끝. 적용 안 함.
```

```python
# ✅ 수정
del robots[(r, c)]
robots[(nr, nc)] = idx
```

---

## 3. 치명적: BFS sentinel 값 불일치
BFS는 `[-1, -1]` 반환하는데 호출부는 `-2`를 체크.

```python
# ❌ 잘못된 코드
if nr != -2 and nc != -2:   # 항상 True가 되어버림
```

```python
# ✅ 수정
if (nr, nc) != (-1, -1):
```

---

## 4. 치명적: 순차적 이동 처리 누락
문제: "각각의 로봇 청소기는 **순서대로** 이동"
→ 1번 로봇이 이동한 새 위치를 2번 로봇 BFS에서 장애물로 인식해야 함.

```python
# ✅ 수정: 인덱스 순으로 정렬한 스냅샷으로 iterate, 라이브 dict는 매번 갱신
items = sorted(robots.items(), key=lambda x: x[1])
for (r, c), idx in items:
    nr, nc = bfs(r, c, board, N, robots)  # robots는 라이브 dict
    if (nr, nc) != (-1, -1):
        del robots[(r, c)]
        robots[(nr, nc)] = idx
```

`items`로 처리 순서를 고정하되, BFS에 넘기는 `robots`는 매 iteration마다 갱신된 라이브 dict가 되어 다음 로봇이 이전 로봇의 새 위치를 장애물로 인식.

---

## 5. 치명적: `items` 만들어놓고 정작 안 씀
4번 수정의 후속 실수. 변수만 만들고 for문은 여전히 `robots.items()` 직접 iterate.

```python
# ❌ 잘못된 코드
items = sorted(robots.items(), key=lambda x: x[1])
for (r, c), idx in robots.items():   # ← items 안 씀!
    del robots[(r, c)]   # RuntimeError: dictionary changed size
```

```python
# ✅ 수정
for (r, c), idx in items:
```

---

## 6. 치명적: `vacuum`도 인덱스 순으로 처리해야 함
"청소는 청소기마다 **순서대로** 진행"인데 `list(robots.keys())`는 dict 삽입 순서를 따름.
`move_vacuum`에서 `del → insert`로 인해 순서가 뒤죽박죽이 됨.

```python
# ❌ 잘못된 코드
for (r, c) in list(robots.keys()):
```

```python
# ✅ 수정
for (r, c), idx in sorted(robots.items(), key=lambda x: x[1]):
```

---

## 7. 청소 시 셀당 20 cap 누락
문제: "격자마다 청소할 수 있는 **최대 먼지량은 20**"
방향 선택을 위한 합계 계산 시 `min(먼지, 20)`을 더해야 함.

```python
# ❌ 잘못된 코드
total += board[r][c]
total += board[nr][nc]
```

```python
# ✅ 수정
if board[r][c] > 0:
    total += min(board[r][c], 20)
...
if 0 <= nr < N and 0 <= nc < N and board[nr][nc] > 0:
    total += min(board[nr][nc], 20)
```

---

## 8. 물건(-1) 셀 처리 누락 (두 군데)

### (a) 합계 계산 시
```python
# ❌ board[nr][nc] = -1이면 min(-1, 20) = -1 더해져서 합계가 깎임
if 0 <= nr < N and 0 <= nc < N:
    total += min(board[nr][nc], 20)
```

```python
# ✅ 수정
if 0 <= nr < N and 0 <= nc < N and board[nr][nc] > 0:
    total += min(board[nr][nc], 20)
```

### (b) 청소 시
```python
# ❌ 물건 칸에 적용되면 max(0, -21) = 0이 되어 물건이 사라짐!
board[nr][nc] = max(0, board[nr][nc] - 20)
```

```python
# ✅ 수정
if 0 <= nr < N and 0 <= nc < N and board[nr][nc] > 0:
    board[nr][nc] = max(0, board[nr][nc] - 20)
```

---

## 핵심 교훈

1. **변수 만들고 안 쓰기** — 리팩토링 중 기존 코드 안 바꾸는 실수 (4→5번 연쇄)
2. **dict 순회 중 변경** — 스냅샷 떠서 처리해야 함
3. **순서대로** 라는 문구 = 인덱스 순으로 sort 필요 (move, vacuum 둘 다)
4. **음수 sentinel 값(-1)** — `min`, `max`, 비교 연산 어디든 `> 0` 체크 빠뜨리지 말기
5. **문제의 cap (최대 20)** — "선택 기준"과 "실제 적용" 둘 다에 일관되게 적용
'''