#include "main.h"
#define ANSI_BOLD "\e[1m"
#define ANSI_RESET "\e[m"
#define ANSI_COLOR_RED "\x1b[31m"

int main(int argc, char *argv[])
{
    // Call tokenizer with given params
    tokenizer_main(argc, argv);
}

void ASSERT_MSG(bool condition, char message[])
{
    if (!condition)
    {
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "ASSERTION FAILED: " ANSI_RESET "%s\n", message);
        abort();
    }
}