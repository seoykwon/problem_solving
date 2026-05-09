'''
URL화
문자열에 들어 있는 모든 공백을 '%20'으로 바꿔 주는 메서드를 작성하라
최종적으로 모든 문자를 다 담을 수 있을 만큼 충분한 공간이 이미 확보되어 있으며 문자열의 최종 길이가 함께 주어진다고 가정해도 된다
입력: "Mr John Smith" 13
출력: "Mr%20John%20Smith"
'''

def solve():
    line = input()          # "Mr John Smith 13"
    n = int(line.split()[-1])       # 마지막 토큰 = 숫자
    s1 = line[:-(len(str(n)) + 1)]  # 숫자 부분 제외한 앞 문자열

    s2 = ''
    for c in s1:
        if c == ' ':
            s2 += '%20'
        else:
            s2 += c

    print(s2)

solve()

s1.replace(' ', '%20')