//
// Created by Gavin Grossman on 4/30/20.
//

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int task_queue[2] = {0, 0};
pthread_mutex_t task_queue_lock;
int one = 0;
int two = 0;
int counter = 0;

void *producer (void *);
void *consumer (void *);

int main() {

    pthread_t pro[1],con[2];
    pthread_mutex_init(&task_queue_lock, NULL);

    int a[2] = {1,2}; //Just used for numbering the producer and consumer

    pthread_create(&pro[0], NULL, (void *)producer, (void *)&a[0]);
    for(int i = 0; i < 2; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    pthread_join(pro[0], NULL);
    for(int i = 0; i < 2; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&task_queue_lock);

    printf("Consumer 1 Removed %d Items. Consumer 2 removed %d items.\n", one, two);
    return 0;

}

bool isFull() {
    if (task_queue[0] != 0 && task_queue[1] != 0) {
        return true;
    } else {
        return false;
    }
}

bool isEmpty() {
    if (task_queue[0] == 0 && task_queue[1] == 0) {
        return true;
    } else {
        return false;
    }
}

int empty_space() {
    if (task_queue[0] == 0) {
        return 0;
    } else {
        return 1;
    }
}

int full_space() {
    if (task_queue[0] != 0) {
        return 0;
    } else {
        return 1;
    }
}

void *producer(void *pno)
{
    int item;
    while(counter < 10) {
        item = rand(); // Produce an random item
        if (isFull() == false) {
            pthread_mutex_lock(&task_queue_lock);
            int spot = empty_space();
            task_queue[spot] = item;
            counter++;
            printf("Producer %d: Insert Item %d at %d\n", *((int *) pno), task_queue[spot], spot);
            pthread_mutex_unlock(&task_queue_lock);
        }
    }
}

void *consumer(void *cno)
{
    while(counter < 10 || isEmpty() == false) {
        pthread_mutex_lock(&task_queue_lock);
        if (isEmpty() == false) {
            int spot = full_space();
            int item = task_queue[spot];
            task_queue[spot] = 0;
            printf("Consumer %d: Remove Item %d from %d\n", *((int *) cno), item, spot);
            
            if (*((int *) cno) == 1) {
                one++;
            }else{
                two++;
            }
            
        }
      pthread_mutex_unlock(&task_queue_lock);  
    }
}