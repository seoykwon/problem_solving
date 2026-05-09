'''
행렬 회전:
이미지를 표현하는 NxN 행렬이 있다.
이미지의 각 픽셀은 4바이트로 표현된다. 
이때, 이미지를 90도 회전시키는 메서드를 작성하라.
행렬을 추가로 사용하지 않고서도 할 수 있겠는가?
'''

def solve():
    N = int(input())
    board = [list(map(int, input().split())) for _ in range(N)]

    # zip(*board[::-1]) : 행을 뒤집은 뒤 전치 = 90도 회전
    rotated = [list(row) for row in zip(*board[::-1])]

    for row in rotated:
        print(row)


def solve():
    N = int(input())
    board = [list(map(int, input().split())) for _ in range(N)]

    # 1단계: 전치 (대각선 기준 뒤집기)
    for i in range(N):
        for j in range(i+1, N):
            board[i][j], board[j][i] = board[j][i], board[i][j]

    # 2단계: 각 행 뒤집기
    for i in range(N):
        board[i].reverse()

    for row in board:
        print(row)

solve()


'''
reverse(zip(*board))   # ❌ reverse는 없는 함수

reversed(zip(*board))  # ✅ 근데 iterator 반환
list(zip(*board))[::-1] # ✅ 리스트로 바로 사용 가능
'''