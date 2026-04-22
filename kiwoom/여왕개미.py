# dic[번호] = [좌표, prev, next]
# dic[0] 은 원형 연결 리스트의 더미 노드
# dic[0] = [0(여왕 좌표=0), 마지막 집 번호, 첫 집 번호]

def check(t, r):
    left = t
    ori_r = r
    cur_num = dic[0][2]
    
    while r > 0:
        # 개미 한마리 배치
        r -= 1

        left = t

        # 다음 위치까지의 거리
        while True:
            next_num = dic[cur_num][2]

            if next_num == 0 and left >= 0:
                return True
            length = dic[next_num][0] - dic[cur_num][0]
            left -= length
            if left >= 0:
                cur_num = next_num
            else:
                cur_num = next_num
                break

    return False

q = int(input())
dic = dict()
for _ in range(q):
    query = list(map(int, input().split()))
    op = query[0]

    if op == 100:
        dic[0] = [0] * 3
        dic[0][2] = 1

        n = query[1]
        dic[0][1] = n
        for i, x in enumerate(query[2:]):
            dic[i+1] = [0]*3
            dic[i+1][0] = x
            dic[i+1][1] = i
            dic[i+1][2] = (i+2)%(n+1) # next (n번의 next는 0 = 여왕으로 돌아감)

    elif op == 200:
        n += 1
        p = query[1]
        dic[n] = [0]*3
        dic[n][0] = p

        b = dic[0][1]   # 현재 '마지막 집'의 번호 (여왕의 prev)
        dic[b][2] = n   # 기존 마지막 집의 next = n
        dic[n][1] = b   # n의 prev = 기존 마지막 집
        dic[0][1] = n   # 여왕의 prev = n (n이 새 '마지막'이 됨)
        dic[n][2] = 0   # n의 next = 여왕 (wrap)

    elif op == 300:
        q = query[1]
        b = dic[q][1]
        a = dic[q][2]
        dic[b][2] = dic[q][2]
        dic[a][1] = dic[q][1]
        del dic[q]
    
    elif op == 400:
        r = query[1]
        left = 0
        right = int(1e9)
        answer = 0

        while left <= right:
            mid = (left + right) // 2
            test = check(mid, r)

            if test:
                answer = mid
                right = mid - 1
            else:
                left = mid + 1
        
        print(answer)