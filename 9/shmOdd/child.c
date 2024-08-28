//Compile this program with arguments -> ( -o child )

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

void main(int argc, char* argv[]){
	int n,i,shmid;
	int *shared_memory;
	
	n = atoi(argv[1]);
	
	shmid = shmget((key_t)110011,1024,0666);
	shared_memory = (int*)shmat(shmid,NULL,0);

	int j=0;
	for(i=1;i<2*n;i++){
		if (i%2!=0){
			shared_memory[j] = i;
			j++;
		}
	}
	
}


Output:
gcc -o parent Parent.c -lrt
gcc -o child Child.c -lrt
Enter n>> 5
1 3 5 7 9
Enter n>> 3
1 3 5
Enter n>> 1
1
