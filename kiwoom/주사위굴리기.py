N, M, x, y, K = map(int, input().split())
board = [list(map(int, input().split())) for _ in range(N)]
commands = list(map(int, input().split()))

# 주사위 면: [top, bottom, north, south, west, east]
#              [  0,     1,     2,     3,    4,    5]
dice = [0] * 6

# 방향별 이동량 (동, 서, 북, 남)
dr = {1: 0, 2: 0, 3: -1, 4: 1}
dc = {1: 1, 2: -1, 3: 0, 4: 0}

def roll(dice, d):
    t, bo, n, s, w, e = dice  # top, bottom, north, south, west, east
    if d == 1:   # 동쪽: top←west, east←top, bottom←east, west←bottom
        return [w, e, n, s, bo, t]
    elif d == 2: # 서쪽: top←east, west←top, bottom←west, east←bottom
        return [e, w, n, s, t, bo]
    elif d == 3: # 북쪽: top←south, north←top, bottom←north, south←bottom
        return [s, n, t, bo, w, e]
    elif d == 4: # 남쪽: top←north, south←top, bottom←south, north←bottom
        return [n, s, bo, t, w, e]

for cmd in commands:
    nx, ny = x + dr[cmd], y + dc[cmd]

    # 범위 밖이면 무시
    if not (0 <= nx < N and 0 <= ny < M):
        continue

    # 주사위 굴리기
    dice = roll(dice, cmd)
    x, y = nx, ny

    # 칸의 값이 0이면 주사위 바닥면 → 칸으로 복사
    if board[x][y] == 0:
        board[x][y] = dice[1]
    # 칸의 값이 0이 아니면 칸 → 주사위 바닥면으로 복사 후 칸을 0으로
    else:
        dice[1] = board[x][y]
        board[x][y] = 0

    print(dice[0])
'''

**핵심 아이디어: 주사위 굴리기**

주사위 상태를 `[top, bottom, north, south, west, east]` 6개의 값으로 관리합니다.
```
방향별 면 이동 규칙:

동쪽 굴리기          서쪽 굴리기
  top ← west           top ← east
  east ← top           west ← top
  bottom ← east        bottom ← west
  west ← bottom        east ← bottom

북쪽 굴리기          남쪽 굴리기
  top ← south          top ← north
  north ← top          south ← top
  bottom ← north       bottom ← south
  south ← bottom       north ← bottom
```

**예제 흐름 (일부)**
```
초기: 주사위 전면 0, 위치 (0,0)
남쪽 이동 → (1,0): 칸=3 → 주사위 바닥=3, 칸=0, 출력: top=0
남쪽 이동 → (2,0): 칸=5 → 주사위 바닥=5, 칸=0, 출력: top=0
남쪽 이동 → (3,0): 칸=7 → 주사위 바닥=7, 칸=0, 출력: top=3  ← 이전 north가 top으로
...
'''