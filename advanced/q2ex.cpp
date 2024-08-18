#include <iostream>
#include <vector>

using namespace std;

int t, n;
int board[51][51];
int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};  // down, up, right, left

struct Position {
    int y, x;
};

Position p;

bool isInBounds(int y, int x) {
    return y >= 0 && y < n && x >= 0 && x < n;
}

int dfs(Position pos, int movesLeft) {
    if (movesLeft == 0) return 0;

    int maxEaten = 0;

    for (int d = 0; d < 4; d++) {
        int ny = pos.y;
        int nx = pos.x;
        bool jumped = false;

        while (true) {
            ny += directions[d][0];
            nx += directions[d][1];

            if (!isInBounds(ny, nx)) break;

            if (board[ny][nx] != 0) {
                if (jumped) break; // If it's the second non-empty cell, stop
                jumped = true; // We jump over the first piece
            } else if (jumped && board[ny][nx] == 1) { // Find a pawn after a jump
                // Eat the pawn
                board[ny][nx] = 0;
                // Recursively explore further moves from this position
                maxEaten = max(maxEaten, 1 + dfs({ny, nx}, movesLeft - 1));
                // Restore the pawn for other paths
                board[ny][nx] = 1;
                break;
            }
        }
    }

    return maxEaten;
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            if (board[i][j] == 2) {
                p = {i, j};
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        input();
        int result = dfs(p, 3);
        cout << "#" << tc << " " << result << endl;
    }

    return 0;
}
