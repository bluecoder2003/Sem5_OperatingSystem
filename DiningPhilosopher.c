#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t chopstick[5];

void *philosopher(void *args) {
  int id = *(int *)args;

  while (1) {
    printf("Phylosopher %d is thinking\n", id);
    pthread_mutex_lock(&chopstick[id]);
    pthread_mutex_lock(&chopstick[(id + 1) % 5]);
    printf("Phylosopher %d is eating\n", id);
    pthread_mutex_unlock(&chopstick[id]);
    pthread_mutex_unlock(&chopstick[(id + 1) % 5]);
    sleep(1);
  }

  return 0;
}

int main() {
  pthread_t phylosophers_thread[5];

  for (int i = 0; i < 5; i++) {
    pthread_create(&phylosophers_thread[i], NULL, philosopher, &i);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(phylosophers_thread[i], NULL);
  }

  return 0;
}