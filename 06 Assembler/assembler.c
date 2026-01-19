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
 */
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

/**
 * Translates an A-instruction (e.g., "@21" or "@LOOP") to a 16-bit binary string.
 *
 * This function takes a string representing either a decimal number or a symbol name
 * (from an A-instruction like "@21" or "@LOOP"). It resolves the symbol to an address
 * using the symbol table, or parses the number directly. Then, it converts the address
 * to a 16-bit binary string representation.
 *
 * Steps:
 * 1. Check if the input starts with a digit (decimal number).
 *    - If yes, convert to integer using atoi.
 *    - If no, look up the symbol in the symbol table.
 *      - If found, use the associated address.
 *      - If not found, default to address 0 (incomplete assembler; full version should allocate RAM).
 * 2. Convert the address to a 16-bit binary string by iterating from bit 15 to 0.
 *    - For each bit position i (15 to 0), check if the i-th bit of address is set.
 *    - Append '1' if set, '0' otherwise.
 * 3. Null-terminate the string.
 *
 * Returns a pointer to a static buffer containing the 16-bit binary string.
 *
 * Example:
 *   translateA("21") -> "0000000000010101" (21 in binary)
 *   translateA("LOOP") -> "0000000000000010" (assuming LOOP is at address 2)
 *
 * | Input | Type | Address | Binary Representation |
 * | ------|------|---------|-----------------------|
 * | "21"  | Number| 21      | 0000000000010101     |
 * | "LOOP"| Symbol| 2       | 0000000000000010     |
 */

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
/**
 * Translates a C-instruction (e.g., "D=M+1;JGT", "M=D", "0;JMP") to a 16-bit binary string.
 *
 * A C-instruction in Hack assembly has the general form:
 *   dest=comp;jump
 * where:
 *   - dest (optional): where to store the computation result (e.g., "M", "D", "MD", etc.)
 *   - comp: the computation to perform (e.g., "D+1", "A-1", "M", etc.)
 *   - jump (optional): jump condition (e.g., "JGT", "JEQ", etc.)
 *
 * The binary format for a C-instruction is:
 *   1 1 1 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3
 *   |---| |-------------------| |-------| |-----|
 *    3   7 (comp)              3 (dest)   3 (jump)
 *
 * Steps:
 * 1. Parse the instruction into dest, comp, and jump parts.
 *    - For example, "D=M+1;JGT" -> dest="D", comp="M+1", jump="JGT"
 * 2. Look up the binary codes for comp, dest, and jump using predefined tables.
 *    - Each mnemonic maps to a specific bit pattern.
 * 3. Concatenate the parts into the final 16-bit binary string:
 *    - "111" + comp bits (7) + dest bits (3) + jump bits (3)
 * 4. Null-terminate the string.
 *
 * Example:
 *   "D=M+1;JGT" -> "1111110111010001"
 *   "0;JMP"     -> "1110101010000111"
 *
 * | Assembly        | dest | comp | jump | Binary                |
 * |-----------------|------|------|------|-----------------------|
 * | "D=M+1;JGT"     | D    | M+1  | JGT  | 1111110111010001      |
 * | "0;JMP"         |      | 0    | JMP  | 1110101010000111      |
 * | "M=D"           | M    | D    |      | 1110001100001000      |
 */

// Lookup tables for comp, dest, jump
typedef struct { const char *mnemonic; const char *binary; } TableEntry;

// comp: 7 bits (a c1 c2 c3 c4 c5 c6)
TableEntry compTable[] = {
    {"0",   "0101010"}, {"1",   "0111111"}, {"-1",  "0111010"},
    {"D",   "0001100"}, {"A",   "0110000"}, {"!D",  "0001101"},
    {"!A",  "0110001"}, {"-D",  "0001111"}, {"-A",  "0110011"},
    {"D+1", "0011111"}, {"A+1", "0110111"}, {"D-1", "0001110"},
    {"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"},
    {"A-D", "0000111"}, {"D&A", "0000000"}, {"D|A", "0010101"},
    {"M",   "1110000"}, {"!M",  "1110001"}, {"-M",  "1110011"},
    {"M+1", "1110111"}, {"M-1", "1110010"}, {"D+M", "1000010"},
    {"D-M", "1010011"}, {"M-D", "1000111"}, {"D&M", "1000000"},
    {"D|M", "1010101"},
    {NULL, NULL}
};

// dest: 3 bits (d1 d2 d3)
TableEntry destTable[] = {
    {"",    "000"}, {"M",   "001"}, {"D",   "010"}, {"MD",  "011"},
    {"A",   "100"}, {"AM",  "101"}, {"AD",  "110"}, {"AMD", "111"},
    {NULL, NULL}
};

