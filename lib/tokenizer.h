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

int tokenizer_main(int argc, char *argv[]);
void ASSERT_MSG(bool, char[]);

// TODO: Switch to dynamic array
char char_array[4096];
Token token_array[4096];

// Input: char[] file_path
int read_source(char[]);
// Input: int number of characters to print
void print_source(int);
// Input: char[] source array, Token[] destination array, int number of characters in source array
int tokenize(char[], Token[], int);
// Input: char[] word
// Output: Token *{ type and value }
Token *tokenize_single(char[]);
// Input: char[] word
// Output: TokenType
TokenType check_token_type(char[]);
// Input: char character to convert
// Output: OperatorType of input, can be INVALID if not an operator
OperatorType convert_to_operator(char);
// Input: char character to check
// Output: bool, true if semicolon, false if not
bool check_if_semicolon(char);