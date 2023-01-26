#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "parser.h"
#include "ast.h"

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
    char* buffer = malloc(MEM_SIZE);
    getLine(buffer, MEM_SIZE); // get str from stdin
    struct ast* ast = ast_parse(buffer);
    ast_to_string(ast, buffer);
    printf("%s", buffer);
    return 0;
}
