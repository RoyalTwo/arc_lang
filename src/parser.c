#include "parser.h"

ProgramNode parser_main(Token *tokens[])
{
    ProgramNode root = parse_program(tokens);
    return root;
}
ProgramNode parse_program(Token *tokens[])
{
    ProgramNode program;
    program.function = parse_function(tokens);
    return program;
}
Function_Node parse_function(Token *tokens[])
{
    int array_pos = 0;
    Function_Node function;
    // int main() { statement }
    // <function> ::= "int" <id> "(" ")" "{" <statement> "}"
    ASSERT_MSG(!strcmp(tokens[array_pos]->value, "int"), "Missing int!");
    array_pos++;
    ASSERT_MSG((tokens[array_pos]->type == T_IDENTIFIER), "Missing function name!");
    strcpy(function.id, tokens[array_pos]->value);
    array_pos++;
    ASSERT_MSG((tokens[array_pos]->type == T_LPAREN), "Missing left parenthese!");
    array_pos++;
    ASSERT_MSG((tokens[array_pos]->type == T_RPAREN), "Missing right parenthese!");
    // TODO: Add PARAMS
    array_pos++;
    ASSERT_MSG((tokens[array_pos]->type == T_LBRACE), "Missing left brace!");
    array_pos++;
    Token *statement_tokens[128];
    int statement_tokens_pos = 0;
    while (strcmp(tokens[array_pos]->value, "}"))
    {
        statement_tokens[statement_tokens_pos] = tokens[array_pos];
        statement_tokens_pos++;
        array_pos++;
    }
    Statement_Node statement = parse_statement(statement_tokens);
    function.statement = statement;
    ASSERT_MSG((tokens[array_pos]->type == T_RBRACE), "Missing right brace!");
    return function;
}
Statement_Node parse_statement(Token *tokens[])
{
    int array_pos = 0;
    // return expr;
    // <statement> ::= "return" <exp> ";"
    ASSERT_MSG(!strcmp(tokens[array_pos]->value, "return"), "Missing return keyword!");
    array_pos++;
    Token *expression_tokens[128];
    expression_tokens[0] = tokens[array_pos];
    // TODO: Parse more than one more token as expression
    array_pos++;
    Expression_Node expression = parse_expression(expression_tokens);
    Statement_Node statement = {expression};
    return statement;
}
Expression_Node parse_expression(Token *tokens[])
{
    // <int>
    ASSERT_MSG(tokens[0]->type == T_INTEGER, "Expression is not an integer!");
    Constant c = {atoi(tokens[0]->value)};
    Expression_Node expr = {c};
    return expr;
}