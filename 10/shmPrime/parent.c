//Include -lrt while compiling

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

void main(int argc, char* argv[]){
	
	if (argc<2){
		printf("Didn't pass range\n");
		exit(0);
	}
	
	int fd, i, j,flag;
	int* shared_memory;
	
	fd = shm_open("chandan", O_CREAT|O_RDWR , 0666);
	ftruncate(fd,1024);
	shared_memory = (int*) mmap(NULL,1024, PROT_WRITE, MAP_SHARED, fd, 0);
	
	if (fork()==0){
		execlp("./child", "child", 	argv[1], argv[2], NULL);	
	}
	else{
		wait(NULL);
		int i=0;
		while(shared_memory[i]!=0){
			printf("%d ",shared_memory[i++]);
		}
		printf("\n");
		shm_unlink("chandan");
	}
}

Output:
gcc -o parent Parent.c -lrt
gcc -o child Child.c -lrt
./parent 10 30
./parent 10 30
11 13 17 19 23 29
./parent 5 15
5 7 11 13
./parent 1 10
2 3 5 7
