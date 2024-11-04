#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    // 그룹사 신입사원 ID 정보를 벡터로 저장
    unordered_map<char, vector<int>> mp = {
        {'A', {21, 15, 3}},
        {'B', {32}},
        {'C', {35, 36}},
        {'D', {14}},
        {'E', {15, 6, 34}}};

    // 그룹사 이름 입력 받기
    freopen("input.txt", "r", stdin);
    char cmp;
    cin >> cmp;

    // 해당 그룹사의 신입사원 ID 출력
    if (mp.find(cmp) != mp.end())
    {
        for (int id : mp[cmp])
        {
            cout << id << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "해당 그룹사는 존재하지 않습니다." << endl;
    }

    return 0;
}
