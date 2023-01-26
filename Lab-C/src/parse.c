//
// Created by ildar on 26.01.2023.
//
#include <string.h>
#include <stdlib.h>
#include "ast.h"

extern struct ast* result;
extern struct vector* vc;

void yyerror(const char *error) {
    fprintf(stderr, "Error: %s", error);
}

int yywrap() {
    return 1;
}

struct ast* parse_expression(const char* src) {
    yy_scan_string(src);
    yyparse();
    return result;
}

void parse_header(
        const char* src,
        struct ast** assumptions,
        int* num_assumptions,
        struct ast** res
) {
    char* copy = strdup(src);
    char* token = strtok(copy, ",");
    while (token != NULL) {
        size_t deduce_pos = strstr(token, "|-") - token;
        if (deduce_pos == -1) {
            assumptions[*num_assumptions] = parse_expression(token);
            (*num_assumptions)++;
        } else {
            assumptions[*num_assumptions] = parse_expression(token);
            (*num_assumptions)++;
            *res = parse_expression(token + deduce_pos + 2);
        }
        token = strtok(NULL, ",");
    }
    free(copy);
}