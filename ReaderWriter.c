#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t wrt, mut;
int rc = 0;

void *writer(void *args) {
  int id = *(int *)args;

  while (1) {
    pthread_mutex_lock(&wrt);//wait
    printf("Writer %d Writing\n", id);
    pthread_mutex_unlock(&wrt);//sigmal
    sleep(1);
  }

  return NULL;
}

void *reader(void *args) {
  int id = *(int *)args;

  while (1) {
    pthread_mutex_lock(&mut);
    rc++;
    if (rc == 1)
      pthread_mutex_lock(&wrt);
    pthread_mutex_unlock(&mut);

    printf("Reader %d Reading\n", id);

    pthread_mutex_lock(&mut);
    rc--;
    if (rc == 0)
      pthread_mutex_unlock(&wrt);
    pthread_mutex_unlock(&mut);
    sleep(1);
  }

  return NULL;
}

int main() {
  pthread_mutex_init(&wrt, NULL);
  pthread_mutex_init(&mut, NULL);

  pthread_t writer_thread[2], reader_thread[5];

  for (int i = 0; i < 2; i++) {
    pthread_create(&writer_thread[i], NULL, writer, &i);
  }

  for (int i = 0; i < 5; i++) {
    pthread_create(&reader_thread[i], NULL, reader, &i);
  }

  for (int i = 0; i < 2; i++) {
    pthread_join(writer_thread[i], NULL);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(reader_thread[i], NULL);
  }

  return 0;
}