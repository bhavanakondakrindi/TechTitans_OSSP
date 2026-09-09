#include<stdio.h>

int main()
{
    int *ptr = NULL;
    int x = 25;

    ptr = &x;

    printf("x = %d \n", x);
    printf("address of x = %p \n", (void *)&x);
    printf("value of ptr = %p \n", (void *)ptr);
    printf("value at ptr = %d \n", *ptr);
    printf("address of ptr = %p \n", (void *)&ptr);

    return 0;
}
