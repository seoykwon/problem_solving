#include <string>
#include <vector>

using namespace std;

int visited[1001] = {
    0,
};
int answer = 0;

void dfs(int start, int num, vector<int> numbers, int target)
{
    if (start == numbers.size() - 1)
    {
        if (num == target)
        {
            answer++;
        }
        return;
    }

    dfs(start + 1, num + numbers[start + 1], numbers, target);
    dfs(start + 1, num - numbers[start + 1], numbers, target);
}

int solution(vector<int> numbers, int target)
{

    dfs(0, numbers[0], numbers, target);

    dfs(0, -numbers[0], numbers, target);

    return answer;
}