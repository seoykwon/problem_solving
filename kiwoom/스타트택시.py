from collections import deque
import sys
input = sys.stdin.readline  # 빠른 입력

N, M, fuel = map(int, input().split())  # N: 격자 크기, M: 승객 수, fuel: 초기 연료

# 격자 입력 (1-indexed 위해 앞에 빈 행/열 추가)
arr = [[]]  # arr[0]은 dummy 행
for _ in range(N):
    arr.append([0] + list(map(int, input().split())))  # arr[i][0]은 dummy 열, 1은 벽

taxi = list(map(int, input().split()))  # 택시 초기 위치 [x, y]

# 승객 정보 입력: [출발x, 출발y, 도착x, 도착y]
people = []
for _ in range(M):
    people.append(list(map(int, input().split())))

dx = [0, 1, 0, -1]  # 이동 방향 (우, 하, 좌, 상)
dy = [1, 0, -1, 0]


def find_person():
    tx, ty = taxi  # 현재 택시 위치

    dist_map = get_dist(tx, ty)  # 택시에서 모든 칸까지의 거리 계산

    # 정렬 기준: 거리 오름차순 → 행 오름차순 → 열 오름차순
    # sort 후 pop()으로 마지막 요소(= 가장 우선순위 높은 승객)를 꺼내기 위해
    # 음수 부호로 역정렬 (내림차순으로 쌓아서 pop하면 오름차순 효과)
    people.sort(key=lambda p: (-dist_map[p[0]][p[1]], -p[0], -p[1]))

    sx, sy, ex, ey = people.pop()  # 우선순위 가장 높은 승객 꺼내기
    return [sx, sy, ex, ey, dist_map[sx][sy]]  # 승객 정보 + 택시→승객 거리 반환


def drive():
    global taxi   # 택시 위치 전역 변수 수정
    global fuel   # 연료 전역 변수 수정

    sx, sy, ex, ey, dist = find_person()  # 태울 승객 선택

    if dist == -1:       # 택시가 승객에게 도달 불가능하면 실패
        return False

    fuel -= dist         # 택시 → 승객 이동 연료 소모
    if fuel < 0:         # 연료 부족하면 실패
        return False

    used = get_dist(sx, sy)       # 승객 출발지에서 모든 칸까지 거리 계산
    if used[ex][ey] == -1:        # 승객 출발지 → 목적지 도달 불가능하면 실패
        return False

    fuel -= used[ex][ey]          # 승객 태우고 목적지까지 이동 연료 소모
    if fuel < 0:                  # 연료 부족하면 실패
        return False

    fuel += used[ex][ey] * 2     # 이동 거리의 2배 연료 충전 (문제 조건)
    taxi = [ex, ey]               # 택시 위치를 목적지로 업데이트
    return True


def get_dist(a, b):
    """(a, b)에서 출발해 모든 칸까지의 최단 거리를 BFS로 계산"""
    q = deque()
    q.append((a, b))

    # 방문 배열 초기화 (-1: 미방문 or 도달 불가)
    visited = [[-1 for _ in range(N+1)] for _ in range(N+1)]
    visited[a][b] = 0  # 출발지 거리 = 0

    while q:
        x, y = q.popleft()
        for k in range(4):          # 4방향 탐색
            nx = x + dx[k]
            ny = y + dy[k]
            if 0 < nx <= N and 0 < ny <= N and visited[nx][ny] == -1:
                if not arr[nx][ny]:              # 벽(1)이 아닌 경우만 이동
                    visited[nx][ny] = visited[x][y] + 1
                    q.append((nx, ny))

    return visited  # 모든 칸까지의 거리 맵 반환


# M명의 승객을 순서대로 처리
for _ in range(M):
    if not drive():    # 한 명이라도 실패하면
        fuel = -1      # 연료를 -1로 설정하고 중단
        break

print(fuel)  # 최종 연료 출력 (실패 시 -1)