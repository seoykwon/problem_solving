#include <iostream>
#include <string>
using namespace std;

char ch[9];
int map[10][10];
int path[10];

void input()
{
	cin >> ch;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			cin >> map[y][x];
		}
	}
}

void dfs(int now)
{
	cout << ch[now];

	for (int i = 0; i < 8; i++) {
		if (map[now][i] == 1) {
			dfs(i);
		}
	}
}

int main()
{
	input();
	path[0] = 0;

	dfs(0);

	return 0;
}