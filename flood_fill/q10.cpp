#include <iostream>
#include <queue>

using namespace std;

int T, N, M;
int sy, sx;
int ty, tx;
int sword_y, sword_x;
int stick_y, stick_x;
int field[11][11];
int visited[11][11];
int visited2[11][11];
int hp;
int power = 0;
int ydir[] = {-1, 0, 1, 0};
int xdir[] = {0, -1, 0, 1};

struct node{
    int y;
    int x;
};

// pass target y and x as parameters as well
// then you first acquire tools
// after you reach to the devil 
void bfs(int y, int x){
    queue <node> q;
    q.push({y, x});
    visited[y][x] = 0;


    while(!q.empty()){
        node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M || field[ny][nx] == -1) continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;

            if (ny == sword_y && nx == sword_x && power == 0) {
                power += 5;
            }

            if (ny == ty && nx == tx && power > 0){
                while(hp > 0){
                    hp -= power;
                    visited[ny][nx] += 1;
                }

                return;
            }
        }
    }
}

void bfs2(int y, int x){
    queue <node> q;
    q.push({y, x});
    visited2[y][x] = 0;


    while(!q.empty()){
        node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M || field[ny][nx] == -1) continue;

            visited2[ny][nx] = visited2[now.y][now.x] + 1;

            if (ny == stick_y && nx == stick_x && power > 0) {
                power += 2;
            }

            if (ny == ty && nx == tx){
                if (power == 0){
                    return;
                }
                while(hp > 0){
                    hp -= power;
                    visited2[ny][nx] += 1;
                }

                return;
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N >> M;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                char tmp;
                cin >> tmp;

                if (tmp == 'Y')
                {
                    sy = i;
                    sx = j;
                    field[i][j] = 0;
                }
                else if (tmp == 'M')
                {
                    ty = i;
                    tx = j;
                    field[i][j] = 0;
                }
                else if (tmp == 'S')
                {
                    sword_y = i;
                    sword_x = j;
                    field[i][j] = 0;
                }
                else if (tmp == 'T')
                {
                    stick_y = i;
                    stick_x = j;
                    field[i][j] = 0;
                }
                else if (tmp == '_')
                {
                    field[i][j] = 0;
                }
                else if (tmp == 'x')
                {
                    field[i][j] = -1;
                }
                visited[i][j] = -1;
                visited2[i][j] = -1;
            }
        }
        cin >> hp;

        bfs(sy, sx);
        bfs2(sy, sx);

        if (visited[ty][tx] == -1 && visited2[ty][tx] == -1){
            cout << "#" << tc << " " << "the world is doomed" << endl;
        }
        else {
            cout << "#" << tc << " " << visited[ty][tx] << endl;
        }
        
    }

    

}