#include <stdio.h>
#include <stdlib.h>

struct process{
	int pid, at, bt, wt, tt, ct, pri;
};

void main(){
	int n,i;
	printf("No. of Processes>> ");
	scanf("%d",&n);
	struct process p[n];
	int burstRemain[n];
	
	printf("\nPID\tAT\tBT\tPRI\n");
	for(i=0;i<n;i++){
		scanf("%d\t%d\t%d\t%d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].pri);
		burstRemain[i]=p[i].bt;
	}
		
	int* isCompleted = (int*) calloc(n,sizeof(int));
	
	int max, index, curtime=0, completed=0, j=0, prev=-2, len=0, tottt=0, totwt=0, pid[20], ct[20];
	
	while(completed<n){
		index=-1; max=-1;
		for(i=0;i<n;i++){
			if (p[i].at<=curtime && !isCompleted[i] && max<p[i].pri){
				index = i;
				max = p[i].pri;
			}
			
			if (p[i].pri == max){
				if (p[i].at<p[index].at){
					index = i;
					max = p[i].pri;
				}
			}
		}
		
		if (index!=-1){
			if (prev==curtime-1 && pid[j-1]==p[index].pid){
				ct[j-1]++;
				prev=curtime;
			}
			else{
				ct[j] = curtime+1;
				pid[j] = p[index].pid;
				j++;
				len++;
				prev=curtime;				
			}
			curtime++;
			burstRemain[index]--;
			
			if (burstRemain[index]==0){
				p[index].ct = curtime;
				p[index].tt = p[index].ct - p[index].at;
				p[index].wt = p[index].tt - p[index].bt;
				
				tottt+=p[index].tt;
				totwt+=p[index].wt;
				
				completed++;
				isCompleted[index]=1;
			}
			
		}
		else{
			if (prev==curtime-1 && pid[j-1]==-1){
				ct[j-1]++;
				prev=curtime;
			}
			else{
				ct[j]=curtime+1;
				pid[j]=-1;
				j++;
				len++;
				prev = curtime;
			}
			curtime++;
		}
	}
	
	printf("\nPID\tAT\tBT\tPRI\tCT\tTT\tWT\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tt, p[i].wt);
	}
	
	printf("\nGhant Chart\n");
	for(i=0;i<len;i++)
		printf("-------");
	printf("\n");
	for(i=0;i<len;i++){
		if (pid[i]!=-1)
			printf("  P%d  |", pid[i]);
		else
			printf(" IDLE |");
	}
	printf("\n");
	for(i=0;i<len;i++)
		printf("-------");
	printf("\n");
	printf("0      ");
	for(i=0;i<len;i++)
		printf("%d      ", ct[i]);
	printf("\n\n");
	
	printf("Avg. Turnaround Time: %.2f\n", (float)tottt/n);
	printf("Avg. Waiting Time: %.2f\n", (float)totwt/n);
}

Output:
No. of Processes>> 4

PID    AT    BT    PRI
1      0     8     2
2      1     4     1
3      2     9     3
4      3     5     2

PID    AT    BT    PRI   CT   TT   WT
1      0     8     2     17   17   9
2      1     4     1     5    4    0
3      2     9     3     26   24   15
4      3     5     2     12   9    4

Ghant Chart
-------------------------------------------
  P1  |  P2  |  P1  |  P4  |  P3  |
-------------------------------------------
0      1      5      12     17     26     

Avg. Turnaround Time: 13.50
Avg. Waiting Time: 7.00
