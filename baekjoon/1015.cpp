#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<int,int>> A(n);
	vector<int> P(n);
	for (int i=0; i<n; i++) {
		cin >> A[i].first;
		A[i].second = i;// 정렬 했을 때 원래 몇번째 배열이 었는지
	}
	sort(A.begin(), A.end());
	for (int i=0; i<n; i++) {
		P[A[i].second] = i;
	}
	for (auto r : P) cout << r << " ";
}