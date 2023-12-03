#pragma once

// TODO: Put operatorTypes here
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
    T_INTEGER,
    T_OPERATOR
} TokenType;

typedef struct
{
    TokenType type;
    char value[];
} Token;

// AST Nodes
typedef struct
{
    int integer;
} Constant;
typedef struct
{
    Constant constant;
} Expression_Node;
typedef struct
{
    // TODO: Add KEYWORD
    Expression_Node expr;
} Statement_Node;
typedef struct
{
    char id[10];
    // TODO: Add RETURNTYPE
    // TODO: Add PARAMS
    Statement_Node statement;
} Function_Node;
typedef struct
{
    Function_Node function;
} ProgramNode;
