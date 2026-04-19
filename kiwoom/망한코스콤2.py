def s(x):
    return sum(int(d) for d in str(x))

def find_y(x):
    sx = s(x)
    target = x - sx  # y + s(y) = target
    if target <= 0:
        return None

    lo, hi = 1, x
    while lo < hi:
        mid = (lo + hi) // 2
        if mid + s(mid) < target:
            lo = mid + 1
        else:
            hi = mid

    candidates = []
    for y in range(max(1, lo - 200), min(x, lo + 200)):
        if y + s(y) == target:
            candidates.append(y)

    return min(candidates) if candidates else None

def solve(x):
    visited = set()
    min_x = x

    while x not in visited:
        visited.add(x)
        y = find_y(x)
        if y is None:
            break
        x = abs(x - y)  # ✅ s(x) + s(y) 와 동일
        min_x = min(min_x, x)

    return min_x

print(solve(75))        # 75→21→12
print(solve(7))         # 7
print(solve(29999999))  # 빠르게 수렴