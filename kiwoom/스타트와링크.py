from itertools import combinations
import sys
input = sys.stdin.readline

N = int(input())
S = [list(map(int, input().split())) for _ in range(N)]

def team_score(members):
    score = 0
    for i in members:
        for j in members:
            if i != j:
                score += S[i][j]
    return score

people = list(range(N))
half = N // 2
min_diff = float('inf')

for start_team in combinations(people, half):
    link_team = tuple(p for p in people if p not in start_team)
    diff = abs(team_score(start_team) - team_score(link_team))
    min_diff = min(min_diff, diff)
    if min_diff == 0:
        break

print(min_diff)