#include "vm_writer.h"
#include <string.h>

static FILE *outFile;

/* -------- helpers -------- */

static const char* segmentStr(Segment s) {
    switch(s) {
        case SEG_CONSTANT: return "constant";
        case SEG_ARGUMENT: return "argument";
        case SEG_LOCAL:    return "local";
        case SEG_STATIC:   return "static";
        case SEG_THIS:     return "this";
        case SEG_THAT:     return "that";
        case SEG_POINTER:  return "pointer";
        case SEG_TEMP:     return "temp";
        default: return "";
    }
}

static const char* commandStr(Command c) {
    switch(c) {
        case CMD_ADD: return "add";
        case CMD_SUB: return "sub";
        case CMD_NEG: return "neg";
        case CMD_EQ:  return "eq";
        case CMD_GT:  return "gt";
        case CMD_LT:  return "lt";
        case CMD_AND: return "and";
        case CMD_OR:  return "or";
        case CMD_NOT: return "not";
        default: return "";
    }
}

/* -------- public API -------- */

void vmInit(FILE *out) {
    outFile = out;
}

void writePush(Segment seg, int index) {
    fprintf(outFile, "push %s %d\n", segmentStr(seg), index);
}

void writePop(Segment seg, int index) {
    fprintf(outFile, "pop %s %d\n", segmentStr(seg), index);
}

void writeArithmetic(Command cmd) {
    fprintf(outFile, "%s\n", commandStr(cmd));
}

void writeLabel(const char *label) {
    fprintf(outFile, "label %s\n", label);
}

void writeGoto(const char *label) {
    fprintf(outFile, "goto %s\n", label);
}

void writeIf(const char *label) {
    fprintf(outFile, "if-goto %s\n", label);
}

void writeCall(const char *name, int nArgs) {
    fprintf(outFile, "call %s %d\n", name, nArgs);
}

void writeFunction(const char *name, int nLocals) {
    fprintf(outFile, "function %s %d\n", name, nLocals);
}

void writeReturn() {
    fprintf(outFile, "return\n");
}
