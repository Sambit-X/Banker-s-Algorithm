#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - allot[i][j];
        }
    }
}

bool isSafe(int processes[P], int avail[R], int maxm[P][R], int allot[P][R]) {
    int need[P][R];

    calculateNeed(need, maxm, allot);

    bool finish[P] = { false };

    int safeSeq[P];

    int work[R];
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

                    // Add this process to safe sequence.
                    safeSeq[count++] = p;

                    // Mark this p as finished
                    finish[p] = true;

                    found = true;
                }
            }
        }

        if (found == false) {
            printf("System is not in safe state.\n");
            return false;
        }
    }

    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSeq[i]);
    }

    return true;
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

    isSafe(processes, avail, maxm, allot);

    return 0;
}
