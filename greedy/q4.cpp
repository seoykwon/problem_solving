#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Applicant
{
    int coding;
    int interview;
};

// Comparator for sorting applicants by coding rank
bool compareByCoding(const Applicant &a, const Applicant &b)
{
    return a.coding < b.coding;
}

int main()
{
    int n;
    cin >> n;

    vector<Applicant> applicants(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> applicants[i].coding >> applicants[i].interview;
    }

    // Sort applicants by coding test rank (ascending)
    sort(applicants.begin(), applicants.end(), compareByCoding);

    int count = 0;
    int minInterviewRank = INT_MAX;

    // Iterate through the sorted applicants
    for (int i = 0; i < n; ++i)
    {
        // If the current applicant's interview rank is better (smaller)
        // than the minimum interview rank seen so far, they are not dominated
        if (applicants[i].interview < minInterviewRank)
        {
            count++;
            minInterviewRank = applicants[i].interview;
        }
    }

    cout << count << endl;

    return 0;
}