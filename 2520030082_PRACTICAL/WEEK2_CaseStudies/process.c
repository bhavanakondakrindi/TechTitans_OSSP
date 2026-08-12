#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Before fork: PID = %d, PPID = %d\n", getpid(), getppid());

    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    if (pid == 0) {
        printf("\nCHILD PROCESS\n");
        printf("PID  = %d\n", getpid());
        printf("PPID = %d\n", getppid());
        printf("Child is running...\n");

        sleep(10);

        printf("Child process finishing...\n");
    }
    else {
        printf("\nPARENT PROCESS\n");
        printf("PID  = %d\n", getpid());
        printf("Child PID = %d\n", pid);
        printf("Parent is waiting for child...\n");

        sleep(5);

        wait(NULL);

        printf("Child has terminated.\n");
        printf("Parent process finishing...\n");
    }

    return 0;
}
