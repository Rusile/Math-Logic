#include "ast.h"
#include "vector.h"
#include "bison/gen/Expression.lexer.h"
#include <stdio.h>
#include <string.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define MEM_SIZE 102400000

extern struct ast* result;
extern struct vector* vc;

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


    int64_t true_count = 0;
    int64_t false_count = 0;
    int64_t max_mask_value = 1 << get_count(vc);

    for (int64_t i = 0; i < max_mask_value; i++) {

        int64_t res = execute_ast_expression(result, i, vc);

        if (res) {
            true_count++;
        } else {
            false_count++;
        }
    }

    if (true_count == 0) {
        printf("Unsatisfiable");
    } else if (false_count == 0) {
        printf("Valid");
    } else {
        printf("Satisfiable and invalid, %d true and %d false cases", true_count, false_count);
    }

    return 0;
}


