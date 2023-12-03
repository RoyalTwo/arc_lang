#include "generator.h"

void generate(ProgramNode program)
{
    // ASM:
    // Function:
    // .globl _foo
    // _foo:
    //  <FUNCTION BODY GOES HERE>

    // Return:
    //  movl    $3, %eax
    //  ret

    FILE *asm_file = fopen("test_files/asm_output.asm", "w");
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