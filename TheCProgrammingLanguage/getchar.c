#include <stdio.h>

int main()
{
    int c;
    printf("This program duplicate input from console\n");
    while ((c = getchar()) != EOF)
    {
        printf("%c = %d, ", c, c);
        //putchar(c);
    }
    printf("EOF = %d\n", c);
    printf("End of program\n");
}

int WordsCount()
{
    return 0;
}