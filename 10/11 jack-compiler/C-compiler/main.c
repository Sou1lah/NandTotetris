#include <ctype.h>
#include <stdio.h>
#define DS_IMPLMENTATION
#include "ds.h"


enum token_type{
  TOKEN_IDENTIFIER,
  TOKEN_LABEL,
  TOKEN_INPUT,
  TOKEN_IF,
  TOKEN_THEN,
  TOKEN_OUTPUT,
  TOKEN_GOTO,
  TOKEN_INTEGER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_EQUALS,
  INVALID,
};

const char *show_token(enum token_type type){
  switch(type){
    case TOKEN_IDENTIFIER:
      return "identifier";
    case TOKEN_LABEL:
      return "label";
    case TOKEN_INPUT:
      return "input";
    case TOKEN_IF:
      return "if";
    case TOKEN_THEN:
      return "then";
    case TOKEN_OUTPUT:
      return "output";
    case TOKEN_GOTO:
      return "goto";
    case TOKEN_INTEGER:
      return "integer";
    case TOKEN_PLUS:
      return "plus";
    case TOKEN_MINUS:
      return "minus";
    case TOKEN_EQUALS:
      return "equals";
      break;
    case INVALID:
      return "INVALID";
    }
}

struct lexer {
  char *buffer;
  unsigned int buffer_len;
  unsigned int pos;
  unsigned int read_next;
  char ch;
};


static char lexer_peek_char(struct lexer *l){
  if (l -> read_next >= l ->buffer_len){
    return EOF;
  }
  return l -> buffer [l -> read_next];
}

static char lexer_read_char(struct lexer *l){
  l ->ch = lexer_peek_char(l);

  l -> pos = l -> read_next;
  l -> read_next += 1;

  return l->ch;

}

static void skip_whitespaces(struct lexer *l){
  while (isspace(l->ch)){
    lexer_read_char(l);
  }
}



int main(){
  char *buffer = NULL;
  ds_io_read_file();

  printf("%s\n",buffer);
}
