#include "SemanticAnalyzer.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>


static const char* currentType = NULL; // Track the current type for variable declarations

/*
analyzeClass() walks through all top-level elements of a class, sending class variables to one handler and subroutines to another, while managing the symbol table scope for the class. It’s basically the entry point for semantic analysis of a Jack class.
*/
void analyzeClass() {
    startClass();

    advance(); // Skip 'class' keyword
    advance(); // Skip class name
    advance(); // Skip '{'

    while(hasMoreTokens()){
        advance();
        if (strcmp(currentToken, "static") == 0 || strcmp(currentToken, "field") == 0) {
            analyzeClassVarDec();
        } else if (strcmp(currentToken, "constructor") == 0 || strcmp(currentToken, "function") == 0 || strcmp(currentToken, "method") == 0) {
            analyzeSubroutineDec();
        } else if (strcmp(currentToken, "}") == 0) {
            break; // End of class
        }
    }
}

void analyzeSubroutineDec() {
    // ---------------- Step 0: Reset subroutine scope ----------------
    startSubroutine();  // clears ARG and VAR indices

    // ---------------- Step 1: Subroutine kind ----------------
    char subroutineKind[16];
    strcpy(subroutineKind, currentToken); // constructor, function, method
    advance(); // move to return type

    // ---------------- Step 2: Return type ----------------
    char currentReturnType[64];
    strcpy(currentReturnType, currentToken);

    // Check return type is valid
    if(strcmp(currentReturnType, "int") != 0 &&
       strcmp(currentReturnType, "char") != 0 &&
       strcmp(currentReturnType, "boolean") != 0 &&
       strcmp(currentReturnType, "void") != 0 &&
       !isClass(currentReturnType)) {
        printf("Semantic Error: Unknown return type '%s'\n", currentReturnType);
        return;
    }

    advance(); // move to subroutine name

    // ---------------- Step 3: Subroutine name ----------------
    char subroutineName[64];
    strcpy(subroutineName, currentToken);

    // Optional: check for duplicate subroutine names
    if(subroutineExists(subroutineName)) {
        printf("Semantic Error: Subroutine '%s' already declared in class\n", subroutineName);
        return;
    }

    advance(); // move to '('

    // ---------------- Step 4: Parameter list ----------------
    // Example: (int x, boolean flag)
    if(tokenType() == TOKEN_SYMBOL && symbol() == '(') {
        advance(); // move to first parameter or ')'
        while(tokenType() != TOKEN_SYMBOL || symbol() != ')') {
            char paramType[64];
            char paramName[64];

            strcpy(paramType, currentToken);   // read type
            advance();
            strcpy(paramName, currentToken);   // read parameter name

            // Add to subroutine symbol table as ARG
            if(find(paramName) != NULL) {
                printf("Semantic Error: Parameter '%s' already exists\n", paramName);
                return;
            }
            define(paramName, paramType, KIND_ARG);

            advance();
            if(tokenType() == TOKEN_SYMBOL && symbol() == ',') advance(); // next param
        }
        advance(); // move past ')'
    }

    // ---------------- Step 5: Subroutine body ----------------
    advance(); // '{'
    while(tokenType() == TOKEN_KEYWORD && strcmp(currentToken, "var") == 0) {
        analyzeVarDec(); // handle local variables, add to subroutine table as VAR
    }

    analyzeStatements(); // let/do/return etc.

    advance(); // '}' end of subroutine
}
