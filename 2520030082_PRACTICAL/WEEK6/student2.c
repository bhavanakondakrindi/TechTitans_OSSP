#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SUBJECTS 5

int main()
{
    int fd = shm_open("/student2_marks", O_RDONLY, 0666);

    if (fd == -1)
    {
        perror("Student 2: shm_open");
        exit(1);
    }

    int *marks = mmap(NULL, SUBJECTS * sizeof(int),
                      PROT_READ, MAP_SHARED, fd, 0);

    if (marks == MAP_FAILED)
    {
        perror("Student 2: mmap");
        exit(1);
    }

    int total = 0;

    printf("\nStudent 2\n");
    printf("--------------------------------\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("Subject %d : %d\n", i + 1, marks[i]);
        total += marks[i];
    }

    printf("\nTotal : %d\n", total);
    printf("Average : %.2f\n", (float)total / SUBJECTS);

    munmap(marks, SUBJECTS * sizeof(int));
    close(fd);

    return 0;
}
