#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define BUFFER_SIZE 10
typedef struct {
    char type; // 0=fried chicken, 1=French fries
    int amount; // pieces or weight
    char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void printLog(){
  printf("first = %d\t last = %d\n", first, last);
  return;
}

void produce(item *i) {
    while ((first + 1) % BUFFER_SIZE == last) { 
        // do nothing -- no free buffer item
        }
    memcpy(&buffer[first], i, sizeof(item));
    first = (first + 1) % BUFFER_SIZE;
    printLog();
}

item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) {
        // do nothing -- nothing to consume
    }
    memcpy(i, &buffer[last], sizeof(item));
    last = (last + 1) % BUFFER_SIZE;
    printLog();
    return i;
}

item *initbuffer(char t, int a, char u){
    item *i = malloc(sizeof(item));
    i->type=t;
    i->amount=a;
    i->unit=u;
    return i;
}

void *thread_producer(void *param){
    item *item1 = initbuffer(0,9,0);
    produce(item1);
    item *item2 = initbuffer(1,8,1);
    produce(item2);
    item *item3 = initbuffer(1,7,1);
    produce(item3);
}

void *thread_consumer(void *param){
    item *item0;
    for (int i=0;i<2;i++){
        item0 = consume();
    }
}

int main(){
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_producer, NULL);
    pthread_create(&tid2, NULL, thread_consumer, NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}c
