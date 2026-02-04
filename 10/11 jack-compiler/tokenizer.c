// tokenizer.c
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN 256

static const char *input;
static int pos;
static char currentToken[MAX_TOKEN];
static TokenType currentType;

const char *keywords[] = {
    "class","constructor","function","method","field","static","var",
    "int","char","boolean","void","true","false","null","this",
    "let","do","if","else","while","return"
};
const int numKeywords = 21;
const char symbols[] = "{}()[].,;+-*/&|<>=~";

// ----------------- UTILITY -----------------
int isKeyword(const char *str) {
    for(int i=0;i<numKeywords;i++) if(strcmp(str, keywords[i])==0) return 1;
    return 0;
}

int isSymbol(char c) {
    for(int i=0;i<sizeof(symbols)-1;i++) if(c==symbols[i]) return 1;
    return 0;
}

void skipWhitespace() {
    while(input[pos]) {
        if(isspace(input[pos])) { pos++; continue; }
        if(input[pos]=='/' && input[pos+1]=='/') { while(input[pos] && input[pos++]!='\n'); continue; }
        if(input[pos]=='/' && input[pos+1]=='*') { 
            pos+=2; while(input[pos] && !(input[pos]=='*' && input[pos+1]=='/')) pos++;
            if(input[pos]) pos+=2;
            continue;
        }
        break;
    }
}

// ----------------- MAIN FUNCTIONS -----------------
void initTokenizer(const char *fileContent) {
    input = fileContent; pos=0;
    currentToken[0]='\0'; currentType=TOKEN_NONE;
}

int hasMoreTokens() { skipWhitespace(); return input[pos]!='\0'; }

void advance() {
    skipWhitespace();
    int i=0; char c = input[pos];
    if(!c) { currentType=TOKEN_NONE; currentToken[0]='\0'; return; }

    if(isSymbol(c)) { currentToken[0]=c; currentToken[1]='\0'; currentType=TOKEN_SYMBOL; pos++; return; }

    if(c=='"') {
        pos++;
        while(input[pos] && input[pos]!='"' && i<MAX_TOKEN-1) currentToken[i++] = input[pos++];
        currentToken[i]='\0'; currentType=TOKEN_STRING_CONST;
        if(input[pos]=='"') pos++;
        return;
    }

    if(isdigit(c)) {
        while(isdigit(input[pos]) && i<MAX_TOKEN-1) currentToken[i++] = input[pos++];
        currentToken[i]='\0'; currentType=TOKEN_INT_CONST;
        return;
    }

    if(isalpha(c) || c=='_') {
        while((isalnum(input[pos])||input[pos]=='_') && i<MAX_TOKEN-1) currentToken[i++] = input[pos++];
        currentToken[i]='\0';
        currentType = isKeyword(currentToken) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return;
    }

    // fallback
    currentToken[0]=c; currentToken[1]='\0'; currentType=TOKEN_SYMBOL; pos++;
}

// ----------------- GETTERS -----------------
TokenType tokenType() { return currentType; }
const char* keyword() { return currentType==TOKEN_KEYWORD ? currentToken : NULL; }
char symbol() { return currentType==TOKEN_SYMBOL ? currentToken[0] : '\0'; }
const char* identifier() { return currentType==TOKEN_IDENTIFIER ? currentToken : NULL; }
int intVal() { return currentType==TOKEN_INT_CONST ? atoi(currentToken) : 0; }
const char* stringVal() { return currentType==TOKEN_STRING_CONST ? currentToken : NULL; }
