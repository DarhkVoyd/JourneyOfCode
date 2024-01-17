#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int a = 0;
    do
    {
        a = get_int("Start size: ");
    }
    while (a < 9);

    // TODO: Prompt for end size
    int b = 0;
    do
    {
        b = get_int("End size: ");
    }
    while (b < a);

    // TODO: Calculate number of years until we reach threshold
    int i = 0;
    while (a < b)
    {
        a = a + (a / 3) - (a / 4);
        i++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", i);
}