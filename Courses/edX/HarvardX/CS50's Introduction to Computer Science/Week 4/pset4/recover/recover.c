#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

// Block Size of FAT File System
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    // Usage Error
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open Input File
    FILE *memory = fopen(argv[1], "r");
    if (memory == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Initialize Required Variables
    int imageCount = 0;
    char *fileName = malloc(10);

    // Opening first Output file
    FILE *jpgPhoto = fopen("000.jpg", "w");
    if (jpgPhoto == NULL)
    {
        printf("Could not create the file.\n");
        return 1;
    }

    //Buffer Space to Store a Block
    BYTE buffer[BLOCK_SIZE];

    // Reading a Block
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, memory) == BLOCK_SIZE)
    {
        // Check if given block is a JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // If the second image if found close the first image
            if (imageCount > 0)
            {
                fclose(jpgPhoto);
            }

            // Creating Names For Next Image
            sprintf(fileName, "%03d.jpg", imageCount);

            // Opening Next Image
            jpgPhoto = fopen(fileName, "w");
            if (jpgPhoto == NULL)
            {
                printf("Could not create the file.\n");
                return 1;
            }

            // Increase Image Count
            imageCount++;
        }

        // To write only if first photo is found
        if (imageCount > 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, jpgPhoto);
        }

    }

    // Free Allocated Memory
    free(fileName);

    // Closing all files
    fclose(memory);
    fclose(jpgPhoto);
}