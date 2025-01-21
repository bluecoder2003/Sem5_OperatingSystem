#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main() {

    int fd[2];
    pipe(fd);

    pid_t id = fork();

    if (id > 0) {
        // Parent process
        char input[100];
        printf("Enter a string: ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline if present
        input[strcspn(input, "\n")] = '\0';

        write(fd[1], input, sizeof(input));
        close(fd[1]);
    } 
    else {
        // Child process
        char received[100];
        read(fd[0], received, sizeof(received));
        close(fd[0]);

        int vowels = 0, consonants = 0;

        for (int i = 0; received[i] != '\0'; i++) {
            char ch = tolower(received[i]); // Convert to lowercase for case-insensitive comparison
            if (isalpha(ch)) { // Check if it's an alphabet
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                    vowels++;
                } else {
                    consonants++;
                }
            }
        }

        printf("Vowels: %d\n", vowels);
        printf("Consonants: %d\n", consonants);
    }

    return 0;
}
