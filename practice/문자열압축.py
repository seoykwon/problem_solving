'''
문자열 압축
반복되는 문자의 개수를 세는 방식의 기본적인 문자열 압축 메서드를 작성하라.
예를 들어 문자열 aabccccaaa를 압축하면 a2b1c5a3이 된다. 만약 압축된 문자열의 길이가 기존 문자열의 길이보다 길다면 기존 문자열을 반환해야 한다. 
문자열은 대소문자 알파벳으로만 이루어져 있다.
'''

def solve():
    s1 = input()

    prev = s1[0]
    cnt = 1

    s2 = ''
    for i in range(1, len(s1)):
        if s1[i] == prev:
            cnt += 1
        else:
            s2 += prev + str(cnt)
            cnt = 1
            prev = s1[i]
    
    s2 += prev + str(cnt)

    return s1 if len(s2) >= len(s1) else s2

print(solve())

