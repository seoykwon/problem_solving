import sys
input = sys.stdin.readline

N, M = map(int, input().split())
r, c, d = map(int, input().split())
board = []
for i in range(N):
    board.append(list(map(int, input().split())))

dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

cleaned = [[False] * M for _ in range(N)]
count = 0

while True:
    # 현재 칸이 청소되지 않았으면 청소
    if not cleaned[r][c]:
        cleaned[r][c] = True
        count += 1

    # 주변 4칸 중 청소되지 않은 빈 칸이 있는지 확인
    has_dirty = False
    for i in range(4):
        nr, nc = r + dr[i], c + dc[i]
        if 0 <= nr < N and 0 <= nc < M and board[nr][nc] == 0 and not cleaned[nr][nc]:
            has_dirty = True
            break

    if not has_dirty:
        # 주변에 청소할 칸 없음 -> 후진 시도
        # 후진 방향: 현재 방향의 반대
        br, bc = r + dr[(d + 2) % 4], c + dc[(d + 2) % 4]
        if board[br][bc] == 1:
            # 후진 불가 (벽)
            break
        else:
            # 후진 (방향 유지)
            r, c = br, bc
    else:
        # 주변에 청소할 칸 있음. 반시계 90도 회전
        d = (d + 3) % 4
        # 앞쪽 칸이 청소되지 않은 빈 칸이면 전진
        nr, nc = r + dr[d], c + dc[d]
        if board[nr][nc] == 0 and not cleaned[nr][nc]:
            r, c = nr, nc
        # 다시 1번으로 돌아감 (while loop 반복)

print(count)