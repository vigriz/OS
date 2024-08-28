#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, tt, wt, ct;
};

void main() {
    int n, i;
    printf("No. of processes: ");
    scanf("%d", &n);
    struct process p[n];
    int burstRemain[n];

    printf("\nPID\tAT\tBT\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
        burstRemain[i] = p[i].bt;
    }

    int *isCompleted = (int *)calloc(n, sizeof(int));
    int curtime = 0, completed = 0, min, index;
    float tottt = 0, totwt = 0;

    while (completed < n) {
        index = -1;
        min = 9999;
        for (i = 0; i < n; i++) {
            if (p[i].at <= curtime && !isCompleted[i] && burstRemain[i] < min) {
                min = burstRemain[i];
                index = i;
            }
        }

        if (index != -1) {
            burstRemain[index]--;
            curtime++;

            if (burstRemain[index] == 0) {
                p[index].ct = curtime;
                p[index].tt = p[index].ct - p[index].at;
                p[index].wt = p[index].tt - p[index].bt;

                tottt += p[index].tt;
                totwt += p[index].wt;

                completed++;
                isCompleted[index] = 1;
            }
        } else {
            curtime++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
    }

    printf("Avg. Turnaround Time: %.2f\n", tottt / n);
    printf("Avg. Waiting Time: %.2f\n", totwt / n);

    free(isCompleted);
}

Output: 
No. of processes: 4

PID    AT    BT
1      0     6
2      1     8
3      2     7
4      3     3

PID    AT    BT    CT    TT    WT
1      0     6     6     6     0
2      1     8     17    16    8
3      2     7     19    17    10
4      3     3     10    7     4

Avg. Turnaround Time: 11.50
Avg. Waiting Time: 5.50
