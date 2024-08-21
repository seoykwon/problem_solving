#include <iostream>
#include <algorithm>
using namespace std;

bool condition(long long num)
{
    // num 검증~!!
    // 1234567890의 제곱근 정수부
    if (num * num >= 1234567890)
        return true;
    return false;
}

int main()
{

    // 기본 binary search
    // 정렬된 데이터에서 탐색범위를 반씩 줄여가면서
    // 특정값을 빠르게 찾는 알고리즘

    int arr[10] = {2, 2, 2, 2, 2, 2, 2, 2, 4, 4};
    // 1. sort 가 필수~!!
    sort(arr, arr + 10);

    // 2. upper_bound()
    //  target == 2 target 보다 큰 숫자가 등장하는 위치 찾기
    //  target보다 큰 값이 어디서부터 시작인가?

    /*int left = 0;
    int right = 9;
    int target = 2;
    int ret = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) {
            left = mid + 1;
        }
        else if (arr[mid] > target) {
            ret = mid;
            right = mid - 1;
        }
    }
    cout << ret << " ";*/

    // 3. lower_bound
    //  target이상의 값이 시작되는 지점 결과 0

    /*int left = 0;
    int right = 9;
    int ret = 0;
    int target = 2;
    while (left <= right) {

        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else if (arr[mid] >= target) {
            ret = mid;
            right = mid - 1;
        }
    }
    cout << ret;*/
    // 2.
    // int left = 0;
    // int right = 9;
    // int target = 15;
    // int ret = 0;
    // while (left <= right) {
    //	int mid = (left + right) / 2; //중간값을 임의로 정하고,
    //	if (arr[mid] > target) {
    //		right = mid - 1;
    //	}
    //	else if (arr[mid] < target) {
    //		left = mid + 1;
    //	}
    //	else if (arr[mid] == target) {
    //		ret = mid;
    //		break;
    //	}
    // }

    // parametric search
    // 범위를 좁혀가면서 답을 구한다.
    // 최상위급 난이도
    // 조건에 따라서 범위를 좁힘.

    int N = 1234567890;
    // 제곱근의 정수부를 구하는 문제
    // 답 : 35136
    // 하나의 정답 35000
    //  condition() OK
    // 더 나은 정답은 없을까?

    int left = 0;
    int right = 100000000;
    int ret = 0;

    while (left <= right)
    {
        // int mid = (left + right) / 2;
        int mid = right - (right - left) / 2; // overflow
        if (condition(mid))
        {
            ret = mid; // 정답을 저장하고, 더나은 정답을 찾는다~!!
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    cout << ret - 1;
}