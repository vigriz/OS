#include <stdio.h>
#include <stdlib.h>

struct pcb {
    int pid, at, bt, ct, tt, wt;
};

int n;
int Q[20], f = -1, r = -1;

void enqueue(int index) {
    if (f == -1) f++;
    r = (r + 1) % n;
    Q[r] = index;
}

int dequeue() {
    int a = f;
    if (f == r) {
        f = r = -1;
    } else {
        f = (f + 1) % n;
    }
    return Q[a];
}

int isEmpty() {
    return f == -1;
}

int main() {
    printf("Enter num. of processes >> ");
    scanf("%d", &n);

    struct pcb p[n];
    int bt[n], qt;

    printf("PID  AT  BT\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
        bt[i] = p[i].bt;
    }

    printf("Enter time quantum >> ");
    scanf("%d", &qt);

    int* inqueue = (int*)calloc(n, sizeof(int));
    int completed = 0, curtime = 0, index, tottt = 0, totwt = 0;
    int pid[40], ct[40], len = 0, j = 0;

    // Sorting based on arrival time
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (p[j].at > p[j + 1].at) {
                struct pcb temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;

                int t = bt[j + 1];
                bt[j + 1] = bt[j];
                bt[j] = t;
            }
        }
    }

    if (p[0].at != 0) {
        pid[j] = -1;
        ct[j] = p[0].at;
        ++j;
        ++len;
    }

    // Putting first arrived process in queue
    enqueue(0);
    inqueue[0] = 1;

    while (completed != n) {
        if (!isEmpty()) {
            index = dequeue();

            if (p[index].bt > qt) {
                p[index].bt -= qt;
                curtime += qt;
            } else {
                curtime += p[index].bt;
                p[index].bt = 0;

                p[index].ct = curtime;
                p[index].tt = p[index].ct - p[index].at;
                p[index].wt = p[index].tt - bt[index];

                tottt += p[index].tt;
                totwt += p[index].wt;

                ++completed;
            }
        } else {
            ++curtime;
        }

        if (j > 0 && p[index].pid == pid[j - 1]) {
            ct[j - 1] = curtime;
        } else {
            ct[j] = curtime;
            pid[j] = p[index].pid;
            ++j;
            ++len;
        }

        for (int i = 0; i < n && p[i].at <= curtime; ++i) {
            if (p[i].bt > 0 && !inqueue[i]) {
                enqueue(i);
                inqueue[i] = 1;
            }
        }

        if (p[index].bt > 0) enqueue(index);
    }

    printf("\nPID\tAT\tBT\tCT\tTT\tWT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, bt[i], p[i].ct, p[i].tt, p[i].wt);
    }

    printf("\n\nGantt chart >> \n");
    for (int i = 0; i < len; ++i) printf("-------");
    printf("\n");
    for (int i = 0; i < len; ++i) {
        if (pid[i] != -1) printf("  P%d  |", pid[i]);
        else printf(" IDLE |");
    }
    printf("\n");
    for (int i = 0; i < len; ++i) printf("-------");
    printf("\n0     ");
    for (int i = 0; i < len; ++i) {
        printf("%d     ", ct[i]);
    }

    printf("\n\nAvg turn around time >> %.2f\n", (float)tottt / n);
    printf("Avg waiting time >> %.2f\n", (float)totwt / n);

    free(inqueue);
    return 0;
}


Output:
Enter num. of processes >> 4

PID  AT  BT
1    0   5
2    1   4
3    2   2
4    3   1

Enter time quantum >> 2

PID   AT   BT   CT   TT   WT
1     0    5    10   10   5
2     1    4    12   11   7
3     2    2    7    5    3
4     3    1    6    3    2

Gantt chart >>
-----------------------------------
  P1  |  P2  |  P3  |  P4  |  P1  |  P2  |
-----------------------------------
0     2     4     6     7     9     12

Avg turn around time >> 7.25
Avg waiting time >> 4.25
