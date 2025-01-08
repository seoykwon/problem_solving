/**
 * (100+1+ | 01)+
 * 김동혁 박사는 다양한 전파 기록 중에서 위의 패턴을 지니는 전파를 가려내는 프로그램을 필요로 한다. 
 * 이를 수행할 수 있는 프로그램을 작성하라.
 */

#include <iostream>
#include <regex>

using namespace std;

int T;
string s;
regex pattern("(100+1+|01)+");

void solution() {
    cout << (regex_match(s, pattern) ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> T;

    while(T--) {
        cin >> s;
        solution();
    }

    return 0;
}

// ##############################################
#include <iostream>
#include <vector>
using namespace std;

string res = "NO";// 결과 출력값

void dfs(string tmp, string& answer, int size, string choosed) {
	if (res == "YES" || size > answer.size() || answer.substr(0, size) != tmp) {
		return ;// 이미 결과를 찾았거나, 사이즈가 넘어갔거나, 문자열이 달라졌다면
	}
	if (tmp == answer && choosed != "100") {// 문자열의 끝이 100 일수는 없다.
		res = "YES";
		return ;
	}
	if (choosed == "") {
		dfs(tmp+"01", answer, size+2, "");
		dfs(tmp+"100", answer, size+3, "100");
	} else if (choosed == "100") {
		dfs(tmp+"1", answer, size+1, "1");
		dfs(tmp+"0", answer, size+1, "100");
	} else if (choosed == "1") {
		dfs(tmp+"1", answer, size+1, "1");
		dfs(tmp+"01", answer, size+2, "");
		dfs(tmp+"100", answer, size+3, "100");
	}
}

int main() {
	int t;
	cin >> t;
	string input, answer;

	while (t--) {
		cin >> input;
		dfs("", input, 0, "");
		cout << res << "\n";
		res = "NO";
	}
}