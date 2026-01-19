/*
 * Hack Assembler - Project Skeleton (Step-by-step Structure)
 * ----------------------------------------------------------
 * This file outlines the structure and main components needed to build
 * a Hack assembler in C, using hash maps for symbol management.
 * Each section is marked with comments for incremental development.
 */

#include <stdio.h> // For file operations  (fopen, fclose, fgets, etc.)
#include <stdlib.h> // For memory allocation (malloc, free, etc.)
#include <string.h> // For string manipulation (strcmp, strcpy, etc.)
#include <ctype.h> // For character checks (isspace, isalpha, etc.)

// =======================
// Step 1: File Reading and Cleaning
// =======================

// Reads a line from file into buffer
// int readLine(FILE *file, char *buffer);
FILE *openFile(const char *filename, const char *mode) {
    FILE *fptr = fopen(filename, mode);
    if (fptr == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE); 
    }
    return fptr;
}

// Removes whitespace and comments from a line
void stripCommentsAndWhitespace(char *line) {
    int i = 0, j = 0;
    int in_comment = 0;
    while (line[i]) {
        // Start of comment
        if (!in_comment && line[i] == '/' && line[i+1] == '/') {
            in_comment = 1;
            break;
        }
        // Skip whitespace
        if (!in_comment && !isspace((unsigned char)line[i])) {
            line[j++] = line[i];
        }
        i++;
    }
    line[j] = '\0';
}



// =======================
// Step 2: Instruction Detection
// =======================

enum InstructionType { A_INSTRUCTION, C_INSTRUCTION, LABEL };

// Returns the type of Hack assembly instruction for a cleaned line
int getInstructionType(char *line) {
    if (line[0] == '@') { // @value
        return A_INSTRUCTION; 
    } else if (line[0] == '(' && line[strlen(line) - 1] == ')') { // (LOOP)
        return LABEL;
    } else {
        return C_INSTRUCTION; // M=D+1;JGT
    }
}

// =======================
// Step 3: Symbol Table (Hash Map)
// =======================

// Hash map node for symbol table
typedef struct SymbolNode {
    char *name;                  // Symbol name (e.g., "LOOP", "R0")
    int address;                 // Associated address (ROM/RAM location)
    struct SymbolNode *next;     // For handling hash collisions (chaining)
} SymbolNode;

#define SYMBOL_TABLE_SIZE 211    // Prime number for better distribution
SymbolNode *symbolTable[SYMBOL_TABLE_SIZE] = {NULL}; // Hash table array

/**
 * Computes a hash value for a given string using the djb2 algorithm.
 *
 * This function takes a null-terminated string (typically a symbol name)
 * and computes its hash value, which is then reduced modulo SYMBOL_TABLE_SIZE
 * to fit within the bounds of a symbol table array.
 *
 * The djb2 algorithm starts with an initial hash value of 5381 and iteratively
 * updates the hash by multiplying the current hash by 33 and adding the ASCII
 * value of the current character.
 *
 * Example:
 *   hash("LOOP") returns a value between 0 and SYMBOL_TABLE_SIZE-1.
 *   hash("R0")   returns a value between 0 and SYMBOL_TABLE_SIZE-1.
//  */
// | Char | ASCII | Calculation           | h          |
// | ---- | ----- | --------------------- | ---------- |
// | L    | 76    | h = 5381*33 + 76      | 177649     |
// | O    | 79    | h = 177649*33 + 79    | 5862616    |
// | O    | 79    | h = 5862616*33 + 79   | 193466327  |
// | P    | 80    | h = 193466327*33 + 80 | 6384398891 |
// Apply modulo SYMBOL_TABLE_SIZE = 16:
// ```
// 6384398891 % 16 = 3
//```
// So "LOOP" maps to index 3 in the symbol table.


// Simple hash function for symbol names
unsigned int hash(char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % SYMBOL_TABLE_SIZE;
}

// Insert a symbol into the table (adds or updates)
void insertSymbol(char *name, int address) {
    unsigned int idx = hash(name);
    SymbolNode *node = symbolTable[idx];
    // Check if symbol already exists, update if so
    while (node) {
        if (strcmp(node->name, name) == 0) {
            node->address = address;
            return;
        }
        node = node->next;
    }
    // Not found, create new node
    node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->name = strdup(name);
    node->address = address;
    node->next = symbolTable[idx];
    symbolTable[idx] = node;
}

