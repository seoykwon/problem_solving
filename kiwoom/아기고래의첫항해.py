import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

'''
1단계를 BFS로 구현한 것이 가장 큰 문제
우선순위가 전혀 작동하지 않음
치명적인 타입에러 
2단계 거리는 맨해튼 거리가 아니라 BFS
2단계 경로 추적의 좌하우상 우선순위 무시
얕은 복사버그. copy.deepcopy(visited)
입력 처리에서 읽는 줄 개수 오류
solve에서 r, c가 절대 업데이트 안 됨
'''

from collections import deque

dir_map = {1: 0, 2: 1, 3: 2, 4: 3}
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]

turns = {
    0: [0, 2, 3, 1], # 상: 상->좌->우->하
    1: [1, 3, 2, 0], # 하: 하->우->좌->상
    2: [2, 1, 0, 3], # 좌: 좌->하->상->우
    3: [3, 0, 1, 2], # 우: 우->상->하->좌
}

def bfs(sr, sc, board, N):
    """(sr, sc)에서 모든 바다 칸까지의 최단 거리. 암초는 통과 불가."""
    INF = float('inf')
    dist = [[INF]*N for _ in range(N)]
    dist[sr][sc] = 0
    q = deque([(sr, sc)])

    while q:
        cr, cc = q.popleft()
        for i in range(4):
            nr, nc = cr + dr[i], cc + dc[i]
            if 0 <= nr < N and 0 <= nc < N and board[nr][nc] == 0 and dist[nr][nc] == INF:
                dist[nr][nc] = dist[cr][cc] + 1
                q.append((nr, nc))
    return dist

def solve():
    N, r, c, d = map(int, input().split())
    board = [list(map(int, input().split())) for _ in range(N)]

    r -= 1
    c -= 1
    d = dir_map[d]

    visited = [[False]*N for _ in range(N)]
    visited[r][c] = True
    result = [(r+1, c+1)] # 출력은 1-indexed

    total_sea = sum(row.count(0) for row in board)

    while len(result) < total_sea:
        # 1단계: 인접 탐험
        while True:
            moved = False
            for nd in turns[d]:
                nr, nc = r + dr[nd], c + dc[nd]
                if 0 <= nr < N and 0 <= nc < N and board[nr][nc] == 0 and not visited[nr][nc]:
                    r, c, d = nr, nc, nd
                    visited[r][c] = True
                    result.append((r+1, c+1))
                    moved = True
                    break # 우선순위상 첫 번째 성공에서 멈춤
            if not moved: # 인접한 칸에 움직일 수 있는 칸이 없을 때
                break
            
        if len(result) >= total_sea:
            break

        # 2단계: 가장 가까운 미방문 바다 선택
        dist_cur = bfs(r, c, board, N)
        target = None
        best = float('inf')
        for i in range(N):
            for j in range(N):
                if not visited[i][j] and board[i][j] == 0 and dist_cur[i][j] < best:
                    best = dist_cur[i][j]
                    target = (i, j)
        if target is None:
            break
        
        # 2단계: 좌->하->우->상 우선순위로 최단 경로 이동
        dist_tgt = bfs(target[0], target[1], board, N)
        priority = [2, 1, 3, 0]
        while (r, c) != target:
            cur = dist_tgt[r][c]
            for i in priority:
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < N and 0 <= nc < N and board[nr][nc] == 0 and dist_tgt[nr][nc] == cur - 1:
                    r, c, d = nr, nc, i
                    break

        visited[r][c] = True
        result.append((r+1, c+1))

    print('\n'.join(f'{x} {y}' for x, y in result))

solve()

'''
문제 이해보다 구현의 정확성에서 주로 막히고 있다.

1. 비슷한 알고리즘으로 대체하는 습관이 있다
2. 경계/인덱싱에서 계속 실수한다
    이 변수가 지금 어떤 타입/범위인가를 머릿속에서 놓치고 있다
3. 디버깅 없이 다 됐다고 판단한다. 
    코드 짜고 반드시 예제 입력으로 손이든 실행이든 한 번 트레이스하기

"문제를 못 읽는다"는 아니다. 머릿속 계획을 코드로 옮기는 중간 단계에서 디테일이 샌다.
알고리즘 지식 새로 쌓을 필요 없고, 짤 때 변수 타입, 인덱스 기준 문제 정의를 계속 의식하는 습관
'''