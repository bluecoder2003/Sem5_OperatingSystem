#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main() {

  int fd[2];
  pipe(fd);

  pid_t id = fork();

  if (id > 0) {
    char input[100];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    write(fd[1], input, sizeof(input));
    close(fd[1]);
  } 
  else 
  {
    char received[100];
    read(fd[0], received, sizeof(received));
    close(fd[0]);
    int alphabets = 0, digits = 0, specialChars = 0;
    for (int i = 0; received[i] != '\0'; i++) {
            if (isalpha(received[i])) {
                alphabets++;
            } else if (isdigit(received[i])) {
                digits++;
            } else if (received[i] == '#' || received[i] == '&') {
                specialChars++;
            }
        }

        printf("Alphabets: %d\n", alphabets);
        printf("Digits: %d\n", digits);
        printf("Special characters (#, &): %d\n", specialChars);
  }
}