import sys
input = sys.stdin.readline

from collections import Counter

def sort_sequence(seq):
    filtered = [x for x in seq if x != 0]
    cnt = Counter(filtered)
    sorted_pairs = sorted(cnt.items(), key=lambda x: (x[1], x[0]))
    result = []
    for val, count in sorted_pairs:
        result.append(val)
        result.append(count)
    return result

def solve():
    r, c, k = map(int, input().split())

    A = []
    for i in range(3):
        A.append(list(map(int, input().split())))

    for t in range(101):
        rows = len(A)
        cols = max(len(row) for row in A)

        for row in A:
            while len(row) < cols:
                row.append(0)

        if r <= rows and c <= cols:
            if A[r-1][c-1] == k:
                print(t)
                return

        if t == 100:
            break

        rows = len(A)
        cols = max(len(row) for row in A)

        if rows >= cols:
            new_A = []
            for row in A:
                new_row = sort_sequence(row)
                new_A.append(new_row)
            max_len = min(max(len(row) for row in new_A), 100)
            for row in new_A:
                while len(row) < max_len:
                    row.append(0)
                del row[100:]
            A = new_A
        else:
            columns = []
            for j in range(cols):
                col = [A[i][j] if j < len(A[i]) else 0 for i in range(rows)]
                columns.append(col)

            new_columns = [sort_sequence(col) for col in columns]
            max_len = min(max(len(col) for col in new_columns), 100)
            for col in new_columns:
                while len(col) < max_len:
                    col.append(0)
                del col[100:]

            A = [[new_columns[j][i] for j in range(len(new_columns))] for i in range(max_len)]

    print(-1)

solve()