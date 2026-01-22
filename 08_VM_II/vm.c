#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
    C_UNKNOWN
};

int hasMoreCommands(FILE *vmfile);
int advance(FILE *vmfile, char *command);
int commandType(char *command);
void arg1(char *command, char *arg);
int arg2(char *command);

void writeArithmetic(const char *cmd, FILE *out);
void writePush(const char *segment, int index, FILE *out);
void writePop(const char *segment, int index, FILE *out);
void writeLabel(const char *label, const char *funcName, FILE *out);
void writeGoto(const char *label, const char *funcName, FILE *out);
void writeIfGoto(const char *label, const char *funcName, FILE *out);
void writeFunction(const char *funcName, int nLocals, FILE *out);
void writeCall(const char *funcName, int nArgs, FILE *out);
void writeReturn(FILE *out);
void writeBootstrap(FILE *out) {
    // Set SP=256 and call Sys.init
    fprintf(out, "// Bootstrap code\n");
    fprintf(out, "@256\nD=A\n@SP\nM=D\n");
    // Optionally, call Sys.init here if implementing function call support
    // fprintf(out, "@Sys.init\n0;JMP\n");
}

int advance(FILE *vmfile, char *command) {
    char line[256];
    while (fgets(line, sizeof(line), vmfile)) {
        char *comment = strstr(line, "//");
        if (comment) *comment = '\0';
        char *start = line;
        while (*start && (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')) start++;
        char *end = start + strlen(start) - 1;
        while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) *end-- = '\0';
        if (*start == '\0') continue;
        strcpy(command, start);
        return 1;
    }
    return 0;
}

int hasMoreCommands(FILE *vmfile) {
    int c = fgetc(vmfile);
    if (c == EOF) return 0;
    ungetc(c, vmfile);
    return 1;
}

int commandType(char *command) {
    if (strncmp(command, "push", 4) == 0) return C_PUSH;
    if (strncmp(command, "pop", 3) == 0) return C_POP;
    const char *arith[] = {"add","sub","neg","eq","gt","lt","and","or","not",NULL};
    for (int i = 0; arith[i]; i++) {
        if (strncmp(command, arith[i], strlen(arith[i])) == 0) return C_ARITHMETIC;
    }
    return C_UNKNOWN;
}

void arg1(char *command, char *arg) {
    if (commandType(command) == C_ARITHMETIC) {
        sscanf(command, "%s", arg);
        return;
    }
    char op[16];
    sscanf(command, "%s %s", op, arg);
}

int arg2(char *command) {
    char op[16], segment[16];
    int index = 0;
    if (commandType(command) == C_PUSH || commandType(command) == C_POP) {
        sscanf(command, "%s %s %d", op, segment, &index);
        return index;
    }
    return -1;
}

void writeArithmetic(const char *cmd, FILE *out) {
    if (strcmp(cmd, "add") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=M+D\n");
    } else if (strcmp(cmd, "sub") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n");
    } else if (strcmp(cmd, "neg") == 0) {
        fprintf(out, "@SP\nA=M-1\nM=-M\n");
    } else if (strcmp(cmd, "and") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=M&D\n");
    } else if (strcmp(cmd, "or") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nM=M|D\n");
    } else if (strcmp(cmd, "not") == 0) {
        fprintf(out, "@SP\nA=M-1\nM=!M\n");
    } else if (strcmp(cmd, "eq") == 0 || strcmp(cmd, "gt") == 0 || strcmp(cmd, "lt") == 0) {
        static int labelCount = 0;
        char labelTrue[32], labelEnd[32];
        sprintf(labelTrue, "COMP_TRUE_%d", labelCount);
        sprintf(labelEnd, "COMP_END_%d", labelCount);
        labelCount++;
        fprintf(out, "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@%s\n", labelTrue);
        if (strcmp(cmd, "eq") == 0)
            fprintf(out, "D;JEQ\n");
        else if (strcmp(cmd, "gt") == 0)
            fprintf(out, "D;JGT\n");
        else
            fprintf(out, "D;JLT\n");
        fprintf(out, "@SP\nA=M-1\nM=0\n@%s\n0;JMP\n(%s)\n@SP\nA=M-1\nM=-1\n(%s)\n",
            labelEnd, labelTrue, labelEnd);
    }
}

void writePush(const char *segment, int index, FILE *out) {
    if (strcmp(segment, "constant") == 0) {
        fprintf(out, "@%d\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "local") == 0) {
        fprintf(out, "@%d\nD=A\n@LCL\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "argument") == 0) {
        fprintf(out, "@%d\nD=A\n@ARG\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "this") == 0) {
        fprintf(out, "@%d\nD=A\n@THIS\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "that") == 0) {
        fprintf(out, "@%d\nD=A\n@THAT\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "temp") == 0) {
        fprintf(out, "@%d\nD=A\n@5\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    } else if (strcmp(segment, "pointer") == 0) {
        int addr = (index == 0) ? 3 : 4;
        fprintf(out, "@%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", addr);
    } else if (strcmp(segment, "static") == 0) {
        fprintf(out, "@Static.%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", index);
    }
}

void writePop(const char *segment, int index, FILE *out) {
    if (strcmp(segment, "local") == 0) {
        fprintf(out, "@%d\nD=A\n@LCL\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "argument") == 0) {
        fprintf(out, "@%d\nD=A\n@ARG\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "this") == 0) {
        fprintf(out, "@%d\nD=A\n@THIS\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "that") == 0) {
        fprintf(out, "@%d\nD=A\n@THAT\nD=M+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "temp") == 0) {
        fprintf(out, "@%d\nD=A\n@5\nD=A+D\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n", index);
    } else if (strcmp(segment, "pointer") == 0) {
        int addr = (index == 0) ? 3 : 4;
        fprintf(out, "@SP\nAM=M-1\nD=M\n@%d\nM=D\n", addr);
    } else if (strcmp(segment, "static") == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\n@Static.%d\nM=D\n", index);
    }
}

int labelCounter = 0;
static char currentFileName[64];

char* generateLabel(const char *base) {
    static char label[128];
    snprintf(label, sizeof(label), "%s_%d", base, labelCounter++);
    return label;
}

void setFileName(const char *filename) {
    const char *base = strrchr(filename, '/');
    base = base ? base + 1 : filename;
    strncpy(currentFileName, base, sizeof(currentFileName) - 1);
    currentFileName[sizeof(currentFileName) - 1] = '\0';
    char *dot = strrchr(currentFileName, '.');
    if (dot) *dot = '\0';
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <inputFile.vm | inputDirectory>\n", argv[0]);
        return 1;
    }

    char *inputPath = argv[1];
    char asmFileName[256];
    FILE *out = NULL;

    // Check if input is a directory or file
    int isDir = 0;
    FILE *test = fopen(inputPath, "r");
    if (!test) {
        // Try as directory
        isDir = 1;
    } else {
        fclose(test);
        size_t len = strlen(inputPath);
        if (len > 3 && strcmp(inputPath + len - 3, ".vm") == 0) {
            // Single file: output .asm with same base name
            strncpy(asmFileName, inputPath, len - 3);
            asmFileName[len - 3] = '\0';
            strcat(asmFileName, ".asm");
        } else {
            isDir = 1;
        }
    }

    if (isDir) {
        // Directory: output .asm with directory name
        const char *slash = strrchr(inputPath, '/');
        const char *base = slash ? slash + 1 : inputPath;
        snprintf(asmFileName, sizeof(asmFileName), "%s/%s.asm", inputPath, base);
    }

    out = fopen(asmFileName, "w");
    if (!out) {
        fprintf(stderr, "Cannot open output file %s\n", asmFileName);
        return 1;
    }

    // Write bootstrap code for multi-file (directory) input
    if (isDir) {
        writeBootstrap(out);
    }

    // Helper for reading .vm files
    char command[256];

    if (!isDir) {
        setFileName(inputPath);
        FILE *in = fopen(inputPath, "r");
        if (!in) {
            fprintf(stderr, "Cannot open input file %s\n", inputPath);
            fclose(out);
            return 1;
        }
        while (advance(in, command)) {
            int type = commandType(command);
            char arg[64];
            switch (type) {
                case C_ARITHMETIC:
                    arg1(command, arg);
                    writeArithmetic(arg, out);
                    break;
                case C_PUSH:
                    arg1(command, arg);
                    writePush(arg, arg2(command), out);
                    break;
                case C_POP:
                    arg1(command, arg);
                    writePop(arg, arg2(command), out);
                    break;
                default:
                    // Ignore unknowns for now
                    break;
            }
        }
        fclose(in);
    } else {
        // Directory: process all .vm files
        #include <dirent.h>
        DIR *dir = opendir(inputPath);
        if (!dir) {
            fprintf(stderr, "Cannot open directory %s\n", inputPath);
            fclose(out);
            return 1;
        }
        struct dirent *entry;
        char filePath[512];
        while ((entry = readdir(dir)) != NULL) {
            size_t len = strlen(entry->d_name);
            if (len > 3 && strcmp(entry->d_name + len - 3, ".vm") == 0) {
                snprintf(filePath, sizeof(filePath), "%s/%s", inputPath, entry->d_name);
                setFileName(filePath);
                FILE *in = fopen(filePath, "r");
                if (!in) continue;
                while (advance(in, command)) {
                    int type = commandType(command);
                    char arg[64];
                    switch (type) {
                        case C_ARITHMETIC:
                            arg1(command, arg);
                            writeArithmetic(arg, out);
                            break;
                        case C_PUSH:
                            arg1(command, arg);
                            writePush(arg, arg2(command), out);
                            break;
                        case C_POP:
                            arg1(command, arg);
                            writePop(arg, arg2(command), out);
                            break;
                        default:
                            // Ignore unknowns for now
                            break;
                    }
                }
                fclose(in);
            }
        }
        closedir(dir);
    }

    fclose(out);
    printf("Output written to %s\n", asmFileName);
    return 0;
}