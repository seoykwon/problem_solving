import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

from collections import deque
import heapq

dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]

def bfs(r, c, key, board):
    queue = deque()
    visited = [[False]*N for _ in range(N)]

    queue.append([r, c])
    total = 0

    while queue:
        cr, cc  = queue.popleft()
        visited[cr][cc] = True
        total += 1

        for d in range(4):
            nr = cr + dy[d]
            nc = cc + dx[d]

            if nr < 0 or nc < 0 or nr >= N or nc >= N:
                continue
            if visited[nr][nc]:
                continue
            if board[nr][nc] != key:
                continue
            visited[nr][nc] = True
            queue.append([nr, nc])

    return total

def delete_micro(key, micros):
    micros.pop(key)

def insert_micro(micro, board, micros, areas):
    key, c1, r1, c2, r2 = micro
    # 1. 보드에 직사각형 미생물 투입
    i = r1
    while i < r2:
        j = c1
        while j < c2:
            board[i][j] = key
            j += 1
        i += 1
    # 2. 새로 투입된 미생물이 원래 영역에 있던 미생물 덮어씀

    # 3. 기존에 있던 미생물 무리가 새로 투입된 미생물에 의해 둘 이상으로 나뉘면
    # 기존 미생물 사라짐. .pop(key)
    goal = areas[key]
    visited = [False] * Q
    for i in range(N):
        for j in range(N):
            num = board[i][j]
            if num != 0 and not visited[num]:
                visited[num] = True
                a = bfs(i, j, num, board)
                if goal != a:
                    delete_micro(key, micros)
                else:
                    areas[num] = a

def possible(key, i, j, new_board, micros):
    # i, j는 좌하단
    _, c1, r1, c2, r2 = micros[key]
    jlen = j + (c2 - c1 + 1)
    istart = i - (r2 - r1 + 1)

    if istart < 0 or jlen < 0 or istart >= N or jlen >= N:
        return False
    for y in range(istart, i + 1):
        for x in range(j, jlen):
            if new_board[y][x] != 0:
                return False
    return True

def mark(key, i, j, new_board, micros):
    # i, j는 좌하단
    _, c1, r1, c2, r2 = micros[key]
    jlen = j + (c2 - c1 + 1)
    istart = i - (r2 - r1 + 1)

    for y in range(istart, i + 1):
        for x in range(j, jlen):
            new_board[y][x] = key

def move_micro(board, micros, areas):
    q = []
    # 1. 가장 영역이 넓은 무리, 둘 이상이면 먼저 투입된 미생물 옮기기
    for key in micros.keys():
        heapq.heappush(q, (-(areas[key]), key))

    # 2. 기존 형태를 유지하며, 다른 미생물과 겹치지 않도록.
    # x좌표가 최대한 작고, 그 다음 y 좌표가 작은 위치로
    new_board = [[0]*N for _ in range(N)]
    marked = [False] * Q
    while q:
        _, key = heapq.heappop(q)

        for j in range(N):
            for i in range(N-1, -1, -1):
                if new_board[i][j] != 0:
                    if possible(key, i, j, new_board, micros):
                        mark(key, i, j, new_board, micros)
                        marked[key] = True

    # 3. 옮기는 과정에서 어떤 곳에도 둘 수 없는 무리는 사라짐
    for key in micros.keys():
        if not marked[key]:
            micros.pop(key)

    board = new_board

def calc_area():
    # 1. 무리 중 상하좌우로 맞닿은 면이 있는 무리 한 쌍
    # A 영역 넓이 * B 영역 넓이. 모든 쌍의 곱을 더한 값 결과 -> 출력
    pair = set()

    for i in range(N):
        for j in range(N):
            if board[i][j] != 0:
                k1 = board[i][j]
                for d in range(4):
                    ni = i + dy[d]
                    nj = j + dx[d]

                    if ni < 0 or nj < 0 or ni >= N or nj >= N:
                        continue
                    if board[ni][nj] == k1:
                        continue
                    pair.add((k1, board[ni][nj]))

    result = 0
    for s1, s2 in pair:
        result += (areas[s1] * areas[s2])

N, Q = map(int, input().split())

board = [[0] * N for _ in range(N)]
micros = {}
areas = {}

for i in range(1, Q+1):
    x1, y1, x2, y2 = map(int, input().split())
    y1 = N - y1
    y2 = N - y2
    micros[i] = [i, x1, y2, x2, y1]
    sarea = ((y1 - y2) * (x2 - x1))
    areas[i] = sarea

    insert_micro(micros[i], board, micros, areas)

    move_micro(board, micros, areas)

    calc_area()

'''
기존 코드의 문제점:

visited[nr][nc] 대입만 하고 queue.append 전에 실제 방문 처리 누락
move_micro에서 첫 유효 위치를 찾아도 break 없이 계속 순회
dict.pop() 순회 중 삭제 → RuntimeError
좌표 변환 오류 (y1, y2 뒤바뀜)
calc_area에서 board/areas 미참조
'''

import sys
from collections import deque

