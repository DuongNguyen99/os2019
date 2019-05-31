#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <semaphore.h>

#define BUFFER_SIZE 10
sem_t s;
int pid=-1;

typedef struct product{
	char type; 
	int amount; 
	char unit;  
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void printLog(){
  printf("first = %d\t last = %d\n", first, last);
  return;
}

void produce(item *i){
	while ((first + 1) % BUFFER_SIZE == last){
   // do nothing -- no free buffer item
	}
	sem_wait(&s);
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	sem_post(&s);
	printLog();
}

item *consume(){
	item *i = malloc(sizeof(item));
	while (first == last){
	 // do nothing -- nothing to consume
	}
	sem_wait(&s);
	memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % BUFFER_SIZE;
	sem_post(&s);
	printLog();
	return i;
}

item *initItem(char type, int amount, char unit){
    item *i = malloc(sizeof(item));
    i->type = type;
    i->amount = amount;
    i->unit = unit;
    return i;
 }
 
 void *thread_producer(void* param){
	pthread_mutex_lock(&m);
	item *item1 = initItem(1,3,0);
  produce(item1);
  item *item2 = initItem(0,9,1);
  produce(item2);
  item *item3 = initItem(1,5,1);
  produce(item3);
	pthread_mutex_unlock(&m);
	pthread_exit(NULL);
}

void *thread_consumer(void* param){
  pthread_mutex_lock(&m);
	consume();
	consume();
	consume();
	pthread_mutex_unlock(&m);
	pthread_exit(NULL);
}

int main(){
	sem_t s;
  sem_init(&s,0,1);
  pthread_mutex_t m;
  pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thread_producer, NULL) 
	pthread_create(&tid2, NULL, thread_consumer, NULL) 
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
  pthread_exit(NULL);
	pthread_mutex_destroy(&m);
  sem_destroy(&s);
	return 0;
}
