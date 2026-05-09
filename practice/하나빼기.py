'''
하나빼기
문자열을 편집하는 방법에는 세 가지 종류가 있다. 문자 삽입, 문자 삭제, 문자 교체.
문자열 두 개가 주어졌을 때, 문자열을 같게 만들기 위한 편집 횟수가 1회 이내인지 확인하는 함수를 작성하라

'''

def solve():
    s1, s2 = input().split()

    if abs(len(s1) - len(s2)) > 1:
        return False
    
    # 교체 케이스
    if len(s1) == len(s2):
        diff = sum(1 for a, b in zip(s1, s2) if a != b)
        return diff <= 1
    
    # 삽입/삭제 케이스 (긴 문자열 기준으로 비교)
    longer = s1 if len(s1) > len(s2) else s2
    shorter = s2 if len(s1) > len(s2) else s1

    i, j = 0, 0
    diff = 0
    while i < len(longer) and j < len(shorter):
        if longer[i] != shorter[j]:
            diff += 1
            i += 1 # 긴 쪽만 앞으로
        else:
            i += 1
            j += 1
    
    return diff <= 1

print(solve())