// jump: 3 bits (j1 j2 j3)
TableEntry jumpTable[] = {
    {"",    "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
    {"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"},
    {NULL, NULL}
};

// Helper: lookup binary code for mnemonic in table
const char* lookup(TableEntry *table, const char *mnemonic) {
    for (int i = 0; table[i].mnemonic; i++) {
        if (strcmp(table[i].mnemonic, mnemonic) == 0)
            return table[i].binary;
    }
    return NULL;
}

// Parses dest=comp;jump into dest, comp, jump parts
void parseCInstruction(char *line, char *dest, char *comp, char *jump) {
    char *eq = strchr(line, '=');
    char *sc = strchr(line, ';');
    // dest
    if (eq) {
        strncpy(dest, line, eq - line);
        dest[eq - line] = '\0';
    } else {
        dest[0] = '\0';
    }
    // comp
    if (eq && sc) {
        strncpy(comp, eq + 1, sc - (eq + 1));
        comp[sc - (eq + 1)] = '\0';
    } else if (eq) {
        strcpy(comp, eq + 1);
    } else if (sc) {
        strncpy(comp, line, sc - line);
        comp[sc - line] = '\0';
    } else {
        strcpy(comp, line);
    }
    // jump
    if (sc) {
        strcpy(jump, sc + 1);
    } else {
        jump[0] = '\0';
    }
}

// Translates a C-instruction line to a 16-bit binary string
char* translateC(char *line) {
    static char binary[17];
    char dest[4] = "", comp[8] = "", jump[4] = "";
    parseCInstruction(line, dest, comp, jump);

    const char *compBits = lookup(compTable, comp);
    const char *destBits = lookup(destTable, dest);
    const char *jumpBits = lookup(jumpTable, jump);

    if (!compBits || !destBits || !jumpBits) {
        // Invalid instruction
        strcpy(binary, "ERROR");
        return binary;
    }

    // Format: 111 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3
    sprintf(binary, "111%s%s%s", compBits, destBits, jumpBits);
    binary[16] = '\0';
    return binary;
}

// =======================
// Step 6: Second Pass and File Output
// =======================

// Writes the translated binary instructions to a .hack file
void writeHackFile(const char *output_file, char **lines, int n) {
    FILE *f = fopen(output_file, "w");
    if (!f) {
        fprintf(stderr, "Error opening output file: %s\n", output_file);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n", lines[i]);
    }
    fclose(f);
}

// Main assembler logic: two-pass, file output, variable allocation
int main(int argc, char *argv[]) {
    char filename[256];
    char line[512];

    // --- Command-line argument parsing ---
    if (argc < 2) {
        printf("Usage: %s input.asm\n", argv[0]);
        return EXIT_FAILURE;
    }
    strncpy(filename, argv[1], sizeof(filename) - 1);
    filename[sizeof(filename) - 1] = '\0';

    // --- Preload symbols ---
    preloadSymbols();

    // --- First pass: label symbols ---
    FILE *f = openFile(filename, "r");
    int romAddress = 0;
    while (fgets(line, sizeof(line), f)) {
        stripCommentsAndWhitespace(line);
        if (line[0] == '\0') continue;
        int type = getInstructionType(line);
        if (type == LABEL) {
            line[strlen(line) - 1] = '\0';
            char *labelName = line + 1;
            insertSymbol(labelName, romAddress);
        } else {
            romAddress++;
        }
    }
    rewind(f);

    // --- Second pass: translate instructions ---
    // We'll store output lines in memory first
    char **outputLines = malloc(romAddress * sizeof(char*));
    int outputCount = 0;
    int nextRamAddress = 16;

    while (fgets(line, sizeof(line), f)) {
        stripCommentsAndWhitespace(line);
        if (line[0] == '\0') continue;
        int type = getInstructionType(line);
        if (type == LABEL) continue; // skip labels in output

        if (type == A_INSTRUCTION) {
            char *symbolOrNumber = line + 1;
            int address;
            if (isdigit((unsigned char)symbolOrNumber[0])) {
                address = atoi(symbolOrNumber);
            } else {
                address = getSymbolAddress(symbolOrNumber);
                if (address == -1) {
                    // New variable: allocate next RAM address
                    insertSymbol(symbolOrNumber, nextRamAddress);
                    address = nextRamAddress++;
                }
            }
            // Convert to binary
            char *binary = translateA(symbolOrNumber);
            outputLines[outputCount] = strdup(binary);
            outputCount++;
        } else if (type == C_INSTRUCTION) {
            char *binary = translateC(line);
            outputLines[outputCount] = strdup(binary);
            outputCount++;
        }
    }
    fclose(f);

    // --- Output file name ---
    char outputFile[300];
    strncpy(outputFile, filename, sizeof(outputFile) - 1);
    outputFile[sizeof(outputFile) - 1] = '\0';
    char *dot = strrchr(outputFile, '.');
    if (dot) strcpy(dot, ".hack");
    else strcat(outputFile, ".hack");

    // --- Write output ---
    writeHackFile(outputFile, outputLines, outputCount);
    printf("Assembly complete. Output written to %s\n", outputFile);

    // --- Cleanup ---
    for (int i = 0; i < outputCount; i++) free(outputLines[i]);
    free(outputLines);
    freeSymbolTable();
    return 0;
}

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

