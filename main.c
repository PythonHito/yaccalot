#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

#include <stdio.h>
#include <ctype.h>

int yyparse(SExpression **expression, yyscan_t scanner);

SExpression *getAST(const char *expr)
{
    SExpression *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        /* could not initialize */
        return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&expression, scanner)) {
        /* error parsing */
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return expression;
}

char* capitalSlice(char *left, char *right)
{
	char character[] = {' ', '\0'};
	for (int i = 0; i < strlen(left); i++){
		character[0] = left[i];
		if (strstr(right, character)){
			left[i] = toupper(left[i]);
		}
	}
	return left;
}

char* invert(char *operand)
{
        for (int i = 0; i < strlen(operand); i++){
                if (islower(operand[i])){
                        operand[i] = toupper(operand[i]);
                } else {
			operand[i] = tolower(operand[i]);
		}
        }       
        return operand;
}

char* evaluate(SExpression *e)
{
    switch (e->type) {
        case eVALUE:
            return e->value;
        case eCAPITALISE:
            return capitalSlice(evaluate(e->left), evaluate(e->right));
        case eINVERT:
            return invert(evaluate(e->left));
        default:
            /* should not be here */
            return 0;
    }
}

int main(void)
{
    char test[100];
    fgets(test, 100, stdin);
    SExpression *e = getAST(test);
    char* result = evaluate(e);
    printf("Result of '%s' is %s\n", test, result);
    deleteExpression(e);
    return 0;
}
