#include "parser.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>

static int indent = 0;
void printIndent() { for(int i=0;i<indent;i++) printf("  "); }

void printToken() {
    printIndent();
    switch(tokenType()) {
        case TOKEN_KEYWORD:      printf("<keyword> %s </keyword>\n", keyword()); break;
        case TOKEN_SYMBOL:       printf("<symbol> %c </symbol>\n", symbol()); break;
        case TOKEN_IDENTIFIER:   printf("<identifier> %s </identifier>\n", identifier()); break;
        case TOKEN_INT_CONST:    printf("<integerConstant> %d </integerConstant>\n", intVal()); break;
        case TOKEN_STRING_CONST: printf("<stringConstant> %s </stringConstant>\n", stringVal()); break;
        default: break;
    }
}

// ---------------- Parser ----------------
void compileClass();
void compileSubroutine();
void compileStatements();
void compileExpression();
void compileTerm();

// ---------------- compileClass ----------------
void compileClass() {
    printf("<class>\n"); indent++;
    advance(); printToken();        // class
    advance(); printToken();        // className
    advance(); printToken();        // {
    
    while(hasMoreTokens()) {
        advance();
        if(tokenType()==TOKEN_KEYWORD && (strcmp(keyword(),"function")==0)) {
            compileSubroutine();
        } else if(tokenType()==TOKEN_SYMBOL && symbol()=='}') {
            printToken(); break;
        }
    }

    indent--; printf("</class>\n");
}

// ---------------- compileSubroutine ----------------
void compileSubroutine() {
    printf("<subroutineDec>\n"); indent++;
    printToken();                   // 'function'
    advance(); printToken();        // return type
    advance(); printToken();        // subroutine name
    advance(); printToken();        // '('
    printf("<parameterList/>\n");   // skip parameters for simplicity
    advance(); printToken();        // ')'
    
    advance(); printToken();        // '{'
    compileStatements();
    advance(); printToken();        // '}'
    
    indent--; printf("</subroutineDec>\n");
}

// ---------------- compileStatements ----------------
void compileStatements() {
    printf("<statements>\n"); indent++;
    while(tokenType()==TOKEN_KEYWORD && (strcmp(keyword(),"let")==0 || strcmp(keyword(),"do")==0 || strcmp(keyword(),"return")==0)) {
        printToken();               // statement keyword
        advance();
        while(tokenType()!=TOKEN_SYMBOL || symbol()!=';') { advance(); printToken(); }
        advance(); printToken();     // ';'
        if(!hasMoreTokens()) break;
    }
    indent--; printf("</statements>\n");
}

// ---------------- compileExpression ----------------
void compileExpression() {
    printf("<expression>\n"); indent++;
    compileTerm();
    while(tokenType()==TOKEN_SYMBOL && strchr("+-*/&|<>=~",symbol())) {
        printToken();
        advance();
        compileTerm();
    }
    indent--; printf("</expression>\n");
}

// ---------------- compileTerm ----------------
void compileTerm() {
    printf("<term>\n"); indent++;
    if(tokenType()==TOKEN_INT_CONST || tokenType()==TOKEN_STRING_CONST || tokenType()==TOKEN_IDENTIFIER) {
        printToken();
    } else if(tokenType()==TOKEN_SYMBOL && symbol()=='(') {
        printToken();
        advance(); compileExpression();
        advance(); printToken(); // ')'
    } else if(tokenType()==TOKEN_SYMBOL && strchr("-~",symbol())) {
        printToken();
        advance(); compileTerm();
    }
    indent--; printf("</term>\n");
}
