#include "ast.h"
#include "bison/gen/Expression.tab.h"
#include "bison/gen/Expression.lexer.h"
#include <stdio.h>
#include <string.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define MEM_SIZE 102400000

extern struct ast* result;

void yyerror(const char *error) {
    fprintf(stderr, "Error: %s", error);
}

int yywrap() {
    return 1;
}

static int getLine (char *buff, size_t sz) {
    int ch, extra;

    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff)-1] = '\0';
    return OK;
}

int main() {
    char* input = malloc(MEM_SIZE);
    getLine(input, MEM_SIZE); // get str from stdin

    yy_scan_string(input);
    yyparse();

    char* buf = malloc(MEM_SIZE);
    ast_to_string(result, buf);

    printf("%s", buf);
    return 0;
}
