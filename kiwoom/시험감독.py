import math

N = int(input())
A = list(map(int, input().split()))
B, C = map(int, input().split())

total = 0
for a in A:
    remaining = a - B

    if remaining > 0:
        total += 1 + math.ceil(remaining / C)
    else:
        total += 1

print(total)