#include "tokenizer.h"

int tokenizer_main(int argc, char *argv[])
{
    // Tokenize file
    ASSERT_MSG(argc >= 2, "Source path required!");
    int source_length = read_source(argv[1]);
    tokenize(char_array, token_array, source_length);
    return 0;
}

int read_source(char file_path[])
{
    FILE *file_pointer = fopen(file_path, "r");
    ASSERT_MSG(file_pointer != NULL, "Cannot open file!");
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
        printf("%c", char_array[i]);
    }
    printf("\n");
}

int tokenize(char source[], Token destination[], int source_length)
{
    char(*word)[] = malloc(sizeof(char));
    ASSERT_MSG(word != NULL, "Allocating word failed!");
    int word_length = 0;
    // TODO: Change from static array cap
    char words[128][1024]; // 128 words of 1024 chars each
    int words_array_position = 0;
    // For now, we're just going to collect words and only on spaces
    // Loop through every char in source,
    // If char is space OR is end of array, previous chars were a word
    for (int i = 0; i <= source_length; i++)
    {
        if (isspace(source[i]) || i == source_length)
        {
            // Save word, reset word, continue to next char
            strcpy(words[words_array_position], *word);
            free(word);
            word_length = 0;
            word = malloc(sizeof(char));
            ASSERT_MSG(word != NULL, "Allocating word failed!");
            words_array_position++;
            continue;
        }
        word = realloc(word, sizeof(word) + sizeof(char));
        ASSERT_MSG(word != NULL, "Re-allocating word failed!");
        (*word)[word_length] = source[i];
        word_length++;
    }
    printf("[%s, %s]\n", words[0], words[1]);
    return 0;
}

OperatorType convert_to_operator(char character)
{
    OperatorType operator= INVALID;
    // Implicitly casting chars to ints for comparison
    if (character == '+')
    {
        operator= PLUS;
    }
    else if (character == '-')
        operator= MINUS;
    else if (character == '*')
        operator= MULTIPLY;
    else if (character == '/')
        operator= DIVIDE;
    return operator;
}

bool check_if_semicolon(char character)
{
    return character == ';';
}