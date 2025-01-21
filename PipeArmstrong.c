#include <stdio.h>
#include <unistd.h>

int main() {

  int fd[2];
  pipe(fd);

  pid_t id = fork();

  if (id > 0) {
    int n;
    printf("Enter a number:: ");
    scanf("%d", &n);
    write(fd[1], &n, sizeof(int));
  } else {
    int r;
    read(fd[0], &r, sizeof(int));
    int num=r;
    int arm=0;
    while(num>0)
    {
        int m=num%10;
        num=num/10;
        arm = arm+(m*m*m);
    }
    if(arm==r)
    {
        printf("armstrong");
    }
    else
    {
        printf("not armstrong");
    }
  }
}