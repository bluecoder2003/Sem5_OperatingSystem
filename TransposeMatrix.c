#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX 100

int matrix[MAX][MAX], transpose[MAX][MAX];
int rows,cols; 

pthread_mutex_t mutex;

void *input(void *args)
{
    pthread_mutex_lock(&mutex);
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);
    printf("enter numbers");
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void *check(void *args)
{
    pthread_mutex_lock(&mutex);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
           transpose[j][i] = matrix[i][j];
        }
    }
    printf("Transpose of the matrix:\n");
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t thread1,thread2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread1,NULL,input,NULL);
    pthread_create(&thread2,NULL,check,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
}