#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    unordered_set<int> st;

    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;

        st.insert(tmp);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;

        if (st.find(tmp) != st.end())
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
}

// #################### 시간 초과 ############################
// 문제 조건에서 n과 m의 크기는 최대 100,000이다. 시간 제한 1초를 맞추기 위해 시간 복잡도를 고려해야한다.
// 선형 탐색을 선택할 경우 시간 복잡도는 O(n + m)으로 1초의 시간 제한을 넘기게 된다.
// 따라서 O(log N)의 시간복잡도를 가지는 이분 탐색을 선택했다.
// 이분 탐색을 선택할 경우 시간 복잡도는 O(n log m)이 되어 시간 제한을 맞출 수 있다.
#include <iostream>
#include <algorithm>
using namespace std;

int n, m;             // a_array 배열의 길이, 찾고자하는 정수 x의 개수
int a_array[1000000]; // 정수 a를 저장한 배열
int temp;

void binary_search(int x)
{
    int left = 0, mid = 0, right = n - 1;

    while (left <= right)
    {
        mid = (left + right) / 2;

        // 탈출 조건 : a_array에서 x를 찾은 경우
        if (a_array[mid] == x)
        {
            cout << 1 << "\n";
            return;
        }
        else if (a_array[mid] > x)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    // 이분 탐색이 끝날 때까지 x를 찾지 못했다면 0(false)를 출력한다.
    cout << 0 << "\n";

    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> a_array[i];
    }

    // 이분 탐색 알고리즘을 적용하기 위해 배열을 오름차순으로 정렬한다.
    sort(a_array, a_array + n);

    cin >> m;

    int x;
    for (int i = 0; i < m; i++)
    {
        cin >> x;
        binary_search(x);
    }

    return 0;
}