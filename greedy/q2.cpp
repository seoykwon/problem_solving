#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, L;
    cin >> N >> L;

    vector<int> leaks(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> leaks[i];
    }

    // Sort the leak positions
    sort(leaks.begin(), leaks.end());

    int tapesNeeded = 0;
    int i = 0;

    while (i < N)
    {
        // Place a tape starting at the current leak
        int tapeStart = leaks[i];
        tapesNeeded++;

        // Move to the first leak not covered by this tape
        while (i < N && leaks[i] < tapeStart + L)
        {
            i++;
        }
    }

    cout << tapesNeeded << endl;

    return 0;
}