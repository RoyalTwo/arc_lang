#include <stdio.h>
#include "tokenizer.h"
#include <string.h>

int main(int argc, char *argv[])
{
    // Take in a file path when calling main.out
    // Read file at path
    // Tokenize file
    if (argc < 2)
    {
        printf("ERROR: Source path required!\n");
        return 1;
    }
    int source_length = read_source(char_array, argv[1]);
    print_source(source_length);
}

int read_source(char char_array[], char file_path[])
{
    FILE *file_pointer = fopen(file_path, "r");
    int chars_read = 0;
    while (!feof(file_pointer))
    {
        char new_char = fgetc(file_pointer);
        if (!feof(file_pointer))
        {
            char_array[chars_read] = new_char;
            chars_read++;
        }
    }
    return chars_read;
}

void print_source(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("%c", char_array[num]);
    }
    printf("\n");
}