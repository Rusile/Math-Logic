#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "parser.h"
#include "ast.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define MEM_SIZE 102400000
#define AXIOMS_COUNT 10

void create_axioms(ast **axioms);

bool is_axiom(ast* node, ast** table, ast** axioms);

void clear_memory(ast** table);

static int getLine(char *buff, size_t sz) {
    int ch, extra;

    if (fgets(buff, sz, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff) - 1] = '\0';
    return OK;
}

int main() {
    //creating all axioms
    ast *axioms[AXIOMS_COUNT] = {NULL};
    create_axioms(axioms);


    struct ast *memory[3] = {NULL};

    struct ast *a = place(memory + 0);
    struct ast *b = place(memory + 1);
    struct ast *axiom_1 = impl(a, impl(b, a));

    char *buffer = malloc(MEM_SIZE);

    getLine(buffer, MEM_SIZE); // get str from stdin
    struct ast *ast = ast_parse(buffer);

    printf("%d", ast_equals(axiom_1, ast));

    memory[0] = NULL;
    memory[1] = NULL;
    memory[2] = NULL;
    return 0;
}

void create_axioms(ast **axioms) {
    struct ast *a = place(axioms + 0);
    struct ast *b = place(axioms + 1);
    struct ast *c = place(axioms + 2);

    axioms[0] = impl(a, impl(b, a));

    axioms[1] = impl(impl(a, b),impl(
                    impl(a, impl(b, c)),
                    impl(a, c)));

    axioms[2] =   impl(a, impl(b, conj(a, b)));

    axioms[3] = impl(conj(a, b), a);

    axioms[4] = impl(conj(a, b), b);

    axioms[5] = impl(a, disj(a, b));

    axioms[6] = impl(b, disj(a, b));

    axioms[7] = impl(
            impl(a, c),
            impl(impl(b, c), impl(disj(a, b), c))
    );

    axioms[8] =  impl(
            impl(a, b),
            impl(impl(a, neg(b)), neg(a))
    );

    axioms[9] = impl(neg(neg(a)), a);
}

bool is_axiom(ast* node, ast** table, ast** axioms) {
    for (size_t i = 0; i < AXIOMS_COUNT; i++) {
        clear_memory(table);
        if (ast_equals(node, axioms[i])) {
            return true;
        }
    }
    return false;
}

void clear_memory(ast** table) {
    table[0] = NULL;
    table[1] = NULL;
    table[2] = NULL;
}