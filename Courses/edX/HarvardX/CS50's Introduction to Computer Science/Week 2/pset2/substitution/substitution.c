#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Error if no Key is entered
    if (argc == 1)
    {
        printf("Error! Enter Cipher Key\n");
        return 1;
    }
    
    // Error if longer Key is entered
    if (argc > 2)
    {
        printf("Error! Too many arguments.\n");
        return 1;
    }
    
    // Storing the lenght of Cipher Key
    int n = strlen(argv[1]);

    // Error if incomplete Key is entered
    if (n < 26)
    {
        printf("Error! Incomplete Cipher Key\n");
        return 1;
    }
    
    // Error if Improper Key is entered
    for (int i = 0; i < n; i++)
    {
        if ((argv[1][i] < 'A') || (argv[1][i] > 'Z' && argv[1][i] < 'a') || (argv[1][i] > 'z'))
        {
            printf("Error! Improper Cipher Key\n");
            return 1;
        }
    }
    
    // Making The Key Case Sensitive
    for (int i = 0; i < n; i++)
    {
        argv[1][i] = tolower(argv[1][i]);
    }
    
    // Duplicate Key Error
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((argv[1][i] == argv[1][j]) && (i != j))
            {
                printf("Error! Duplicates in the key\n");
                return 1;
            }
            
        }
    }

    // Prompt user for plain text
    string plain = get_string("plaintext: ");
    
    // Encrption
    printf("ciphertext: ");
    for (int i = 0, x = strlen(plain); i < x; i++)
    {
        if (plain[i] >= 'a' && plain[i] <= 'z') 
        {
            plain[i] = plain[i] - 97;
            plain[i] = argv[1][(int) plain[i]];
            printf("%c", plain[i]);
        }
        else if (plain[i] >= 'A' && plain[i] <= 'Z') 
        {
            plain[i] = plain[i] - 65;
            plain[i] = argv[1][(int) plain[i]];
            printf("%c", toupper(plain[i]));
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
}
