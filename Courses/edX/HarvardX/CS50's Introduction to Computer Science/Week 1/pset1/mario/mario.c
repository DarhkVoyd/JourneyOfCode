#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // prompt user for length of ladder
    int a = 0;
    do
    {
        a = get_int("Height: ");
    }
    while (a < 1 || a > 8);

    // making the ladder
    for (int i = 1; i <= a; i++)
    {
        // left spaces
        for (int j = 0; j < (a - i); j++)
        {
            printf(" ");
        }

        // left ladder
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // middle gap
        printf("  ");

        // right ladder
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // next line
        printf("\n");
    }
}