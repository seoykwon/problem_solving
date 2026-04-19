import sys
import heapq

input = sys.stdin.readline


def solve():
    Q = int(input())
    N = 0

    # 좌표 기반 이중연결리스트
    prev_pos = {}   # 좌표 p -> 바로 왼쪽 가로등 좌표 (없으면 None)
    next_pos = {}   # 좌표 p -> 바로 오른쪽 가로등 좌표 (없으면 None)

    id_to_pos = {}  # ID -> 좌표
    next_id = 1     # 다음 발급 ID (절대 감소 X)

    heap = []       # (-gap, left, right)  동률이면 left 작은 쪽 우선
    valid = {}      # (left, right) 가 현재 유효한 간격인가

    leftmost = rightmost = 0   # 가장 왼쪽/오른쪽 가로등 좌표

    for _ in range(Q):
        q = input().split()
        op = q[0]

        if op == '100':
            N = int(q[1])
            M = int(q[2])
            L = list(map(int, q[3:3 + M]))

            for i, p in enumerate(L):
                id_to_pos[next_id] = p
                next_id += 1
                prev_pos[p] = L[i - 1] if i > 0 else None
                next_pos[p] = L[i + 1] if i < M - 1 else None

            leftmost, rightmost = L[0], L[-1]

            for i in range(M - 1):
                a, b = L[i], L[i + 1]
                heapq.heappush(heap, (-(b - a), a, b))
                valid[(a, b)] = True

        elif op == '200':
            while True:
                neg, a, b = heap[0]
                if valid.get((a, b)):
                    heapq.heappop(heap)
                    del valid[(a, b)]
                    break
                heapq.heappop(heap)

            mid = (a + b + 1) // 2

            next_pos[a] = mid
            prev_pos[b] = mid
            prev_pos[mid] = a
            next_pos[mid] = b

            id_to_pos[next_id] = mid
            next_id += 1

            heapq.heappush(heap, (-(mid - a), a, mid)); valid[(a, mid)] = True
            heapq.heappush(heap, (-(b - mid), mid, b)); valid[(mid, b)] = True

        elif op == '300':
            D = int(q[1])
            p = id_to_pos.pop(D)
            left = prev_pos.pop(p)
            right = next_pos.pop(p)

            if p == leftmost:
                leftmost = right
            if p == rightmost:
                rightmost = left

            if left is not None:
                next_pos[left] = right
                valid.pop((left, p), None)
            if right is not None:
                prev_pos[right] = left
                valid.pop((p, right), None)

            if left is not None and right is not None:
                heapq.heappush(heap, (-(right - left), left, right))
                valid[(left, right)] = True

        elif op == '400':
            # ─────────────────────────────────────────────────────────────
            # 목표: 지금 존재하는 인접 가로등 쌍 중 "가장 먼 간격"을 구한다.
            #
            # 문제는 Python heapq 의 한계다.
            # heapq 는 "맨 위(가장 작은 원소) 꺼내기"만 지원하고,
            # 힙 중간에 박혀있는 원소를 임의로 삭제하는 기능이 없다.
            #
            # 그런데 200/300 을 처리하면서 이미 힙에 넣은 간격이
            # "무효"가 되는 경우가 생긴다.
            #   예) 힙에 (10, 50) 간격이 들어있는 상태에서 200 으로 30 을 끼워넣으면
            #       → (10, 50) 은 더 이상 "인접한" 쌍이 아님 (사이에 30 이 있으니까)
            #       → 대신 (10, 30), (30, 50) 이 새로 힙에 푸시됨
            #       → 근데 (10, 50) 엔트리는 힙에서 뽑을 방법이 없어서 그대로 남음 (유령 엔트리)
            #
            # 그래서 "유효한 간격 목록"을 valid dict 로 따로 들고 다니면서,
            # 힙 꼭대기가 유령이면 버리고(pop), 진짜일 때만 값을 쓴다.
            # 이게 "지연 삭제(lazy deletion)" 기법이다.
            # ─────────────────────────────────────────────────────────────

            max_gap = 0
            while heap:
                neg, a, b = heap[0]        # peek — 아직 꺼내지 않고 확인만
                if valid.get((a, b)):
                    # 이 간격은 여전히 "인접한 두 가로등 사이" 간격이 맞다.
                    # 그러면 이게 곧 현재 힙에 남아있는 최대 간격이다.
                    # (heapq 는 항상 꼭대기가 최솟값 = 여기선 -gap 이 최솟값
                    #  = gap 이 최댓값이 되도록 음수 부호로 넣어뒀으니까)
                    max_gap = -neg
                    # 중요: 여기서 heappop 을 하지 않는다!
                    # 이 간격은 지금도 살아있는 진짜 간격이라, 다음 번 400 이 와도
                    # 여전히 후보여야 하므로 힙에 그대로 남겨둬야 한다.
                    break
                # 유령 엔트리. 다음 400 에서도 쓸모없으니 이 참에 버린다.
                # (언젠가 한 번은 반드시 버려져야 하는 값이라,
                #  각 엔트리는 전체 동안 최대 1번만 pop 되므로 분할 상환 O(log n))
                heapq.heappop(heap)

            # 최소 전력 r 의 2배를 출력한다.
            #   - 왼쪽 끝:   좌표 1 을 비추려면  r ≥ leftmost - 1      → 2r ≥ 2*(leftmost - 1)
            #   - 오른쪽 끝: 좌표 N 을 비추려면  r ≥ N - rightmost     → 2r ≥ 2*(N - rightmost)
            #   - 중간 간격: 거리 d 인 이웃 사이를 덮으려면 r ≥ d/2  → 2r ≥ d (= max_gap)
            ans = max(max_gap, 2 * (leftmost - 1), 2 * (N - rightmost))
            print(ans)


solve()

'''
1. 이 문제는 세 가지 서로 다른 빠른 연산 동시에 요구
    - 최대 간격 찾기: 힙
    - 이웃 찾기: 정렬된 자료구조/연결 리스트
    - ID로 좌표 찾기: dict

2. 지연 삭제는 알아야 하는 테크닉
    힙의 중간을 못 지우지만, 나중에 뽑을 때 걸러내면 됨

3. 연결 리스트를 dict로 구현한다는 발상도 걸림돌
    좌표가 고유하니까 좌표 자체를 노드 주소로 쓰자
    
'''