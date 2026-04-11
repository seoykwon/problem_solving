import heapq

def schedule(tasks):
    # 입력: (task_type, arrival, duration)
    # 원본 인덱스 보존 (1-indexed)
    indexed = [(task_type, arrival, duration, i+1) 
               for i, (task_type, arrival, duration) in enumerate(tasks)]
    indexed.sort(key=lambda x: x[1])  # 도착시간 기준 정렬

    heap = []
    time = 0
    idx = 0
    result = []
    current = None  # (task_type, remaining, arrival, original_idx)

    while idx < len(indexed) or heap or current:
        while idx < len(indexed) and indexed[idx][1] <= time:
            task_type, arrival, duration, orig_idx = indexed[idx]
            heapq.heappush(heap, (task_type, duration, arrival, orig_idx))
            idx += 1

        if current:
            heapq.heappush(heap, current)
            current = None

        if heap:
            task_type, remaining, arrival, orig_idx = heapq.heappop(heap)

            if idx < len(indexed):
                next_arrival = indexed[idx][1]
                run_time = min(remaining, next_arrival - time)
            else:
                run_time = remaining

            time += run_time
            remaining -= run_time

            if remaining > 0:
                current = (task_type, remaining, arrival, orig_idx)
            else:
                result.append(orig_idx)  # 완전히 끝난 작업만 기록
        else:
            if idx < len(indexed):
                time = indexed[idx][1]

    return result

# 테스트
tasks = [(2, 6, 7), (2, 10, 1)]
print(schedule(tasks))  # [2, 1]