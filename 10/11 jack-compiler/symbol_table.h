#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {
    KIND_STATIC,
    KIND_FIELD,
    KIND_ARG,
    KIND_VAR,
    KIND_NONE
} Kind;

void startClass();          // reset class scope
void startSubroutine();    // reset subroutine scope

void define(const char *name, const char *type, Kind kind);

int varCount(Kind kind);

Kind kindOf(const char *name);
const char* typeOf(const char *name);
int indexOf(const char *name);

#endif
