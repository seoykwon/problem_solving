import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

import math
import copy

Q = int(input())
N, M = 0, 0
towns = {}
towns_lst = []

def add_lamp():
    global M
    M += 1
    # M+1의 고유번호 부여 0-indexed
    # 인접한 가로등 사이의 거리가 가장 먼 곳 가운데
    # math.ceil(i + (i + 1) // 2)
    # 반드시 두 가로등 사이에 위치
    dist = 0
    idx = -1
    for m in range(M - 1):
        if (m + 1) - m > dist:
            dist = (m + 1) - m
            idx = m

    towns[M-1] = [idx, math.ceil(dist // 2)]
    towns_lst.insert(idx, math.ceil(dist // 2))
    # idx 이후 밀린 인덱스 업데이트 해주기
    for ni in range(idx + 1, M):
        towns[ni][0] += 1

def discard_lamp(idx):
    global M

    lst_i = towns[idx-1][0]
    towns_lst.remove(lst_i)
    towns.pop(idx - 1)
    M -= 1

def calc_electricity():
    # 최소 소비 전력 r 구하기
    # 설치된 위치 x를 기준으로 [x - r, x + r] 거리를 밝힘
    mx = 0
    for m in range(M - 1):
        if towns_lst[m + 1] - towns_lst[m] > mx:
            mx = towns_lst[m + 1] - towns_lst[m]
        # list로 가로등을 관리하면 추가 됐을 때 인덱스를 순차적으로 고치는데 너무 많은 시간이 드는데?
    
    print(math.ceil(mx // 2) * 2)

for _ in range(Q):
    query = list(map(int, input().split()))
    op = int(query[0])

    if op == 100:
        N = int(query[1])
        M = int(query[2])
        lst = query[3:]
        towns_lst = copy.deepcopy(query[3:])
        for m in range(M):
            towns[m] = [m, lst[m]]

    if op == 200:
        add_lamp()

    if op == 300:
        print("300")
        idx = query[1]
        discard_lamp(idx)

    if op == 400:
        print("here")
        calc_electricity()