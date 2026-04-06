# 나선형 코드를 이미 알고 있고, 일차원 배열 관점에서 풀이해야겠다
# board: 안에서부터 밖으로 돌아나오면서 1부터 N*N까지 값을 차례로 넣어줌
# board1d: board의 값에 해당하는 인덱스에 구슬 번호를 넣음
'''
문제에서 구슬을 파괴하고 빈칸이 생기면 구슬을 앞당기고 하는 과정을 2차원 배열에서 한다면 구현하기
매우 까다롭다. 하지만 1차원 배열에서 빈칸을 앞당기는 (0을 제외하는) 과정은 쉽다.
참고로 배열의 값을 없앤 만큼 배열 크기가 줄어들기 때문에 기존 N*N 크기를 맞추기 위해
extend() 함수를 사용한다.
'''
import sys
# sys.stdin = open('input.txt', 'r')
input = sys.stdin.readline

N, M = map(int, input().split())
board = []
board1D=[0]
# ↑, ↓, ←, →가 있고, 정수 1, 2, 3, 4
d=[(-1,0),(1,0),(0,-1),(0,1)]
result=0
for _ in range(N):
    board.append(list(map(int, input().split())))

magics = []
for _ in range(M):
    magics.append(list(map(int, input().split())))


def print_board():
    global board
    for i in range(len(board)):
        print(board[i])

def make1Array():
    global board, board1D
    d = [(0, -1), (1, 0), (0, 1), (-1, 0)] #local variable
    y = N // 2
    x = N // 2
    num = 0
    dist = 1
    move_count = 0  # 2가 되면 dist+1
    d_idx = 0  # 서:0, 남:1, 동:2, 북:3
    while True:
        for _ in range(dist):
            dy, dx = d[d_idx]
            y = dy + y
            x = dx + x
            if (y, x) == (0, -1):
                return
            board1D.append(board[y][x])
            num += 1
            board[y][x]=num # 기존 board에는 순서 번호를 덮어씌운다

        d_idx = (d_idx + 1) % 4
        move_count += 1
        if move_count == 2:
            dist += 1
            move_count = 0

def destroy(magic):
    d_idx,s=magic
    # print(d_idx,s)
    dy,dx=d[d_idx-1]
    y,x=N//2,N//2 # 상어의 위치
    for i in range(s):
        Y=y+dy
        X=x+dx
        # print(Y,X,board[Y][X])
        if 0<=Y<N and 0<=X<N:
            board1D[board[Y][X]]=0
            y=Y
            x=X
        else:
            break
            
def move_balls():
    global board1D
    new_board1d=[0]
    for i in range(1,N*N):
        if board1D[i]!=0:
            new_board1d.append(board1D[i])
    new_board1d.extend([0]*((N*N)-len(new_board1d)))
    board1D=new_board1d[:]

def ball_explosion():
    global result
    flag=False # 구슬이 하나도 파괴되지 않은 경우 false 반환
    cnt=0
    start_idx=0 # 현재 연속하고 있느 구슬의 첫 인덱스
    ball_num =0 # 현재 연속하고 있는 구슬의 번호 (처음엔 0으로 초기화)
    # 구슬은 1,2,3번이 존재
    for i in range(1,N*N):
        if board1D[i]==ball_num:
            cnt+=1
        else:
            if cnt>=4:
                flag=True
                for j in range(start_idx,i):
                    board1D[j]=0
                result+=ball_num*(i-start_idx)
            start_idx=i
            ball_num=board1D[i]
            cnt=1 # 새로 시작하니까 cnt 1 (현재 값 포함하므로)
    return flag

def grouping_balls():
    global board1D
    cnt = 0
    ball_num = 0  # 현재 연속하고 있는 구슬의 번호 (처음엔 0으로 초기화)
    grouping=[0]
    for i in range(1, N * N):
        if board1D[i]!=ball_num:
            if cnt:
                grouping.extend([cnt,ball_num])
            ball_num=board1D[i]
            cnt=1
        else:
            cnt+=1
    if len(grouping)>N*N:
        grouping=grouping[:N*N]
    elif len(grouping)<N*N:
        grouping.extend([0]*(N*N-len(grouping)))
    board1D=grouping[:]

#init
make1Array()
for i in range(M):
    # print_board()
    # print(board1D)
    destroy(magics[i])
    # print_board()
    # print(board1D,5)
    move_balls()
    # print(board1D)
    while True:
        if not ball_explosion():
            break
        move_balls()
    # print(board1D)
    grouping_balls()
    # print(board1D)
print(result)