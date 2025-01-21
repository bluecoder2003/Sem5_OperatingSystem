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
    if (r % 2 == 0) {
      printf("%d is even\n", r);
    } else {
      printf("%d is odd\n", r);
    }
  }
}