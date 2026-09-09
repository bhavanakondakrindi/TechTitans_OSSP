#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SUBJECTS 5

int main()
{
    int marks1[SUBJECTS], marks2[SUBJECTS];

    printf("Enter marks for Student 1:\n");
    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("Subject %d: ", i + 1);
        scanf("%d", &marks1[i]);
    }

    printf("\nEnter marks for Student 2:\n");
    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("Subject %d: ", i + 1);
        scanf("%d", &marks2[i]);
    }

    int fd1 = shm_open("/student1_marks", O_CREAT | O_RDWR, 0666);
    int fd2 = shm_open("/student2_marks", O_CREAT | O_RDWR, 0666);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("shm_open");
        exit(1);
    }

    ftruncate(fd1, sizeof(marks1));
    ftruncate(fd2, sizeof(marks2));

    int *ptr1 = mmap(NULL, sizeof(marks1),
                     PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    int *ptr2 = mmap(NULL, sizeof(marks2),
                     PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);

    if (ptr1 == MAP_FAILED || ptr2 == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    for (int i = 0; i < SUBJECTS; i++)
    {
        ptr1[i] = marks1[i];
        ptr2[i] = marks2[i];
    }

    printf("\nMarks successfully written to shared memory.\n");
    printf("Student 1 can access /student1_marks.\n");
    printf("Student 2 can access /student2_marks.\n");

    printf("\nTeacher is waiting for students to complete...\n");

    printf("Press Enter after Student 1 and Student 2 have completed.\n");
    getchar();
    getchar();

    munmap(ptr1, sizeof(marks1));
    munmap(ptr2, sizeof(marks2));

    close(fd1);
    close(fd2);

    shm_unlink("/student1_marks");
    shm_unlink("/student2_marks");

    printf("Shared memory objects cleaned up successfully.\n");

    return 0;
}
