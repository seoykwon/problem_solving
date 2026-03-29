import sys
from itertools import combinations
input = sys.stdin.readline

def solve():
    N, M = map(int, input().split())

    houses = [] # 집 좌표 목록
    chickens = [] # 치킨집 좌표 목록

    for r in range(N):
        row = list(map(int, input().split()))
        for c in range(N):
            if row[c] == 1: houses.append((r, c))
            if row[c] == 2: chickens.append((r, c))

    ans = float('inf')

    # 치킨집 중 M개 조합을 모두 시도
    for selected in combinations(chickens, M):
        total = 0
        for hr, hc in houses:
            # 선택된 치킨집 중 가장 가까운 거리
            dist = min(abs(hr-cr) + abs(hc - cc) for cr, cc in selected)
            total += dist
        ans = min(ans, total)

    print(ans)

solve()