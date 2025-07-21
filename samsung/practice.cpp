#include <stdio.h>
#include <stdbool.h>

#define MAX (20000 + 10000 + 500)
#define INF (1000000000)

#define INIT (100)
#define CREATE (200)
#define REMOVE (300)
#define FIND (400)

int Q;
int N;

int house[MAX];
bool isBroken[MAX];
int hcnt = 0;

void input() {
    scanf("%d", &N);

    hcnt = 1;
    for (int i = 0; i < N; i++){
        int x;
        scanf("%d", &x);
        house[hcnt++] = x;
    }

    for (int i = 0; i < MAX; i++){
        isBroken[i] = false;
    }
}

void createAntHouse(int pos){
    house[hcnt++] = pos;
}