// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N] = {NULL};

// Calculating Varibles
bool isLoaded = false;
int wordCount = 0;
int dictionaryIndex = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int bucket = hash(word);
    node *checker = table[bucket];
    if (checker == NULL)
    {
        return false;
    }
    while (checker->next != NULL)
    {
        if (strcasecmp(checker->word, word) == 0)
        {
            return true;
        }
        else
        {
            checker = checker->next;
        }
    }
    if (checker->next == NULL)
    {
        if (strcasecmp(checker->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opening Dictionary
    FILE *oxford = fopen(dictionary, "r");

    // Set isLoaded
    if (oxford == NULL)
    {
        isLoaded = false;
        fclose(oxford);
        return isLoaded;
    }
    else
    {
        isLoaded = true;
    }

    // Variables
    char letter;
    node *pointer = NULL;
    // Variables END

    // Starting the dictionary
    fread(&letter, sizeof(char), 1, oxford);
    char currentFirst = letter;
    table[(int)(currentFirst - 'a')] = malloc(sizeof(node));
    pointer = table[(int)(currentFirst - 'a')];
    pointer->word[dictionaryIndex] = letter;
    pointer->next = NULL;
    dictionaryIndex++;

    while (fread(&letter, sizeof(char), 1, oxford))
    {
        // New Entry
        if (dictionaryIndex == 0)
        {
            if (currentFirst != letter)
            {
                currentFirst = letter;
                table[(int)(currentFirst - 'a')] = malloc(sizeof(node));
                pointer = table[(int)(currentFirst - 'a')];
                pointer->word[dictionaryIndex] = letter;
                pointer->next = NULL;
                dictionaryIndex++;
                continue;
            }
            if (currentFirst == letter)
            {
                // Make a new node
                pointer->next = malloc(sizeof(node));
                pointer = pointer->next;

                // Append character to word
                pointer->word[dictionaryIndex] = letter;

                dictionaryIndex++;
                continue;
            }
        }
        // We must have found a whole word
        if (letter == '\n')
        {
            // Terminate current word
            pointer->word[dictionaryIndex] = '\0';
            pointer->next = NULL;

            // Update counter
            wordCount++;
            // Prepare for next word
            dictionaryIndex = 0;
            continue;
        }

        // Append character to word
        pointer->word[dictionaryIndex] = letter;
        dictionaryIndex++;
    }
    fclose(oxford);
    return isLoaded;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (isLoaded)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *pointer = NULL;
    node *freeNode = NULL;
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        freeNode = table[i];
        pointer = table[i]->next;
        while (true)
        {
            free(freeNode);
            if (pointer == NULL)
            {
                break;
            }
            freeNode = pointer;
            pointer = pointer->next;
        }
    }
    return true;
}