
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Command types
enum {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_UNKNOWN
};

// Command types

// Function prototypes for parser and code generator
int advance(FILE *vmfile, char *command);
int commandType(char *command);
void arg1(char *command, char *arg);
int arg2(char *command);
void writeArithmetic(const char *cmd, FILE *out);
void writePush(const char *segment, int index, FILE *out);
void writePop(const char *segment, int index, FILE *out);

// ----------------------------
// Simple main for testing parser and code generator
// ----------------------------
// This main reads a VM file, parses each command, and writes Hack assembly to an output file.
// For demonstration/testing only. Remove or replace with full main later.
int main() {
    char infile[256], outfile[256];
    printf("Enter input VM file name: ");
    if (!fgets(infile, sizeof(infile), stdin)) return 1;
    infile[strcspn(infile, "\n")] = 0;
    printf("Enter output ASM file name: ");
    if (!fgets(outfile, sizeof(outfile), stdin)) return 1;
    outfile[strcspn(outfile, "\n")] = 0;
    FILE *in = fopen(infile, "r");
    if (!in) {
        perror("Input file open failed");
        return 1;
    }
    FILE *out = fopen(outfile, "w");
    if (!out) {
        perror("Output file open failed");
        fclose(in);
        return 1;
    }
    char command[256], arg[32];
    while (advance(in, command)) {
        int type = commandType(command);
        if (type == C_ARITHMETIC) {
            arg1(command, arg);
            writeArithmetic(arg, out);
        } else if (type == C_PUSH) {
            arg1(command, arg);
            int idx = arg2(command);
            writePush(arg, idx, out);
        } else if (type == C_POP) {
            arg1(command, arg);
            int idx = arg2(command);
            writePop(arg, idx, out);
        } else {
            // Unknown or unsupported command
            fprintf(out, "// Skipped: %s\n", command);
        }
    }
    fclose(in);
    fclose(out);
    printf("Done. Output written to %s\n", outfile);
    return 0;
}
// vm.c - VM Translator Skeleton
// ----------------------------
// Translates .vm file(s) into Hack assembly (.asm)

// ----------------------------
// 1. Parser Section
// ----------------------------
// Responsibilities:
// - Read VM commands from input file(s)
// - Remove comments and whitespace
// - Determine command type (arithmetic, push, pop)
// - Provide access to command arguments

// Command types

