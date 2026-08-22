#include <stdio.h>
#include <string.h>

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
        else if (strlen(command) == 0)
        {
            continue;
        }
        else
        {
            printf("You entered: %s\n", command);
        }
    }

    return 0;
}
