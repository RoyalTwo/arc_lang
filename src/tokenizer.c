#include "tokenizer.h"

int main(int argc, char *argv[])
{
    // Tokenize file
    if (argc < 2)
    {
        printf("ERROR: Source path required!\n");
        return 1;
    }
    int source_length = read_source(argv[1]);
    tokenize(char_array, token_array, source_length);
}

int read_source(char file_path[])
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
        printf("%c", char_array[i]);
    }
    printf("\n");
}

int tokenize(char source[], Token destination[], int source_length)
{
    // Get next word:
    // Go through each character in source array
    // check for whitespace, operator, semicolon, l-rbrace, l-rparenthese
    // These would end a word.
    char(*word)[] = malloc(sizeof(char));
    int word_length = 0;
    for (int i = 0; i < source_length; i++)
    {
        // Go through each character in source array
        // Add to word[] until you hit whitespace, operator, semicolon, l-rbrace, l-rparenthese
        // When you do, turn it into token
        word = realloc(word, sizeof(word) + sizeof(char));
        (*word)[word_length] = source[i];
        word_length++;
    }
    printf("%s:", *word);
    free(word);
    return 0;
}
Token tokenize_single(char word[])
{
}

TokenType check_token_type(char word[])
{
}

OperatorType convert_to_operator(char character)
{
    OperatorType operator= INVALID;
    // Implicitly casting chars to ints for comparison
    if (character == '+')
        operator= PLUS;
    else if (character == '-')
        operator= MINUS;
    else if (character == '*')
        operator= MULTIPLY;
    else if (character == '/')
        operator= DIVIDE;
    return operator;
}