// semantic_analyzer.h
#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "symbol_table.h"
#include "parser.h"  // or AST node definitions

void analyzeClass();           // entry point
void analyzeSubroutine();      // analyze a subroutine
void analyzeStatements();      // statements in subroutine
void analyzeExpression();      // expressions
void analyzeTerm();            // terms

#endif
