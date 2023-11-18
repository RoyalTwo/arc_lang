#include "tokenizer.h"

int tokenizer_main(int argc, char *argv[])
{
    // Tokenize file
    ASSERT_MSG(argc >= 2, "Source path required!");
    int source_length = read_source(argv[1]);
    tokenize(char_array, token_array, source_length);
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
    // Get next word:
    // Go through each character in source array
    // check for whitespace, operator, semicolon, l-rbrace, l-rparenthese
    // These would end a word.
    char(*word)[] = malloc(sizeof(char));
    ASSERT_MSG(word != NULL, "Allocating word failed!");
    int word_length = 0;
    int token_array_length = 0;
    for (int i = 0; i <= source_length; i++)
    {
        // Go through each character in source array
        // Add to word[] until you hit whitespace, operator, semicolon, l-rbrace, l-rparen
        // TODO: Implement braces + parentheses
        // When you do, turn it into token and reset word[], word_length
        // If char is whitespace or operator or semicolon AND isn't a number (if it were a number, operator could return true)
        if (((isspace(source[i]) || convert_to_operator(source[i]) != INVALID || check_if_semicolon(source[i])) && !isdigit(source[i])) || i == source_length)
        {
            // word is empty, do not store
            if ((*word)[0] == '\0')
                continue;

            Token new_token = tokenize_single(*word);
            token_array[token_array_length] = new_token;
            token_array_length++;

            // Reset word
            free(word);
            word_length = 0;
            word = malloc(sizeof(char));
            (*word)[0] = '\0';
            ASSERT_MSG(word != NULL, "Allocating word failed!");

            continue;
        }
        word = realloc(word, sizeof(word) + sizeof(char));
        ASSERT_MSG(word != NULL, "Re-allocating word failed!");

        (*word)[word_length] = source[i];
        word_length++;
    }
    return 0;
}
Token tokenize_single(char word[])
{
    // Call check_token_type to get token type
    // Create new token with value = word and type = TokenType
    // return token
    printf("%s\n", word);
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

bool check_if_semicolon(char character)
{
    return character == ';';
}