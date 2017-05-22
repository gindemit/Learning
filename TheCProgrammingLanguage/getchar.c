#include <stdio.h>

int main()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);
    }
    printf("End of program\n");
}