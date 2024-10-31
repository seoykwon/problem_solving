#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> minHeap;
    int weight;

    // Read the weights and push them into the min-heap
    for (int i = 0; i < n; ++i)
    {
        cin >> weight;
        minHeap.push(weight);
    }

    int totalTime = 0;

    // Process the heap until we have only one monster left
    while (minHeap.size() > 1)
    {
        // Extract the two smallest elements
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();

        // Merge them and calculate the time taken for this merge
        int mergeTime = first + second;
        totalTime += mergeTime;

        // Insert the merged weight back into the heap
        minHeap.push(mergeTime);
    }

    cout << totalTime << endl;

    return 0;
}