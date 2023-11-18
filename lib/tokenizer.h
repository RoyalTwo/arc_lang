#pragma once
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"
#include <stdbool.h>

typedef enum
{
    KEYWORD,
    LPAREN,
    RPAREN,
    EQUALS,
    SEMICOLON,
    LBRACE,
    RBRACE,
    IDENTIFIER,
    INTEGER
} TokenType;

typedef struct
{
    TokenType type;
    char value[];
} Token;

// TODO: Switch to dynamic array
const int MAX_CHARS = 4096;
char char_array[MAX_CHARS];
Token token_array[MAX_CHARS];

// Input: char[] file_path
int read_source(char[]);
// Input: int number of characters to print
void print_source(int);
// Input: char[] source array, Token[] destination array, int number of characters in source array
int tokenize(char[], Token[], int);
// Input: char[] word
// Output: Token { type and value }
Token tokenize_single(char[]);
// Input: char[] word
// Output: TokenType
TokenType check_token_type(char[]);
// Input: char character to convert
// Output: OperatorType of input, can be INVALID if not an operator
OperatorType convert_to_operator(char);
// Input: char character to check
// Output: bool, true if semicolon, false if not
bool check_if_semicolon(char);