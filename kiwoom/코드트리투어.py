import heapq
import sys
from collections import defaultdict

# Solution
class Item:
    def __init__(self, id, r, dest):
        self.id = id
        self.r = r
        self.dest = dest
        self.profit = 0

        self.update_profit()

    def update_profit(self):
        global dist
        self.profit = self.r - dist[self.dest]

    def __lt__(self, other):
        return (-self.profit, self.id) < (-other.profit, other.id)

    def __repr__(self):
        return f"Item{self.id}: {self.profit}"

# Step 1: 코드트리 랜드 건설
def build_land(operation):
    set_edges(operation)
    set_dist(0)  # 시작은 0

# Edge 그래프 생성
def set_edges(operation):
    global N, edges
    N = operation[0]
    M = operation[1]

    edges = [[] for _ in range(N)]

    for i in range(2, 3 * M + 2, 3):
        u = operation[i]
        v = operation[i + 1]
        w = operation[i + 2]

        edges[u].append((v, w))
        edges[v].append((u, w))

# 최단 거리 측정
def set_dist(start):
    global dist
    dist = [sys.maxsize] * N

    hp = [[0, start]]
    dist[start] = 0

    while hp:
        d, curr = heapq.heappop(hp)

        if d > dist[curr]:
            continue

        for next, w in edges[curr]:
            if dist[next] > dist[curr] + w:
                dist[next] = dist[curr] + w
                heapq.heappush(hp, [dist[next], next])

# Step 2: 여행 상품 생성
def create_product(operation):
    global products, dist

    id, r, dest = operation
    new_item = Item(id, r, dest)

    heapq.heappush(products, new_item)
    product_id_set.add(id)

# Step 3: 여행 상품 취소
def delete_product(id):
    if id in product_id_set:
        product_id_set.remove(id)

# Step 4: 여행 상품 판매
def sell_product():
    while True:
        if len(products) <= 0:
            return -1

        item = heapq.heappop(products)

        if item.id not in product_id_set:
            continue

        if item.profit < 0:
            heapq.heappush(products, item)
            return - 1

        return item.id

# Step 5: 시작지 변경
def change_starting_point(s):
    global products

    set_dist(s)

    for item in products:
        item.update_profit()

    heapq.heapify(products)

# Main
Q = int(sys.stdin.readline().strip())
N = 0
products = []
edges = []
dist = []
product_id_set = set()

# Game
op = list(map(int, sys.stdin.readline().strip().split()))
build_land(op[1:])

for _ in range(Q - 1):
    op = list(map(int, sys.stdin.readline().strip().split()))

    # 상품 추가
    if op[0] == 200:
        create_product(op[1:])
    # 상품 삭제
    elif op[0] == 300:
        delete_product(op[1])
    # 상품 판매
    elif op[0] == 400:
        id = sell_product()
        print(id)
    # 상품 재생성
    elif op[0] == 500:
        change_starting_point(op[1])