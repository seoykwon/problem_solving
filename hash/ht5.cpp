#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// 학생 정보를 저장하기 위한 구조체
struct Student
{
    string name;
    int language;
    int math;
    int science;
    int sociology;
};

int main()
{
    int N, M;
    cin >> N >> M;

    unordered_map<long long, Student> studentMap; // 학생 ID를 키로 사용

    // 학생 정보 입력 받기
    for (int i = 0; i < N; i++)
    {
        long long id;
        Student student;
        cin >> id >> student.name >> student.language >> student.math >> student.science >> student.sociology;
        studentMap[id] = student; // 맵에 학생 정보 저장
    }

    // 조회 요청 처리
    for (int i = 0; i < M; i++)
    {
        long long id;
        string subject;
        cin >> id >> subject;

        // 학생 정보 조회
        const Student &student = studentMap[id];
        int score = 0;

        // 과목에 따른 점수 선택
        if (subject == "language")
        {
            score = student.language;
        }
        else if (subject == "math")
        {
            score = student.math;
        }
        else if (subject == "science")
        {
            score = student.science;
        }
        else if (subject == "sociology")
        {
            score = student.sociology;
        }

        // 결과 출력
        cout << student.name << " " << score << endl;
    }

    return 0;
}
