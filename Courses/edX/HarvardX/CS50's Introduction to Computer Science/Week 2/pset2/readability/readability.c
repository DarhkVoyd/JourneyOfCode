#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float alg(float L, float S, float W);

int main(void)
{
    // Prompt the user for input
    string text = get_string("Text: ");

    // Conditions for calculating words, sentences and letters
    float letters = 0, words = 0, sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Usually words are generated due to gap between collection of letters
        if (text[i] == ' ')
        {
            words = words + 1;
        }
        // but sometimes punctuations which build sentences also cause formation of words
        else if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            sentences = sentences + 1;
            words = words + 1;
        }
        
        // any character of alphabetical type is letter
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters = letters + 1;
        }

        // due simultaneous occurence of punctuations and gaps there will be miscalculation in words so correct one must be reduced each time
        if ((text[i] == '?' && text[i + 1] == ' ') || (text[i] == '!' && text[i + 1] == ' ') || (text[i] == '.' && text[i + 1] == ' '))
        {
            words = words - 1;
        }
    }

    // Displaying the result
    int a = round(alg(letters, sentences, words));
    if (a < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (a > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", a);
    }

}

// Algorithm to calculate complexity
float alg(float L, float S, float W)
{
    L = ((L / W) * 100);
    S = ((S / W) * 100);
    float index = ((0.0588 * L) - (0.296 * S) - 15.8);
    return index;
}