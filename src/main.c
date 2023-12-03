#include "main.h"
#define ANSI_BOLD "\e[1m"
#define ANSI_RESET "\e[m"
#define ANSI_COLOR_RED "\x1b[31m"

int main(int argc, char *argv[])
{
    ASSERT_MSG(argc >= 2, "Source path required!");
    // Call tokenizer with given params
    tokenizer_main(argv[1]);
    ProgramNode program = parser_main(token_array);

    char input_path[512];
    strcpy(input_path, argv[1]);
    input_path[strlen(argv[1]) - 4] = '\0';
    generate(program, input_path);
    // Compile asm and delete file
    char command[512] = "gcc ";
    strcat(command, input_path);
    strcat(command, " -o program && rm ");
    strcat(command, input_path);
    system(command);
}

void ASSERT_MSG(bool condition, char message[])
{
    if (!condition)
    {
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "ASSERTION FAILED: " ANSI_RESET "%s\n", message);
        abort();
    }
}