#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Initialize variables for Kadane's algorithm
    int currentSum = arr[0];
    int maxSum = arr[0];

    // Traverse the array
    for (int i = 1; i < n; i++) {
        // Choose the larger of (current element) or (currentSum + current element)
        currentSum = max(arr[i], currentSum + arr[i]);

        // Update the maximum sum
        maxSum = max(maxSum, currentSum);
    }

    cout << maxSum << endl;

    return 0;
}
