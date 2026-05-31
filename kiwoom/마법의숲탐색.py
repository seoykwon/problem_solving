import sys
sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

R, C, K = map(int, input().split())
unit = [list(map(int, input().split())) for _ in range(K)]
arr = [[1]+[0]*C+[1] for _ in range(R+3)] + [[1]*(C+2)]
exit_set = set()

# 상 우 하 좌 (동쪽: 시계방향)
di = [-1, 0, 1, 0]
dj = [0, 1, 0, -1]

def bfs(si, sj):
    q = []
    v = [[0]*(C+2) for _ in range(R+4)]
    mx_i = 0

    q.append((si, sj))
    v[si][sj] = 1

    while q:
        ci, cj = q.pop(0)
        mx_i = max(mx_i, ci)

        for di,dj in ((-1,0),(1,0),(0,-1),(0,1)):
            ni,nj = ci+di, cj+dj
            if v[ni][nj] == 0 and (arr[ci][cj]==arr[ni][nj] or ((ci,cj) in exit_set and arr[ni][nj]>1)):
                q.append((ni, nj))
                v[ni][nj] = 1

    return mx_i-2

ans = 0
num = 2

for cj, dr in unit:
    ci=1

    while True:
        if arr[ci+1][cj-1]+arr[ci+2][cj]+arr[ci+1][cj+1]==0:
            ci += 1
        elif (arr[ci-1][cj-1]+arr[ci][cj-2]+arr[ci+1][cj-1]+arr[ci+1][cj-2]+arr[ci+2][cj-1])==0:
            ci+=1
            cj-=1
            dr=(dr-1)%4
        elif (arr[ci-1][cj+1]+arr[ci][cj+2]+arr[ci+1][cj+1]+arr[ci+1][cj+2]+arr[ci+2][cj+1])==0:
            ci+=1
            cj+=1
            dr=(dr+1)%4
        else:
            break

    if ci < 4:
        arr = [[1]+[0]*C+[1] for _ in range(R+3)] + [[1]*(C+2)]
        exit_set = set()
        num = 2

    else:
        arr[ci+1][cj] = arr[ci-1][cj] = num
        arr[ci][cj-1:cj+2] = [num]*3
        num +=1

        exit_set.add((ci+di[dr], cj+dj[dr]))
        ans += bfs(ci, cj)

print(ans)