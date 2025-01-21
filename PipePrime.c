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
    int isPrime=1;
    read(fd[0], &r, sizeof(int));
    for(int i=2;i * i <=r;i++)
    {
    if (r % i == 0) 
    {
    isPrime = 0; // Not a prime number
    break;
    } 
    }
    if (isPrime) {
        printf("%d is prime\n", r);
    } else {
        printf("%d is not prime\n", r);
    }
  }
}