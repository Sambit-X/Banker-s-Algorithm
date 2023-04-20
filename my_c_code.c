#include <stdio.h>
#include <stdbool.h>
#define P 5
#define R 3

void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - allot[i][j];
        }
    }
}

int main() {
    int processes[P];
    int avail[R];
    int maxm[P][R];
    int allot[P][R];

    // Input processes 1D Array
    for (int i = 0; i < P; i++) {
        scanf("%d", &processes[i]);
    }

    // Input avail 1D Array
    for (int i = 0; i < R; i++) {
        scanf("%d", &avail[i]);
    }

    // Input maxm 2D Array
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &maxm[i][j]);
        }
    }
    // Input allot 2D Array
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    // Perform Bankers Algorithm for Deadlock Avoidance
    char ch;
    int need[P][R];
    calculateNeed(need, maxm, allot);
    bool finish[P] = { false };
    int work[R];
    int safeSeq[P];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == false) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (found == false) {
            ch='F';
        }
    }
    ch='T';

    if(ch=='T'){
        printf("Safe Sequence is Possible \n");
        for (int i = 0; i < P; i++) {
            printf("P%d", safeSeq[i]);
            if(i==P-1){
                break;
            }
            else
            {
                printf(">");
            }
        }
    }
    else{
        printf("Safe Sequence is not Possible");
    }
    return 0;
}
