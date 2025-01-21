#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int buff[5], out = 0, in = 0, item = 0;

sem_t full, empty, mut;

void *producer(void *args) {
  int id = *(int *)args;

  while (1) {
    sem_wait(&empty);
    sem_wait(&mut);

    item++;
    buff[in] = item;
    in = (in + 1) % 5;
    printf("Producer %d:\t Produced item %d\n", id, item);

    sem_post(&full);
    sem_post(&mut);

    sleep(1);
  }

  return NULL;
}

void *consumer(void *args) {
  int id = *(int *)args;

  while (1) {
    sem_wait(&full);
    sem_wait(&mut);

    int c = buff[out];
    out = (out + 1) % 5;
    printf("Consumer %d:\t Consumed item %d\n", id, c);

    sem_post(&empty);
    sem_post(&mut);

    sleep(1);
  }

  return NULL;
}

int main() {
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, 5);
  sem_init(&mut, 0, 1);

  pthread_t producer_thread[3], consumer_thread[3];

  for (int i = 0; i < 3; i++) {
    pthread_create(&producer_thread[i], NULL, producer, &i);
  }
  for (int i = 0; i < 3; i++) {
    pthread_create(&consumer_thread[i], NULL, consumer, &i);
  }

  for (int i = 0; i < 3; i++) {
    pthread_join(producer_thread[i], NULL);
  }

  for (int i = 0; i < 3; i++) {
    pthread_join(consumer_thread[i], NULL);
  }

  return 0;
}