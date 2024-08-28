#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t mutex;
sem_t empty, full;
int in=0, out=0, buffer[5];

void *producer(void *pno){
	for(int i=0;i<5;i++){
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		int x = rand()%100;
		buffer[in]=x;
		in = (in+1)%5;
		printf("Producer %d has put %d in buffer\n",*((int*)pno), x);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

void *consumer(void* cno){
	for(int i=0;i<5;i++){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int x = buffer[out];
		out = (out+1)%5;
		printf("Comsumer %d has consumed %d\n",*((int*)cno), x);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}

void main(){
	pthread_t prod[5], con[5];
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);
	
	int a[] = {1,2,3,4,5};
	
	for(int i=0;i<5;i++){
		pthread_create(&prod[i],NULL,(void*)producer, (void*)&a[i]);
		pthread_create(&con[i],NULL,(void*)consumer, (void*)&a[i]);
	}
	
	for(int i=0;i<5;i++){
		pthread_join(prod[i],NULL);
		pthread_join(con[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
}


gcc -o producer_consumer producer_consumer.c -pthread
./producer_consumer
Producer 1 has put 34 in buffer
Consumer 1 has consumed 34
Producer 2 has put 12 in buffer
Consumer 2 has consumed 12
Producer 3 has put 58 in buffer
Consumer 3 has consumed 58
Producer 4 has put 97 in buffer
Consumer 4 has consumed 97
Producer 5 has put 23 in buffer
Consumer 5 has consumed 23
Producer 1 has put 74 in buffer
Consumer 1 has consumed 74
Producer 2 has put 82 in buffer
Consumer 2 has consumed 82
Producer 3 has put 45 in buffer
Consumer 3 has consumed 45
Producer 4 has put 66 in buffer
Consumer 4 has consumed 66
Producer 5 has put 90 in buffer
Consumer 5 has consumed 90
