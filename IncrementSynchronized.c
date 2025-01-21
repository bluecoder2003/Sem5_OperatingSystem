#include <stdio.h>
#include <pthread.h>

// Shared variable
int count = 0;

// Mutex for synchronization
pthread_mutex_t mutex;

// Thread function
void* incrementCount(void* args) {
    for (int i = 0; i < 10; i++) { // Each thread increments the count 10 times
        pthread_mutex_lock(&mutex); // Lock the mutex
        count++; // Increment the shared variable
        printf("Thread incremented count to %d\n", count);
        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }
    return NULL;
}

int main()
{
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);
    for (long i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, incrementCount, &i);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Final value of count: %d\n", count);
}