def solve():
    N, Q = map(int, input().split())
    # N: 배양 용기 크기, Q: 실험 횟수

    board = [[0] * N for _ in range(N)]
    # N×N 격자. 각 칸에 미생물 번호 저장 (0이면 비어있음)

    micro_cells = {}
    # 미생물 번호 → 그 미생물이 차지한 칸들의 집합 {(r,c), ...}

    def count_components(cells):
        # cells 안의 칸들이 몇 개의 덩어리로 나뉘는지 반환
        if not cells:
            return 0
        visited = set()
        count = 0
        for start in cells:
            if start in visited:
                continue
            count += 1
            if count > 1:
                return count
            # count > 1 이면 이미 분리된 거라 더 볼 필요 없음
            q = deque([start])
            visited.add(start)
            while q:
                r, c = q.popleft()
                for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                    nb = (r + dr, c + dc)
                    if nb in cells and nb not in visited:
                        visited.add(nb)
                        q.append(nb)
                # 상하좌우 인접한 칸이 cells 안에 있으면 같은 덩어리로 탐색
        return count

    results = []

    for q_idx in range(1, Q + 1):
        x1, y1, x2, y2 = map(int, input().split())
        # (x1,y1): 직사각형 좌하단, (x2,y2): 우상단 (좌표 평면 기준)

        r_top   = N - y2   # 배열 기준 위쪽 행 (포함)
        r_bot   = N - y1   # 배열 기준 아래쪽 행 (미포함)
        c_left  = x1       # 배열 기준 왼쪽 열 (포함)
        c_right = x2       # 배열 기준 오른쪽 열 (미포함)

        new_rect = set()
        for r in range(r_top, r_bot):
            for c in range(c_left, c_right):
                new_rect.add((r, c))
        # 새로 투입되는 미생물이 차지할 칸들

        # ── STEP 1 : 미생물 투입 ──────────────────────────────────────

        affected = set()
        for r, c in new_rect:
            if board[r][c] != 0:
                affected.add(board[r][c])
        # new_rect 안에 이미 있던 미생물 번호들 수집

        to_delete = []
        for key in affected:
            old_cells = micro_cells[key]
            remaining = old_cells - new_rect
            # 새 미생물한테 잡아먹히고 남은 칸들

            if not remaining or count_components(remaining) > 1:
                # 남은 게 없거나, 둘 이상으로 분리되면 완전 소멸
                for r, c in remaining:
                    board[r][c] = 0
                to_delete.append(key)
            else:
                micro_cells[key] = remaining
                # 연결 유지되면 생존, 잡아먹힌 칸만 제거

        for key in to_delete:
            del micro_cells[key]
        # 순회 끝난 뒤에 삭제 (순회 중 삭제하면 RuntimeError)

        micro_cells[q_idx] = new_rect
        for r, c in new_rect:
            board[r][c] = q_idx
        # 새 미생물 배치 (rect 안을 q_idx로 덮어씌움)

        # ── STEP 2 : 새 배양 용기로 이동 ─────────────────────────────

        order = sorted(micro_cells.keys(),
                       key=lambda k: (-len(micro_cells[k]), k))
        # 넓은 순서 정렬, 넓이 같으면 번호 작은 것(먼저 투입된 것) 우선

        new_board = [[0] * N for _ in range(N)]
        new_micro_cells = {}

        for key in order:
            cells = micro_cells[key]
            rows = [r for r, c in cells]
            cols = [c for r, c in cells]
            r_min, r_max = min(rows), max(rows)
            c_min, c_max = min(cols), max(cols)
            height = r_max - r_min + 1
            width  = c_max - c_min + 1
            # 현재 미생물의 바운딩 박스 크기

            rel = [(r - r_min, c - c_min) for r, c in cells]
            # 바운딩 박스 좌상단 기준 상대 좌표로 변환
            # 이걸 해야 나중에 어디든 갖다 붙일 수 있음

            placed = False
            for tc in range(N - width + 1):
                # tc: 새 위치의 왼쪽 열. x 최소 우선이라 0부터 시작
                if placed:
                    break
                for tr in range(N - height, -1, -1):
                    # tr: 새 위치의 위쪽 행. y 최소(= 배열 행 최대) 우선이라 아래부터
                    if all(new_board[tr + dr][tc + dc] == 0 for dr, dc in rel):
                        # 놓으려는 칸이 전부 비어있으면 배치
                        for dr, dc in rel:
                            new_board[tr + dr][tc + dc] = key
                        new_micro_cells[key] = {(tr + dr, tc + dc) for dr, dc in rel}
                        placed = True
                        break
            # placed == False면 어디도 못 놓음 → 소멸 (그냥 안 넣으면 됨)

        board = new_board
        micro_cells = new_micro_cells

        # ── STEP 3 : 실험 결과 기록 ──────────────────────────────────

        result = 0
        seen_pairs = set()

        for key in micro_cells:
            area_key = len(micro_cells[key])
            for r, c in micro_cells[key]:
                for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < N and 0 <= nc < N:
                        other = board[nr][nc]
                        if other != 0 and other != key:
                            pair = (min(key, other), max(key, other))
                            if pair not in seen_pairs:
                                seen_pairs.add(pair)
                                result += area_key * len(micro_cells[other])
                            # 인접한 서로 다른 무리 쌍 발견 시 넓이 곱 더함
                            # (A,B)와 (B,A)를 같은 쌍으로 처리하려고 min/max 정규화

        results.append(result)

    for r in results:
        print(r)

solve()