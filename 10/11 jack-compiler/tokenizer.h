// tokenizer.h
#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_SYMBOL,
    TOKEN_IDENTIFIER,
    TOKEN_INT_CONST,
    TOKEN_STRING_CONST,
    TOKEN_NONE
} TokenType;

// Initialize tokenizer with file content
void initTokenizer(const char *fileContent);

// Check if more tokens exist
int hasMoreTokens();

// Advance to next token
void advance();

// Get current token type
TokenType tokenType();

// Get token values
const char* keyword();
char symbol();
const char* identifier();
int intVal();
const char* stringVal();

#endif

