import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

import heapq

T = int(input())
N = 0
ship = {}
ship_ready = [] # -p, id
valid = {}
reload = [] # 0: tr 다시 장전되는 시간, 1: 선박 id
state = {} # id -> 'ready' or 'reloading'

for t in range(T):
    query = list(map(int, input().split()))
    op = query[0]

    while reload:
        tr, _ = reload[0]
        if tr <= t:
            newt, id = heapq.heappop(reload)
            heapq.heappush(ship_ready, (-(valid[id]), id))
            state[id] = 'ready'
        else:
            break

    if op == 100:
        N = query[1]
        lst = query[2:]
        for i in range(0, N*3, 3):
            id = lst[i]
            p = lst[i+1]
            r = lst[i+2]
            ship[id] = [p, r]
            valid[id] = p
            heapq.heappush(ship_ready, (-p, id))
            state[id] = 'ready'

    if op == 200:
        id = query[1]
        p = query[2]
        r = query[3]
        ship[id] = [p, r]
        valid[id] = p
        heapq.heappush(ship_ready, (-p, id))
        state[id] = 'ready'

    if op == 300:
        id = query[1]
        pw = query[2]
        valid[id] = pw
        if state.get(id) == 'ready':
            heapq.heappush(ship_ready, (-pw, id))

    if op == 400:
        # 사격 대기 선박 중 공격력이 가장 높은 5개 선박
        cnt = 0
        attackp = 0
        plst = []
        while ship_ready:
            negp, id = heapq.heappop(ship_ready)
            if valid[id] == -(negp):
                cnt += 1
                attackp += valid[id]

                plst.append(id)
                # r시간 후 재장전
                # reload.append([id, t + ship[id][1], -(negp)])
                heapq.heappush(reload, ((t + ship[id][1]), id))
                state[id] = 'reloading'

            if cnt == 5:
                break

        # print(attackp, " ", cnt, end = ' ')
        # for _ in range(cnt):
        #     print(plst, end = ' ')
        print(attackp, cnt, *plst)

'''
구현 디테일을 잡는 습관이 아직 덜 베어있는 상태. 알고리즘 아이디어 (lazy deletion heap, reload 힙으로 시간관리) 잡음

타입 일관성 실수: 
    valid[id] = [p] vs valid[id] = p. 같은 변수를 여러 분기에서 쓰는데 한 곳만 다르게 저장.
    이 dict/list에 들어가는 값의 타입을 한 문장으로 설명할 수 있나?
루프 범위 실수:
    range(0, N, 3)을 range(0, N*3, 3)로.
    i가 뽑을 수 있는 최댓값이 뭐고, 그게 실제 인덱싱 한계랑 맞나? 작은 예시 돌려보기
들여쓰기로 인한 스코프 실수:
    heappush가 for 밖에 있었던 거. 
    반복 안에서 일어나야 하는 작업인지, 한 번만 일어나야 하는 작업인지 매번 자문
출력 포맷 실수:
    print(plst)를 반복 -> 체크 습관
상태 동기화 누락: 
    op 300에서 heap에 push를 안 했던 것. 
    어떤 자료구조를 바꿨으면, 이 자료구조와 연결된 다른 자료구조들도 같이 갱신해야 하나?
    lazy deletion 패턴 쓸 때 특히 자주 나오는 함정
    
'''