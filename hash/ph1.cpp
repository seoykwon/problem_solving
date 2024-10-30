#include <vector>
#include <set>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;

    int half = nums.size() / 2;

    set<int> s(nums.begin(), nums.end());
    int kind = s.size();

    if (half < kind)
        answer = half;
    else
        answer = kind;

    return answer;
}