// Get symbol address from table, or -1 if not found
int getSymbolAddress(char *name) {
    unsigned int idx = hash(name);
    SymbolNode *node = symbolTable[idx];
    while (node) {
        if (strcmp(node->name, name) == 0)
            return node->address;
        node = node->next;
    }
    return -1; // Not found
}

// Preload predefined symbols (R0-R15, SP, LCL, ARG, THIS, THAT, SCREEN, KBD)
void preloadSymbols() {
    char rname[4];
    for (int i = 0; i <= 15; i++) {
        sprintf(rname, "R%d", i);
        insertSymbol(rname, i);
    }
    insertSymbol("SP", 0);
    insertSymbol("LCL", 1);
    insertSymbol("ARG", 2);
    insertSymbol("THIS", 3);
    insertSymbol("THAT", 4);
    insertSymbol("SCREEN", 16384);
    insertSymbol("KBD", 24576);
}

// Free all memory used by the symbol table
void freeSymbolTable() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        SymbolNode *node = symbolTable[i];
        while (node) {
            SymbolNode *tmp = node;
            node = node->next;
            free(tmp->name);
            free(tmp);
        }
        symbolTable[i] = NULL;
    }
}

// =======================
// Step 4: A-instruction Translation
// =======================

// Translates an A-instruction (e.g., "@21" or "@LOOP") to a 16-bit binary string.
// Returns a pointer to a static buffer containing the result.
char* translateA(char *symbol_or_number) {
    static char binary[17];
    int address;

    // Check if it's a number (decimal constant)
    if (isdigit((unsigned char)symbol_or_number[0])) {
        address = atoi(symbol_or_number);
    } else {
        // It's a symbol: look up in symbol table
        address = getSymbolAddress(symbol_or_number);
        if (address == -1) {
            // Not found: user should allocate RAM address in a full assembler
            address = 0;
        }
    }

    // Convert address to 16-bit binary string
    for (int i = 15; i >= 0; i--) {
        binary[15 - i] = ((address >> i) & 1) ? '1' : '0';
    }
    binary[16] = '\0';
    return binary;
}

// =======================
// Step 5: C-instruction Translation
// =======================

// Lookup tables for comp, dest, jump
// const char *compTable[][2];
// const char *destTable[][2];
// const char *jumpTable[][2];

// char* translateC(char *line);

// =======================
// Step 6: Second Pass and File Output
// =======================

// void writeHackFile(char *output_file, char **lines, int n);

// =======================
// Step 7: Testing Utilities
// =======================

// void runTests();

// =======================
// Step 8: Optimization and Cleanup
// =======================

// Free symbol table memory
// void freeSymbolTable();

// =======================
// Optional: Command-line Arguments, Error Handling
// =======================

// int main(int argc, char *argv[])
// {
//     // 1. Parse command-line arguments
//     // 2. Open input .asm file

//     // 3. Read and clean lines
//     // 4. First pass: build symbol table
//     // 5. Second pass: translate instructions
//     // 6. Write .hack output file
//     // 7. Cleanup
//     return 0;
// }

int main(void) {
    char filename[256];
    char line[512];

    // Preload predefined symbols
    preloadSymbols();

    // Prompt user for file name
    printf("Enter file name: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Failed to read file name\n");
        return EXIT_FAILURE;
    }

    FILE *f = openFile(filename, "r");

    int romAddress = 0; // Track ROM address for labels

    // First pass: read file and insert LABELs
    while (fgets(line, sizeof(line), f)) {
        stripCommentsAndWhitespace(line);
        if (line[0] == '\0') continue;

        int type = getInstructionType(line);
        if (type == LABEL) {
            // Remove parentheses
            line[strlen(line) - 1] = '\0';
            char *labelName = line + 1;
            insertSymbol(labelName, romAddress);
            printf("Inserted label '%s' at address %d\n", labelName, romAddress);
        } else {
            romAddress++; // Only increment for A or C instructions
        }
    }

    rewind(f); // Reset file for second pass if needed

    // Second pass: show symbol lookups for A-instructions
    printf("\nTesting symbol table lookups:\n");
    while (fgets(line, sizeof(line), f)) {
        stripCommentsAndWhitespace(line);
        if (line[0] == '\0') continue;

        int type = getInstructionType(line);
        if (type == A_INSTRUCTION) {
            char *symbolName = line + 1; // Skip '@'
            int addr = getSymbolAddress(symbolName);
            if (addr != -1) {
                printf("Symbol '%s' has address %d\n", symbolName, addr);
            } else {
                printf("Symbol '%s' not found\n", symbolName);
            }
        }
    }

    fclose(f);
    freeSymbolTable();
    return 0;
}

