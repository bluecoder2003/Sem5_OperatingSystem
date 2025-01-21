#include<stdio.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        printf("child process id: %d",getpid());
    }
    else if(pid>0)
    {
        printf("parent process id: %d",getpid());
        pid_t pid=fork();
        if(pid==0)
        {
            printf("child process id: %d",getpid());
        }
        else
        {
            wait(NULL);
            wait(NULL);
        }
    }
    else
    {
        perror("fork");
    }

}