#include <stdio.h>
#include <cs50.h>

int luhn(int a[]);
int n = 0;

int main(void)
{
    // prompt users for input
    long int i = get_long("Number: ");

    long int y = i;

    // calculate number of digits
    while (y > 0)
    {
        y = y / 10;
        n++;
    }

    // storing digit in an array
    y = i;
    int a[n];
    for (int j = 0; j < n; j++)
    {
        a[j] = y % 10;
        y = y / 10;
    }

    // checking card using luhn
    if (luhn(a) == 1)
    {
        // checking type of card
        y = i;
        for (int j = 0; j < (n - 2); j++)
        {
            y = y / 10;
        }
        // checking amex
        if (n == 15 && (y == 34 || y == 37))
        {
            printf("AMEX\n");
        }
        // checking mastercard
        else if (n == 16 && (y >= 51  && y <= 55))
        {
            printf("MASTERCARD\n");
        }
        // checking visa
        else if ((n == 13 || n == 16) && (y >= 40  && y <= 49))
        {
            printf("VISA\n");
        }
        // if nothing then invalid
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int luhn(int a[])
{
    // making digits at even places twice
    for (int j = 1; j < n; j = j + 2)
    {
        a[j] = a[j] * 2;
    }

    // adding sum of digits at even places and digits at odd places
    int sum = 0;
    for (int j = 0; j < n; j++)
    {
        sum = sum + (a[j] % 10);
        a[j] = a[j] / 10;
    }

    for (int j = 0; j < n; j++)
    {
        sum = sum + (a[j] % 10);
        a[j] = a[j] / 10;
    }

    // returning result
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}