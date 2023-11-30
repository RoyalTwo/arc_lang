#pragma once
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"
#include <stdbool.h>
#include <string.h>
#include "main.h"

typedef enum
{
    T_KEYWORD,
    T_LPAREN,
    T_RPAREN,
    T_EQUALS,
    T_SEMICOLON,
    T_LBRACE,
    T_RBRACE,
    T_IDENTIFIER,
    T_INTEGER
} TokenType;

typedef struct
{
    TokenType type;
    char value[];
} Token;

int tokenizer_main(char[]);
void ASSERT_MSG(bool, char[]);

// TODO: Switch to dynamic array
char char_array[4096];
Token token_array[4096];

// Input: char[] file_path
int read_source(char[]);
// Input: char[] source array, Token[] destination array, int number of characters in source array
int tokenize(char[], Token[], int);
// Input: char character to convert
// Output: OperatorType of input, can be INVALID if not an operator
OperatorType convert_to_operator(char);

Token *tokenize_single(char[]);