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

void parse_header(
        const char* src,
        struct ast** assumptions,
        size_t* num_assumptions,
        struct ast** res
) {
    char* copy = strdup(src);
    char* token = strtok(copy, ",");
    while (token != NULL) {
        size_t deduce_pos = strstr(token, "|-") - token;
        if (deduce_pos == -1) {
            assumptions[*num_assumptions] = ast_parse(token);
            (*num_assumptions)++;
        } else {
            assumptions[*num_assumptions] = ast_parse(token);
            (*num_assumptions)++;
            *res = ast_parse(token + deduce_pos + 2);
        }
        token = strtok(NULL, ",");
    }
    free(copy); //TODO check
}