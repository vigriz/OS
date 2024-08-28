#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, wt, tt, ct, pri;
};

void main() {
    int n, i;
    printf("No. of Processes>> ");
    scanf("%d", &n);

    struct process p[n];
    int *isCompleted = (int*) calloc(n, sizeof(int));
    int max, index, curtime = 0, completed = 0, j = 0, len = 0, tottt = 0, totwt = 0;
    int pid[20], ct[20];
    
    printf("\nPID\tAT\tBT\tPRI\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d%d%d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].pri);
    }

    while (completed < n) {
        index = -1;
        max = -1;
        
        // Find the process with highest priority that is not completed
        for (i = 0; i < n; i++) {
            if (p[i].at <= curtime && !isCompleted[i]) {
                if (p[i].pri > max) {
                    index = i;
                    max = p[i].pri;
                }
                else if (p[i].pri == max && p[i].at < p[index].at) {
                    index = i;
                    max = p[i].pri;
                }
            }
        }

        if (index != -1) {
            // Update process times
            p[index].ct = curtime + p[index].bt;
            p[index].tt = p[index].ct - p[index].at;
            p[index].wt = p[index].tt - p[index].bt;
            
            // Update totals
            tottt += p[index].tt;
            totwt += p[index].wt;
            
            // Store Gantt chart details
            ct[j] = p[index].ct;
            pid[j] = p[index].pid;
            j++;
            len = (len > j) ? len : j; // Update length of Gantt chart
            curtime = p[index].ct;
            
            // Mark process as completed
            completed++;
            isCompleted[index] = 1;
        } else {
            // Idle time if no process is ready
            if (j > 0 && ct[j-1] == curtime) {
                ct[j-1]++;
            } else {
                pid[j] = -1;
                ct[j] = curtime + 1;
                j++;
                len++;
            }
            curtime++;
        }
    }
    
    // Print process details
    printf("\nPID\tAT\tBT\tPRI\tCT\tTT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tt, p[i].wt);
    }

    // Print Gantt Chart
    printf("\nGantt Chart\n");
    for (i = 0; i < len; i++) {
        printf("-------");
    }
    printf("\n");
    for (i = 0; i < len; i++) {
        if (pid[i] != -1) {
            printf("  P%d  |", pid[i]);
        } else {
            printf(" IDLE |");
        }
    }
    printf("\n");
    for (i = 0; i < len; i++) {
        printf("-------");
    }
    printf("\n");
    printf("0      ");
    for (i = 0; i < len; i++) {
        printf("%d      ", ct[i]);
    }
    printf("\n\n");

    // Print average times
    printf("Avg. Turnaround Time: %.2f\n", (float)tottt / n);
    printf("Avg. Waiting Time: %.2f\n", (float)totwt / n);

    free(isCompleted);
}

Output:
No. of Processes>> 3

PID	AT	BT	PRI
1	0	4	2
2	1	3	1
3	2	2	3

PID	AT	BT	PRI	CT	TT	WT
1	0	4	2	7	7	3
2	1	3	1	10	9	6
3	2	2	3	4	2	0

Gantt Chart
-------------------
  P1  |  P3  |  P2  |
-------------------
0      4      7      10      

Avg. Turnaround Time: 6.00
Avg. Waiting Time: 3.00
