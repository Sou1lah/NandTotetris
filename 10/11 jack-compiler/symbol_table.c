#include "symbol_table.h"
#include <string.h>

#define MAX_SYMBOLS 128

typedef struct {
    char name[64];
    char type[64];
    Kind kind;
    int index;
} Symbol;

/* Class and subroutine scopes */
static Symbol classTable[MAX_SYMBOLS];
static int classCount;
static Symbol subTable[MAX_SYMBOLS];
static int subCount;

/* Running indices */
static int staticIndex, fieldIndex, argIndex, varIndex;

/* ---------------- RESET ---------------- */
void startClass() {
    classCount = staticIndex = fieldIndex = 0;
}

void startSubroutine() {
    subCount = argIndex = varIndex = 0;
}

/* ---------------- DEFINE ---------------- */
void define(const char *name, const char *type, Kind kind) {
    Symbol s;
    strcpy(s.name, name);
    strcpy(s.type, type);
    s.kind = kind;

    if(kind == KIND_STATIC) s.index = staticIndex++;
    else if(kind == KIND_FIELD) s.index = fieldIndex++;
    else if(kind == KIND_ARG) s.index = argIndex++;
    else if(kind == KIND_VAR) s.index = varIndex++;
    else return;

    if(kind==KIND_STATIC || kind==KIND_FIELD) classTable[classCount++] = s;
    else subTable[subCount++] = s;
}

/* ---------------- QUERIES ---------------- */
static Symbol* find(const char *name) {
    for(int i=0;i<subCount;i++) if(strcmp(subTable[i].name,name)==0) return &subTable[i];
    for(int i=0;i<classCount;i++) if(strcmp(classTable[i].name,name)==0) return &classTable[i];
    return NULL;
}

Kind kindOf(const char *name) { Symbol *s=find(name); return s?s->kind:KIND_NONE; }
const char* typeOf(const char *name) { Symbol *s=find(name); return s?s->type:NULL; }
int indexOf(const char *name) { Symbol *s=find(name); return s?s->index:-1; }

int varCount(Kind kind) {
    if(kind==KIND_STATIC) return staticIndex;
    if(kind==KIND_FIELD)  return fieldIndex;
    if(kind==KIND_ARG)    return argIndex;
    if(kind==KIND_VAR)    return varIndex;
    return 0;
}
