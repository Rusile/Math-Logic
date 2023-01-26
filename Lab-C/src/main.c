#include "ast.h"
#include "vector.h"
#include "bison/gen/Expression.lexer.h"
#include "bison/gen/Expression.tab.h"
#include "parse.c"
#include <stdio.h>
#include <string.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define MEM_SIZE 102400000


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

    struct ast** assumptions = malloc(sizeof(struct ast*) * 5);
    int num_assumptions;
    struct ast* res;
    parse_header(input, assumptions, &num_assumptions, &res);
    printf("%d", num_assumptions);

    int64_t max_mask_value = 1 << get_count(vc);

    return 0;
}


