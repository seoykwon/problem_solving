import heapq

def schedule(tasks):
    # 입력: (task_type, arrival, duration)

    # 원본 인덱스(1-indexed)를 튜플에 추가
    # [(task_type, arrival, duration, 원본순서), ...]
    indexed = [(task_type, arrival, duration, i+1) 
               for i, (task_type, arrival, duration) in enumerate(tasks)]
    
    # 도착시간 기준 오름차순 정렬 (arrival = x[1])
    indexed.sort(key=lambda x: x[1])

    heap = []       # 대기 중인 작업들 (우선순위 큐)
    time = 0        # 현재 시각
    idx = 0         # indexed에서 다음에 꺼낼 작업 포인터
    result = []     # 완료된 작업의 원본 인덱스 순서
    current = None  # 선점당해서 중단된 작업 임시 보관 (task_type, remaining, arrival, orig_idx)

    # 미처리 작업이 남아있거나, 대기 중인 작업이 있거나, 중단된 작업이 있으면 계속
    while idx < len(indexed) or heap or current:

        # 현재 시각 기준으로 도착한 작업 모두 heap에 투입
        # heap 튜플: (task_type, duration, arrival, orig_idx)
        # → task_type 낮을수록(주요>부가), duration 짧을수록 먼저 pop됨
        while idx < len(indexed) and indexed[idx][1] <= time:
            task_type, arrival, duration, orig_idx = indexed[idx]
            heapq.heappush(heap, (task_type, duration, arrival, orig_idx))
            idx += 1

        # 선점당해 중단된 작업을 heap에 다시 넣어서 새 작업과 우선순위 경쟁
        if current:
            heapq.heappush(heap, current)
            current = None

        if heap:
            # 우선순위 가장 높은 작업 꺼냄
            task_type, remaining, arrival, orig_idx = heapq.heappop(heap)

            if idx < len(indexed):
                next_arrival = indexed[idx][1]
                # 다음 작업 도착 전까지만 실행 (선점 가능성 때문에)
                # ex) remaining=7, next_arrival-time=4 → 4시간만 실행
                run_time = min(remaining, next_arrival - time)
            else:
                # 더 이상 올 작업 없으면 남은 시간 전부 실행
                run_time = remaining

            time += run_time
            remaining -= run_time

            if remaining > 0:
                # 아직 남은 작업 → 선점당한 것으로 current에 보관
                # 다음 루프에서 heap에 재투입되어 경쟁
                current = (task_type, remaining, arrival, orig_idx)
            else:
                # 작업 완전히 완료 → 결과에 원본 인덱스 추가
                result.append(orig_idx)
        else:
            # heap이 비어있고 current도 없음
            # → 다음 작업 도착 시각으로 time 점프
            if idx < len(indexed):
                time = indexed[idx][1]

    return result

# 테스트
# 작업1: type2, 6시 도착, 7시간 소요
# 작업2: type2, 10시 도착, 1시간 소요
# time=6:  작업1 시작, 4시간 실행 후 time=10에 멈춤 (remaining=3)
# time=10: 작업2 도착, heap에서 duration 1 < 3 이므로 작업2 먼저
# time=11: 작업2 완료 → result=[2]
# time=14: 작업1 잔여(3시간) 완료 → result=[2,1]
tasks = [(2, 6, 7), (2, 10, 1)]
print(schedule(tasks))  # [2, 1]