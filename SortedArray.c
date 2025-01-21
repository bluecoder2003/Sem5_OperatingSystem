#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX 100

int array[MAX];
int n; // Size of the matrix
pthread_mutex_t mutex;
// pthread_cond_t cond;
// bool input_done = false; 

void *input(void *args)
{
    pthread_mutex_lock(&mutex);
    printf("enter array");
    scanf("%d",&n);
    printf("enter numbers");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&array[i]);
    }
    // input_done = true;
    // pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void *sorted(void *args)
{
    pthread_mutex_lock(&mutex);
    // while (!input_done)
    // {
    //     pthread_cond_wait(&cond, &mutex); 
    // }
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(array[j]>array[j+1])
            {
                int temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t thread1,thread2;
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&thread1,NULL,input,NULL);
    pthread_create(&thread2,NULL,sorted,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    
}