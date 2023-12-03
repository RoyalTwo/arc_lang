#pragma once
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "main.h"

ProgramNode parser_main(Token *[]);
ProgramNode parse_program(Token *[]);
Function_Node parse_function(Token *tokens[]);
Statement_Node parse_statement(Token *tokens[]);
Expression_Node parse_expression(Token *tokens[]);

void print_ast(ProgramNode program);