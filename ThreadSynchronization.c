#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Global variables
int a, b, sum;

// Semaphores
sem_t sem1; // Controls thread 2 after thread 1
sem_t sem2; // Controls thread 3 after thread 2

void* thread1(void *args)
{
    printf("enter a");
    scanf("%d",&a);
    sem_post(&sem1);
    return NULL;
}

void* thread2(void *args)
{
    sem_wait(&sem1);
    printf("enter b");
    scanf("%d",&b);
    sem_post(&sem2);
    return NULL;
}

void* thread3(void *args)
{
    sem_wait(&sem2);
    sum=a+b;
    printf("sum %d",sum);
    return NULL;
}

int main()
{
    pthread_t t1,t2,t3;
    
    sem_init(&sem1,0,0);
    sem_init(&sem2,0,0);
    
    // Create threads
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);

    // Wait for threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
}