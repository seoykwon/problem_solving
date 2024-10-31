#include <vector>
#include <utility> // for std::pair
using namespace std;

vector<int> solution(int brown, int yellow)
{
    int totalTiles = brown + yellow;

    for (int h = 3; h <= totalTiles; h++)
    {
        if (totalTiles % h == 0)
        {
            int w = totalTiles / h;
            // 갈색 타일 계산
            if (2 * (w + h) - 4 == brown)
            {
                return {w, h}; // 가로와 세로 반환
            }
        }
    }

    return {}; // 예외 처리 (이론상 도달하지 않음)
}
