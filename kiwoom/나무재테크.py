# import sys
# input = sys.stdin.readline

# def solve():
#     N, M, K = map(int, input().split())

#     A = []
#     for _ in range(N):
#         A.append(list(map(int, input().split())))

#     nutrient = [[5] * N for _ in range(N)]
#     trees = [[[] for _ in range(N)] for _ in range(N)]

#     for _ in range(M):
#         x, y, z = map(int, input().split())
#         trees[x-1][y-1].append(z)
#         trees[x-1][y-1].sort()

#     dx = [-1,-1,-1,0,0,1,1,1]
#     dy = [-1,0,1,-1,1,-1,0,1]

#     for _ in range(K):
#         # 봄 + 여름
#         for r in range(N):
#             for c in range(N):
#                 alive = []
#                 dead_nutrient = 0
#                 for age in trees[r][c]:
#                     if nutrient[r][c] >= age:
#                         nutrient[r][c] -= age
#                         alive.append(age + 1)
#                     else:
#                         dead_nutrient += age // 2
#                 nutrient[r][c] += dead_nutrient
#                 trees[r][c] = alive
        
#         # 가을
#         new_trees = [[[] for _ in range(N)] for _ in range(N)]
#         for r in range(N):
#             for c in range(N):
#                 for age in trees[r][c]:
#                     if age % 5 == 0:
#                         for d in range(8):
#                             nr, nc = r + dx[d], c + dy[d]
#                             if 0 <= nr < N and 0 <= nc < N:
#                                 new_trees[nr][nc].append(1)

#         for r in range(N):
#             for c in range(N):
#                 if new_trees[r][c]:
#                     trees[r][c] = new_trees[r][c] + trees[r][c]
#                     trees[r][c].sort()

#         # 겨울
#         for r in range(N):
#             for c in range(N):
#                 nutrient[r][c] += A[r][c]

#     print(sum(len(trees[r][c]) for r in range(N) for c in range(N)))

# solve()

'''
핵심 변경점

리스트 → defaultdict(int) : {나이: 개수} 로 관리해서 나무가 100만 그루여도 딕셔너리 항목은 몇 개 안 됨
봄 최적화 : 같은 나이 나무를 한 번에 처리 → min(cnt, nutrient // age) 로 살 수 있는 그루 수 한 번에 계산
가을 최적화 : 번식도 new_count에 개수만 누적 후 한 번에 추가
'''
import sys
from collections import defaultdict
input = sys.stdin.readline

def solve():
    N, M, K = map(int, input().split())

    A = []
    for _ in range(N):
        A.append(list(map(int, input().split())))

    nutrient = [[5] * N for _ in range(N)]
    # trees[r][c] = {나이: 개수} 딕셔너리
    trees = [[defaultdict(int) for _ in range(N)] for _ in range(N)]

    for _ in range(M):
        x, y, z = map(int, input().split())
        trees[x-1][y-1][z] += 1

    dx = [-1,-1,-1,0,0,1,1,1]
    dy = [-1,0,1,-1,1,-1,0,1]

    for _ in range(K):
        # 봄 + 여름
        for r in range(N):
            for c in range(N):
                if not trees[r][c]:
                    continue
                new_trees = defaultdict(int)
                dead_nutrient = 0
                for age in sorted(trees[r][c]):
                    cnt = trees[r][c][age]
                    # 이 나이의 나무가 몇 그루나 살 수 있는지 계산
                    can_live = min(cnt, nutrient[r][c] // age)
                    die = cnt - can_live
                    nutrient[r][c] -= can_live * age
                    if can_live:
                        new_trees[age + 1] += can_live
                    dead_nutrient += die * (age // 2)
                nutrient[r][c] += dead_nutrient
                trees[r][c] = new_trees

        # 가을
        new_count = [[0] * N for _ in range(N)]
        for r in range(N):
            for c in range(N):
                for age, cnt in trees[r][c].items():
                    if age % 5 == 0:
                        for d in range(8):
                            nr, nc = r + dx[d], c + dy[d]
                            if 0 <= nr < N and 0 <= nc < N:
                                new_count[nr][nc] += cnt

        for r in range(N):
            for c in range(N):
                if new_count[r][c]:
                    trees[r][c][1] += new_count[r][c]

        # 겨울
        for r in range(N):
            for c in range(N):
                nutrient[r][c] += A[r][c]

    print(sum(sum(v for v in trees[r][c].values()) for r in range(N) for c in range(N)))

solve()