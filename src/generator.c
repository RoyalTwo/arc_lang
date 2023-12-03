#include "generator.h"

void generate(ProgramNode program, char input_path[])
{
    // ASM:
    // Function:
    // .globl _foo
    // _foo:
    //  <FUNCTION BODY GOES HERE>

    // Return:
    //  movl    $3, %eax
    //  ret

    strcat(input_path, ".asm");

    FILE *asm_file = fopen(input_path, "w");
    ASSERT_MSG(asm_file != NULL, "Could not open ASM file!");
    char asm_func_name[128] = "_";
    strcat(asm_func_name, program.function.id);
    fprintf(asm_file, ".globl %s\n", asm_func_name);
    fprintf(asm_file, "%s:\n", asm_func_name);
    // Function body
    fprintf(asm_file, "\tmov w0, #%d\n", program.function.statement.expr.constant.integer);
    fprintf(asm_file, "\tret");
    fclose(asm_file);
}