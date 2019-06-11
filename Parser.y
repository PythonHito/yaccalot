%{
#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

int yyerror(SExpression **expression, yyscan_t scanner, const char *msg) {
    /* Add error handling routine as needed */
}

%}

%code requires {
  typedef void* yyscan_t;
}

%output  "Parser.c"
%defines "Parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { SExpression **expression }
%parse-param { yyscan_t scanner }

%union {
    char* value;
    SExpression *expression;
}

%token EXCLAMATION "!"
%token LEFT_SQUARE "["
%token RIGHT_SQUARE "]"
%token LEFT_BANANA "("
%token RIGHT_BANANA ")"
%token <value> WORD "word"

%type <expression> expr
%left "!"

%%

input
    : expr { *expression = $1; }
    ;

expr
    : "!"expr[E] {$$ = createUnaryOperation(eINVERT, $E); }
    | expr[L]"["expr[R]"]" {$$ = createOperation(eCAPITALISE, $L, $R);  }
    | "word"[W] {$$ = createString($W); } 
    | "("expr[E]")" {$$ = $E;}
    ;
%%
