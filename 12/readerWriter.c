#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

pthread_mutex_t mutex;
sem_t wrt;
int cnt=1, numreader=0;

void *writer(void *wno){
	sem_wait(&wrt);
	cnt = cnt*2;
	printf("Writer %d modified cnt to %d\n", *((int*)wno), cnt);
	sem_post(&wrt);
}

void *reader(void* rno){
	pthread_mutex_lock(&mutex);
	numreader++;
	if (numreader==1)
		sem_wait(&wrt);
	pthread_mutex_unlock(&mutex);
	printf("Reader %d read cnt as %d\n", *((int*)rno), cnt);
	pthread_mutex_lock(&mutex);
	numreader--;
	if (numreader==0)
		sem_post(&wrt);
	pthread_mutex_unlock(&mutex);
}

void main(){
	pthread_t write[10], read[10];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&wrt,0,1);
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	
	for(int i=0;i<10;i++){
		pthread_create(&write[i], NULL, (void*)writer, (void*)&a[i]);
		pthread_create(&read[i],NULL,(void*)reader, (void*)&a[i]);
	}
	
	for(int i=1;i<10;i++){
		pthread_join(write[i],NULL);
		pthread_join(read[i],NULL);
	}
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&wrt);
}


Output:
gcc -o read_write read_write.c -pthread
./read_write
Reader 1 read cnt as 1
Reader 2 read cnt as 1
Reader 3 read cnt as 1
Reader 4 read cnt as 1
Reader 5 read cnt as 1
Reader 6 read cnt as 1
Reader 7 read cnt as 1
Reader 8 read cnt as 1
Reader 9 read cnt as 1
Reader 10 read cnt as 1
Writer 1 modified cnt to 2
Writer 2 modified cnt to 4
Writer 3 modified cnt to 8
Writer 4 modified cnt to 16
Writer 5 modified cnt to 32
Writer 6 modified cnt to 64
Writer 7 modified cnt to 128
Writer 8 modified cnt to 256
Writer 9 modified cnt to 512
Writer 10 modified cnt to 1024
