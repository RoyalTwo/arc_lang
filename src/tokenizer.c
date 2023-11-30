#include "tokenizer.h"

int tokenizer_main(char path[])
{
    int source_length = read_source(path);
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

int tokenize(char source[], Token *destination[], int source_length)
{
    char(*word)[] = malloc(sizeof(char));
    ASSERT_MSG(word != NULL, "Allocating word failed!");
    strcpy(*word, "NULL");
    int word_length = 0;
    // TODO: Change from static array cap
    char words[128][1024]; // 128 words of 1024 chars each
    int words_array_position = 0;

    for (int i = 0; i <= source_length; i++)
    {
        // There are probably a number of ways to optimize this, but this will do for now.

        // NOTE: Whenever you see strcpy(*word, "NULL"), the reasoning is so we can check if the word has not been added to yet
        // For example, if a word has just been tokenized and reset, the next character is a space so we want to add the previous word,
        // but word is empty due to it being reset.
        // If it's empty, we don't want to add it to the words array
        // TODO: Handle operators
        if (source[i] == '(' || source[i] == ')' || source[i] == '{' || source[i] == '}' || source[i] == ';' || source[i] == '=')
        {
            if (strcmp(*word, "NULL"))
            {
                strcpy(words[words_array_position], *word);
                free(word);
                word_length = 0;
                word = malloc(sizeof(char));
                ASSERT_MSG(word != NULL, "Allocating word failed!");
                strcpy(*word, "NULL");
                words_array_position++;
            }

            // Also want to add source[i] as a word
            char char_as_str[2] = {source[i], '\0'};
            strcpy(words[words_array_position], char_as_str);
            words_array_position++;
            continue;
        }

        // If char is space OR is end of array, previous chars were a word
        if (isspace(source[i]) || i == source_length)
        {
            if (!strcmp(*word, "NULL"))
            {
                continue;
            }
            // Save word, reset word, continue to next char
            strcpy(words[words_array_position], *word);
            free(word);
            word_length = 0;
            word = malloc(sizeof(char));
            ASSERT_MSG(word != NULL, "Allocating word failed!");
            strcpy(*word, "NULL");
            words_array_position++;
            continue;
        }

        // This section is where we add characters to the word variable
        // If word was just set to be NULL, we want to erase that so we can add our new chars
        if (!strcmp(*word, "NULL"))
        {
            free(word);
            word = malloc(sizeof(char));
            ASSERT_MSG(word != NULL, "Allocating word failed!");
        }
        word = realloc(word, sizeof(word) + sizeof(char));
        ASSERT_MSG(word != NULL, "Re-allocating word failed!");
        (*word)[word_length] = source[i];
        word_length++;
    }

    // Now that we have the words in an array, we can go through and tokenize
    int token_array_length = 0;
    for (int i = 0; i < words_array_position; i++)
    {
        Token *new_token = tokenize_single(words[i]);
        token_array[token_array_length] = new_token;
        token_array_length++;
    }

    // Printing all tokens for debug purposes
    for (int i = 0; i < token_array_length; i++)
    {
        printf("TYPE: %d | VALUE: %s\n", token_array[i]->type, token_array[i]->value);
    }
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

Token *tokenize_single(char word[])
{
    Token *new_token = malloc(sizeof(Token));
    new_token->type = T_IDENTIFIER; // IDENTIFIER by default
    strcpy(new_token->value, word);
    // TYPES:
    /*
        T_KEYWORD,
        T_LPAREN,
        T_RPAREN,
        T_EQUALS,
        T_SEMICOLON,
        T_LBRACE,
        T_RBRACE,
        T_IDENTIFIER,
        T_INTEGER
    */
    // TODO: Handle operators
    // TODO: Handle KEYWORDS

    // strcmp returns 0 if strings are equal
    if (!strcmp(word, "("))
    {
        new_token->type = T_LPAREN;
    }
    else if (!strcmp(word, ")"))
    {
        new_token->type = T_RPAREN;
    }
    else if (!strcmp(word, "="))
    {
        new_token->type = T_EQUALS;
    }
    else if (!strcmp(word, ";"))
    {
        new_token->type = T_SEMICOLON;
    }
    else if (!strcmp(word, "{"))
    {
        new_token->type = T_LBRACE;
    }
    else if (!strcmp(word, "}"))
    {
        new_token->type = T_RBRACE;
    }
    return new_token;
}