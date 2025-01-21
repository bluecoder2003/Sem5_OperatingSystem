#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX 100

int matrix[MAX][MAX];
int size; // Size of the matrix
bool isSymmetric = true;

void *input(void *args)
{
    printf("enter matrix");
    scanf("%d",&size);
    printf("enter numbers");
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
}

void *check(void *args)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<i;j++)
        {
           if (matrix[i][j] != matrix[j][i]) {
                isSymmetric = false;
                return NULL;
            }
        }
    }
}

int main()
{
    pthread_t thread1,thread2;
    
    pthread_create(&thread1,NULL,input,NULL);
    pthread_create(&thread2,NULL,check,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    
    if (isSymmetric) {
        printf("The matrix is symmetric.\n");
    } else {
        printf("The matrix is not symmetric.\n");
    }
}