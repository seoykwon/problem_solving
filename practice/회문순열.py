'''
회문순열
주어진 문자열이 회문(palindrome)의 순열인지 아닌지 확인하는 함수를 작성하라.
회문이란 앞으로 읽으나 뒤로 읽으나 같은 단어 혹은 구절을 의미하며,
순열이란 문자열을 재배치하는 것을 뜻한다. 
회문이 꼭 사전에 등장하는 단어로 제한될 필요는 없다.

회문이 되려면 -> 홀수 개인 문자가 최대 1개여야 함
짝수 길이: 모든 문자가 짝수 개
홀수 길이: 딱 1개 문자만 홀수 개 (가운데 자리)
'''

def solve():
    s1 = input()

    counts = {}
    for c in s1:
        counts[c] = counts.get(c, 0) + 1

    odd_count = sum(1 for v in counts.values() if v % 2 != 0)

    return odd_count <= 1

print(solve())

'''
XOR 동작원리
'a' 등장 1번 → bit 켜짐 (1) → 홀수
'a' 등장 2번 → bit 꺼짐 (0) → 짝수
'a' 등장 3번 → bit 켜짐 (1) → 홀수
'''

def solve():
    s1 = input()

    checker = 0
    for c in s1:
        bit = 1 << (ord(c) - ord('a'))
        checker ^= bit    # XOR: 홀수면 켜지고, 짝수면 꺼짐
    
    # 비트가 1개 이하로 켜져 있으면 True
    return checker == 0 or (checker & (checker - 1)) == 0

print(solve())