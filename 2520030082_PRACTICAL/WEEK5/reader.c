#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
    char bfr[100];

    printf("receiving message from writer\n");

    int fd = open("/tmp/bhavana_fifo", O_RDONLY);

    int n = read(fd, bfr, sizeof(bfr) - 1);

    bfr[n] = '\0';

    printf("received message : %s\n", bfr);

    close(fd);

    return 0;
}