// Reads the next non-empty, non-comment line from the file into buffer
// Returns 1 if a command was read, 0 if EOF
int advance(FILE *vmfile, char *command) {
    char line[256];
    while (fgets(line, sizeof(line), vmfile)) {
        // Remove comments
        char *comment = strstr(line, "//"); // strstr finds substring
        if (comment) *comment = '\0';
        // Remove leading/trailing whitespace
        char *start = line;
        while (*start && (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')) start++; // /t is tab, /r is carriage return, /n is newline
        char *end = start + strlen(start) - 1; // this line gets the end of the string by adding the length - 1 to the start pointer
        while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) *end-- = '\0'; // this line removes trailing whitespace by moving backwards from the end
        if (*start == '\0') continue; // skip empty lines
        strcpy(command, start); // strcpy copies the cleaned line into command example : strcpy(destination, source);
        return 1;
    }
    return 0;
}

// Returns 1 if there are more commands (peek ahead)
int hasMoreCommands(FILE *vmfile) {
    int c = fgetc(vmfile);
    if (c == EOF) return 0;
    ungetc(c, vmfile);
    return 1;
}

// Determines the command type
int commandType(char *command) {
    if (strncmp(command, "push", 4) == 0) return C_PUSH;
    if (strncmp(command, "pop", 3) == 0) return C_POP;
    // Arithmetic/logical commands: add, sub, neg, eq, gt, lt, and, or, not
    const char *arith[] = {"add","sub","neg","eq","gt","lt","and","or","not",NULL};
    for (int i = 0; arith[i]; i++) {
        if (strncmp(command, arith[i], strlen(arith[i])) == 0) return C_ARITHMETIC;
    }
    return C_UNKNOWN;
}

// Extracts the first argument (segment or operation)
void arg1(char *command, char *arg) {
    // For arithmetic, arg1 is the command itself
    if (commandType(command) == C_ARITHMETIC) {
        sscanf(command, "%s", arg);
        return;
    }
    // For push/pop, arg1 is the segment
    char op[16];
    sscanf(command, "%s %s", op, arg);
}

// Extracts the second argument (index) for push/pop
int arg2(char *command) {
    char op[16], segment[16];
    int index = 0;
    if (commandType(command) == C_PUSH || commandType(command) == C_POP) {
        sscanf(command, "%s %s %d", op, segment, &index);
        return index;
    }
    return -1;
}

/*
Explanation:
- advance: Reads the next VM command, skipping comments/whitespace.
- hasMoreCommands: Checks if more input remains.
- commandType: Classifies the command (arithmetic, push, pop).
- arg1int main(int argc, char **argv) {
//     // TODO: Open VM file(s)
//     // TODO: Open output ASM file

//     // TODO: Loop through all VM commands
//     //      - advance parser
//     //      - determine command type
//     //      - call code generator

//     // TODO: Close files
//     return 0;
// }: Gets the first argument (operation or segment).
- arg2: Gets the second argument (index for push/pop).
*/

// ----------------------------
// 2. Code Generator Section
// ----------------------------
// Responsibilities:
// - Translate each VM command into Hack assembly instructions
// - Handle arithmetic/logical commands
// - Handle push/pop commands for all memory segments
// - Generate unique labels for comparisons (eq, gt, lt)

// Example function prototypes:

// Writes Hack assembly for arithmetic/logical commands (add, sub, neg, eq, gt, lt, and, or, not)
void writeArithmetic(const char *cmd, FILE *out) {
    // Stack pointer is at RAM[0] (SP)
    // Stack grows upward; top value is at *(SP-1)
    if (strcmp(cmd, "add") == 0) {
        // SP--, D = *SP, SP--, *SP = *SP + D, SP++
        fprintf(out,
            "@SP\nAM=M-1\nD=M\nA=A-1\nM=M+D\n");
    } else if (strcmp(cmd, "sub") == 0) {
        fprintf(out,
            "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n");
    } else if (strcmp(cmd, "neg") == 0) {
        fprintf(out,
            "@SP\nA=M-1\nM=-M\n");
    } else if (strcmp(cmd, "and") == 0) {
        fprintf(out,
            "@SP\nAM=M-1\nD=M\nA=A-1\nM=M&D\n");
    } else if (strcmp(cmd, "or") == 0) {
        fprintf(out,
            "@SP\nAM=M-1\nD=M\nA=A-1\nM=M|D\n");
    } else if (strcmp(cmd, "not") == 0) {
        fprintf(out,
            "@SP\nA=M-1\nM=!M\n");
    } else if (strcmp(cmd, "eq") == 0 || strcmp(cmd, "gt") == 0 || strcmp(cmd, "lt") == 0) {
        // Comparison: eq, gt, lt
        // Generate unique label for jump
        static int labelCount = 0;
        char labelTrue[32], labelEnd[32];
        sprintf(labelTrue, "COMP_TRUE_%d", labelCount);
        sprintf(labelEnd, "COMP_END_%d", labelCount);
        labelCount++;
        // SP--, D = *SP, SP--, D = *SP - D, if (D==0) set true else false, SP++
        fprintf(out,
            "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@%s\n", labelTrue);
        if (strcmp(cmd, "eq") == 0)
            fprintf(out, "D;JEQ\n");
        else if (strcmp(cmd, "gt") == 0)
            fprintf(out, "D;JGT\n");
        else
            fprintf(out, "D;JLT\n");
        // False case
        fprintf(out,
            "@SP\nA=M-1\nM=0\n@%s\n0;JMP\n(%s)\n@SP\nA=M-1\nM=-1\n(%s)\n",
            labelEnd, labelTrue, labelEnd);
    }
    // Each arithmetic command manipulates the stack as per VM spec.
}

// Writes Hack assembly for push command
void writePush(const char *segment, int index, FILE *out) {
    // Handles push for constant, local, argument, this, that, temp, pointer, static
    if (strcmp(segment, "constant") == 0) {
        // Push constant value onto stack
        fprintf(out,
            "@%d\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "local") == 0) {
        fprintf(out,
            "@%d\nD=A\n@LCL\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "argument") == 0) {
        fprintf(out,
            "@%d\nD=A\n@ARG\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "this") == 0) {
        fprintf(out,
            "@%d\nD=A\n@THIS\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "that") == 0) {
        fprintf(out,
            "@%d\nD=A\n@THAT\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "temp") == 0) {
        // temp segment base address is 5
        fprintf(out,
            "@%d\nD=A\n@5\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "pointer") == 0) {
        // pointer 0 -> THIS (3), pointer 1 -> THAT (4)
        int addr = (index == 0) ? 3 : 4;
        fprintf(out,
            "@%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", addr);
    } else if (strcmp(segment, "static") == 0) {
        // static variables: use label like Static.index
        fprintf(out,
            "@Static.%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    }
    // Each push command loads a value and puts it on the stack.
}

// Writes Hack assembly for pop command
void writePop(const char *segment, int index, FILE *out) {
    // Handles pop for local, argument, this, that, temp, pointer, static
    if (strcmp(segment, "local") == 0) {
        fprintf(out,
            "@%d\nD=A\n@LCL\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "argument") == 0) {
        fprintf(out,
            "@%d\nD=A\n@ARG\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "this") == 0) {
        fprintf(out,
            "@%d\nD=A\n@THIS\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "that") == 0) {
        fprintf(out,
            "@%d\nD=A\n@THAT\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "temp") == 0) {
        // temp segment base address is 5
        fprintf(out,
            "@%d\nD=A\n@5\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "pointer") == 0) {
        int addr = (index == 0) ? 3 : 4;
        fprintf(out,
            "@SP\nAM=M-1\nD=M\n@%d\nM=D\n", addr);
    } else if (strcmp(segment, "static") == 0) {
        fprintf(out,
            "@SP\nAM=M-1\nD=M\n@Static.%d\nM=D\n", index);
    }
    // Each pop command removes the top value from the stack and stores it in the segment.
}


// ----------------------------
// 3. Utility Section
// ----------------------------
// Responsibilities:
// - Helper functions for label generation
// - Memory segment mapping
// - Any reusable helper routines

// Example function prototypes:
char* generateLabel(const char *base);  // Returns a unique label each time called

// ----------------------------
// 4. Main Function
// ----------------------------
// Responsibilities:
// - Open input .vm file(s)
// - Open output .asm file
// - Loop through all VM commands:
//     - Parse command
//     - Determine type
//     - Call corresponding code generation function
// - Close files


