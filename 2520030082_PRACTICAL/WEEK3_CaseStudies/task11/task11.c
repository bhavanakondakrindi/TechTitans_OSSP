#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Web Browser: Google Chrome is running...\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process: Opening PDF using xdg-open...\n");

        execlp("xdg-open", "xdg-open", "lecture.pdf", (char *)NULL);

        perror("exec failed");
        exit(1);
    }
    else
    {
        printf("Parent Process: Browser is still running.\n");
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);

        wait(NULL);

        printf("PDF viewer process finished.\n");
    }

    return 0;
}
