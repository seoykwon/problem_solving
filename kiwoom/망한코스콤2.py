def s(x):
    return sum(int(d) for d in str(x))

def find_next_x(x):
    sx = s(x)
    target = x - sx  # y + s(y) = target 만족하는 y 탐색
    
    if target <= 0:
        return None
    
    # 이분탐색으로 y 위치 파악
    lo, hi = 0, x
    while lo < hi:
        mid = (lo + hi) // 2
        if mid + s(mid) < target:
            lo = mid + 1
        else:
            hi = mid
    
    # s(y) 불연속성 때문에 근방 ±200 보정
    candidates = []
    for y in range(max(0, lo - 200), min(x, lo + 200)):
        if y + s(y) == target:
            candidates.append(y)
    
    if not candidates:
        return None
    
    # x' = s(x) + s(y) 중 최솟값
    return min(sx + s(y) for y in candidates)


def solve(x):
    visited = set()
    min_x = x
    
    while x not in visited:
        visited.add(x)
        
        next_x = find_next_x(x)
        
        if next_x is None:
            break
        
        min_x = min(min_x, next_x)
        x = next_x
    
    return min_x


# 테스트
print(solve(199))       # 19
print(solve(10000000))  # 작은 수로 수렴
print(solve(100))       # 결과 확인