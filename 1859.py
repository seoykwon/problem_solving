import sys
sys.stdin = open("input.txt", "r")
# sys.stdout = open("output.txt", "w")

def solution():
    profit = 0
    start_index = 0
    max_index = 0
    max_ = 0
    now_buy_cost = 0
    count = 0
    while True:

        for i in range(start_index, N):
            if max_ < cost[i]:
                max_ = cost[i]
                max_index = i

        for i in range(start_index, max_index):
            now_buy_cost += cost[i]
            count += 1

        profit += (cost[max_index] * count) - now_buy_cost
        count = 0
        now_buy_cost = 0
        max_ = 0
        if max_index == len(cost) - 1:
            break

        start_index = max_index + 1

    return profit
    

T = int(input())

for test_case in range(1, T + 1):
    N = int(input())
    cost = list(map(int, input().split()))

    print(f'#{test_case} {solution()} ')
