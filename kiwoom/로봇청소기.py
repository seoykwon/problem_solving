N, M = map(int, input().split())
r, c, d = map(int, input().split())
board = [list(map(int, input().split())) for _ in range(N)]

# 방향: 0=북, 1=동, 2=남, 3=서
# 반시계 회전: 0→3→2→1→0
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

cleaned = 0

while True:
    # 1. 현재 칸 청소
    if board[r][c] == 0:
        board[r][c] = 2  # 청소 완료 표시
        cleaned += 1

    # 주변 4칸 중 청소 안 된 빈 칸 확인
    can_clean = False
    for i in range(4):
        nr, nc = r + dr[i], c + dc[i]
        if 0 <= nr < N and 0 <= nc < M and board[nr][nc] == 0:
            can_clean = True
            break

    if not can_clean:
        # 2. 청소할 칸 없음 → 후진 시도
        # 후진 방향: 현재 방향의 반대
        br, bc = r - dr[d], c - dc[d]
        if 0 <= br < N and 0 <= bc < M and board[br][bc] != 1:
            r, c = br, bc  # 후진 (방향 유지)
        else:
            break  # 뒤가 벽 → 종료
    else:
        # 3. 반시계 회전 후 전진 가능하면 전진
        d = (d - 1) % 4  # 반시계 90도 회전
        nr, nc = r + dr[d], c + dc[d]
        if board[nr][nc] == 0:
            r, c = nr, nc

print(cleaned)