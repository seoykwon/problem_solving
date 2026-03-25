from collections import deque

gears = []
for _ in range(4):
    gears.append(deque(map(int, input())))

K = int(input())

for _ in range(K):
    num, direction = map(int, input().split())
    num -= 1  # 0-indexed
    
    # 각 기어의 회전 방향 결정 (0: 정지)
    rotate = [0] * 4
    rotate[num] = direction
    
    # 오른쪽으로 전파
    for i in range(num, 3):
        # 기어 i의 오른쪽(2) vs 기어 i+1의 왼쪽(6)
        if gears[i][2] != gears[i+1][6]:
            rotate[i+1] = -rotate[i]
        else:
            break
    
    # 왼쪽으로 전파
    for i in range(num, 0, -1):
        # 기어 i의 왼쪽(6) vs 기어 i-1의 오른쪽(2)
        if gears[i][6] != gears[i-1][2]:
            rotate[i-1] = -rotate[i]
        else:
            break
    
    # 동시 회전 적용
    for i in range(4):
        gears[i].rotate(rotate[i])  # rotate(1)=시계, rotate(-1)=반시계

# 점수 계산
score = 0
for i in range(4):
    score += gears[i][0] * (2 ** i)

print(score)