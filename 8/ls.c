#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

void main(int argc, char* argv[]){

	DIR *dp;
	struct dirent *dirp; //used for directory traversal
	
	if (argc<2){
		printf("Didn't pass directory!\n");
		exit(0);
	}
	
	if ((dp=opendir(argv[1]))==NULL){
		printf("Cannot access directory!\n");
		exit(0);
	}
	
	while(dirp=readdir(dp)){
		printf("%s\n",dirp->d_name);
	}
}


Output:
First, compile the program with:
gcc -o list_dir list_dir.c
To test the program, you need to pass a directory path as an argument. For instance:
./list_dir /path/to/directory
Assuming /path/to/directory contains the following files and subdirectories:
file1.txt
file2.txt
subdir1
subdir2
Example Command:
./list_dir /path/to/directory

file1.txt
file2.txt
subdir1
subdir2

