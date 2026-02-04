#ifndef VM_WRITER_H
#define VM_WRITER_H

#include <stdio.h>

typedef enum {
    SEG_CONSTANT,
    SEG_ARGUMENT,
    SEG_LOCAL,
    SEG_STATIC,
    SEG_THIS,
    SEG_THAT,
    SEG_POINTER,
    SEG_TEMP
} Segment;

typedef enum {
    CMD_ADD,
    CMD_SUB,
    CMD_NEG,
    CMD_EQ,
    CMD_GT,
    CMD_LT,
    CMD_AND,
    CMD_OR,
    CMD_NOT
} Command;

void vmInit(FILE *out);

void writePush(Segment seg, int index);
void writePop(Segment seg, int index);

void writeArithmetic(Command cmd);

void writeLabel(const char *label);
void writeGoto(const char *label);
void writeIf(const char *label);

void writeCall(const char *name, int nArgs);
void writeFunction(const char *name, int nLocals);
void writeReturn();

#endif
