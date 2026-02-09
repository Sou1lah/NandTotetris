#include "tokenizer.h"
#include "parser.h"
#include "symbol_table.h"
#include "SemanticAnalyzer.h"
#include "vm_writer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // 1. Read the input file into memory
    FILE *f = fopen(argv[1], "r");
    if(!f) { perror("Failed to open file"); return 1; }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *content = malloc(size + 1);
    fread(content, 1, size, f);
    content[size] = '\0';
    fclose(f);

    // 2. Initialize tokenizer
    initTokenizer(content);

    // 3. Start compilation
    startClass();          // reset class-level symbol table
    startSubroutine();     // reset subroutine-level symbol table

    // 4. Compile the class
    compileClass();

    // 5. Done
    free(content);
    return 0;
}
