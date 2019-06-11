%{

#include "Expression.h"
#include "Parser.h"

#include <stdio.h>

%}

%option outfile="Lexer.c" header-file="Lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%%

[ \r\n\t]*   { continue; /* Skip blanks. */ }

"!"       { return EXCLAMATION; }
"["	  { return LEFT_SQUARE; }
"]" 	  { return RIGHT_SQUARE;}
"("	  { return LEFT_BANANA; }
")" 	  { return RIGHT_BANANA;}

[a-zA-Z0-9]+ { yylval->value = strdup(yytext); return WORD; }

.            { continue; /* Ignore unexpected characters. */}

%%

int yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    return 0;
}
