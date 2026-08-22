#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char command[100];

    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        if (strlen(command) == 0)
        {
            continue;
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            continue;
        }

        if (pid == 0)
        {
            execlp(command, command, (char *)NULL);

            perror("Command execution failed");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}
