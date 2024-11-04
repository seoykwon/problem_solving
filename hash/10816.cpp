#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    unordered_map<int, int> mp;

    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;

        if (mp.find(tmp) != mp.end())
        {
            mp[tmp]++;
        }
        else
        {
            mp.insert({tmp, 1});
        }
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;

        cout << mp[tmp] << " ";
    }
}

// ################ 시간 초과 ####################
// 이분 탐색을 이용한 풀이는 Algorithm STL의 upper_bound, lower_bound을 사용한 풀이가 있었다.
// 이분 탐색을 위해서 오름차순 정렬을 해주고, upper_bound와 lower_bound을 이용해서 결과를 출력했다.
// - upper_bound : 찾고자 하는 값의 다음 값이 최초로 나타나는 위치
// - lower_bound : 찾고자 하는 값 이상이 처음 나타나는 위치

// 즉, 1 2 4 4 6 7에서
// lower_bound(~,~,4)의 결과 : 3 (4 이상의 값이 처음 나타나는 위치)
// upper_bound(~,~,4)의 결과 : 5 (4를 초과하는 값이 처음 나타나는 위치)를 이용해서 
// 사이의 값을 빼주면 2가 나오고 이것은 결국 저장된 4의 개수가 된다.
#include <iostream>
#include <algorithm>

using namespace std;

int arr[500002];
int N, M, card;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> card;
        arr[i] = card;
    }
    sort(arr, arr + N);

    cin >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> card;
        cout << upper_bound(arr, arr + N, card) - lower_bound(arr, arr + N, card) << " ";
    }
}