#include <stdio.h>
#include <pthread.h>

// Shared variable
int count = 0;


// Thread function
void* incrementCount(void* args) {
    for (int i = 0; i < 10; i++) { // Each thread increments the count 10 times
        count++; // Increment the shared variable
        printf("Thread incremented count to %d\n", count);
    }
    return NULL;
}

int main()
{
    pthread_t threads[3];
    for (long i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, incrementCount, &i);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Final value of count: %d\n", count);
}