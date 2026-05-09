'''
순열 확인
문자열 두 개가 주어졌을 때 이 둘이 서로 순열 관계에 있는지 확인하는 메서드를 작성하라
'''

from collections import defaultdict

def solve():
    s1, s2 = map(str, input().split())
    if len(s1) != len(s2):
        return False

    # letters = {}
    letters = defaultdict(int)
    for c in s1:
        letters[c] += 1;

    for c in s2:
        letters[c] -= 1;
        if letters[c] < 0:
            return False
        
    return True

print(solve())