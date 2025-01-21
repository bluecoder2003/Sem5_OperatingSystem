#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {

  int fd[2];
  pipe(fd);

  pid_t id = fork();

  if (id > 0) {
    char input[100];
    printf("Enter a string:: ");
    fgets(input,sizeof(input),stdin);
    input[strcspn(input, "\n")] = '\0';
    write(fd[1], input, sizeof(input));
    close(fd[1]);
  } 
  else 
  {
    char received[100];
    read(fd[0], received, sizeof(received));
    close(fd[0]);
    int len=strlen(received);
    int isPallindrome=1;
    for(int i=0;i<len/2;i++)
    {
      if(received[i]!=received[len-i-1])
      {
        isPallindrome=0;
        break;
      }
    }
    if (isPallindrome) {
            printf("The string \"%s\" is a palindrome.\n", received);
        } else {
            printf("The string \"%s\" is not a palindrome.\n", received);
        }
  }
}