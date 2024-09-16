#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 8; // 바둑판 크기
const char EMPTY = '_';
const char BLACK = '@';
const char WHITE = 'O';

// 8방향 (상, 하, 좌, 우, 좌상, 좌하, 우상, 우하)
int dx[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int dy[8] = {0, 0, -1, 1, -1, -1, 1, 1};

// 바둑판 상태 출력 함수
void printBoard(vector<vector<char>> &board)
{
    for (int i = SIZE - 1; i >= 0; i--)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[j][i];
        }
        cout << endl;
    }
}

// 좌표가 유효한지 확인하는 함수
bool isValid(int x, int y)
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// 특정 위치에 돌을 놓고 규칙에 따라 돌을 뒤집는 함수
bool placeStone(vector<vector<char>> &board, int x, int y, char currentStone)
{
    bool flipped = false; // 돌이 뒤집혔는지 여부
    char opponentStone = (currentStone == BLACK) ? WHITE : BLACK;

    // 8방향 탐색
    for (int dir = 0; dir < 8; dir++)
    {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        vector<pair<int, int>> toFlip;

        // 해당 방향에 상대방 돌이 있는지 확인
        while (isValid(nx, ny) && board[nx][ny] == opponentStone)
        {
            toFlip.push_back({nx, ny});
            nx += dx[dir];
            ny += dy[dir];
        }

        // 상대 돌을 지나서 같은 색 돌이 있는지 확인
        if (isValid(nx, ny) && board[nx][ny] == currentStone)
        {
            // 돌 뒤집기
            for (auto p : toFlip)
            {
                board[p.first][p.second] = currentStone;
            }
            if (!toFlip.empty())
            {
                flipped = true;
            }
        }
    }

    return flipped;
}

// 게임 실행 함수
void playGame(int n, vector<pair<int, int>> &moves)
{
    vector<vector<char>> board(SIZE, vector<char>(SIZE, EMPTY));

    char currentStone = BLACK; // 흑돌이 먼저 시작

    for (int i = 0; i < n; i++)
    {
        int x = moves[i].first;
        int y = moves[i].second;

        // 돌을 놓고 뒤집기
        board[x][y] = currentStone;
        placeStone(board, x, y, currentStone);

        // 다음 차례는 상대방 돌
        currentStone = (currentStone == BLACK) ? WHITE : BLACK;
    }

    // 최종 바둑판 출력
    printBoard(board);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n; // 기보의 수 입력

    vector<pair<int, int>> moves(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y; // 좌표 입력
        moves[i] = {x, y};
    }

    // 게임 실행
    playGame(n, moves);

    return 0;
}

// ######################
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

char MAP[10][10];
char dol[] = {'@', 'O'};

int ydir[] = {0, 0, 1, -1, 1, 1, -1, -1};
int xdir[] = {1, -1, 0, 0, 1, -1, 1, -1};

struct Node
{
    int y;
    int x;
};

vector<Node> path;

void check(int y, int x)
{
    char nowdol = MAP[y][x];
    for (int i = 0; i < 8; i++)
    {
        int dist = 1;
        int flag = 0;
        path.clear();
        while (true)
        {
            int ny = y + ydir[i] * dist;
            int nx = x + xdir[i] * dist;
            if (ny < 0 || nx < 0 || ny >= 8 || nx >= 8)
                break;
            if (MAP[ny][nx] == '_')
                break;
            if (MAP[ny][nx] != nowdol)
            {
                path.push_back({ny, nx});
                flag = 1;
            }
            if (MAP[ny][nx] == nowdol && flag == 1)
            {
                for (int i = 0; i < path.size(); i++)
                {
                    MAP[path[i].y][path[i].x] = nowdol;
                }
                break;
            }
            if (MAP[ny][nx] == nowdol && flag == 0)
                break;
            dist++;
        }
    }

    // cout << '\n';
    // for (int i = 0; i < 8; i++) {
    //	for (int j = 0; j < 8; j++)
    //		cout << MAP[i][j];
    //	cout << '\n';
    // }
}

int main()
{

    // freopen("input.txt", "r", stdin);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            MAP[i][j] = '_';

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        char now = dol[i % 2];
        y = 7 - y;
        MAP[y][x] = now;
        check(y, x);
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << MAP[i][j];
        cout << '\n';
    }
}