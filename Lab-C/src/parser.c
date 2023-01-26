#include "bison/gen/Expression.tab.h"
#include "bison/gen/Expression.lexer.h"
#include "parser.h"

extern struct ast* result;

void yyerror(const char *error) {
    fprintf(stderr, "Error: %s", error);
}

int yywrap() {
    return 1;
}

struct ast* ast_parse(char* string) {
    yy_scan_string(string);
    yyparse();
    return result;
}
