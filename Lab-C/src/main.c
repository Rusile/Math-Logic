#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "parser.h"
#include "ast.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define MEM_SIZE 102400000
#define AXIOMS_COUNT 10

extern ast** context;
extern size_t context_size = 0;
extern ast** proof;
extern size_t proof_size = 0;
extern ast* res;

void create_axioms(ast **axioms, struct ast *memory[3]);

bool is_axiom(ast *node, ast **table, ast **axioms);

void clear_memory(ast **table);

bool is_blank(char *str);

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

void read_input() {
    char* line = malloc(MEM_SIZE);
    getLine(line, MEM_SIZE);
    parse_header(line, context, &context_size, &res);
    while (getLine(line, MEM_SIZE) != NO_INPUT) {
        if (!is_blank(line)) {
            proof[proof_size++] = ast_parse(line);
        }
    }
}

void case_is_axiom(const char* st, const char* a) {
    printf("%s->(%s->%s)\n", st, a, st);
    printf("(%s)\n", st);
}

void case_is_equal_to_a(const char* st, const char* a) {
    char a_impl_a[50];
    sprintf(a_impl_a, "(%s->%s)", a, a);
    printf("%s->%s\n", a, a_impl_a);
    char temp1[50], temp2[50], temp3[50];
    sprintf(temp1, "(%s->%s)", a, a_impl_a);
    sprintf(temp2, "(%s->(%s->%s))", temp1, a_impl_a, a);
    sprintf(temp3, "(%s->%s)->%s", temp2, a_impl_a);
    printf("%s\n", temp3);
    printf("%s->%s->%s\n", a, a_impl_a, a);
}

int main() {
    //creating all axioms
    ast *axioms[AXIOMS_COUNT] = {NULL};
    struct ast *memory[3] = {NULL};
    create_axioms(axioms, memory);


    char *buffer = malloc(MEM_SIZE);

    getLine(buffer, MEM_SIZE); // get str from stdin
    struct ast *ast = ast_parse(buffer);

    printf("%d", is_axiom(ast, memory, axioms));

    memory[0] = NULL;
    memory[1] = NULL;
    memory[2] = NULL;
    return 0;

}

void create_axioms(ast **axioms, struct ast *memory[3]) {
    struct ast *a = place(memory + 0);
    struct ast *b = place(memory + 1);
    struct ast *c = place(memory + 2);

    axioms[0] = impl(a, impl(b, a));

    axioms[1] = impl(impl(a, b), impl(
            impl(a, impl(b, c)),
            impl(a, c)));

    axioms[2] = impl(a, impl(b, conj(a, b)));

    axioms[3] = impl(conj(a, b), a);

    axioms[4] = impl(conj(a, b), b);

    axioms[5] = impl(a, disj(a, b));

    axioms[6] = impl(b, disj(a, b));

    axioms[7] = impl(
            impl(a, c),
            impl(impl(b, c), impl(disj(a, b), c))
    );

    axioms[8] = impl(
            impl(a, b),
            impl(impl(a, neg(b)), neg(a))
    );

    axioms[9] = impl(neg(neg(a)), a);
}

bool is_axiom(ast *node, ast **table, ast **axioms) {
    for (size_t i = 0; i < AXIOMS_COUNT; i++) {
        clear_memory(table);
        if (ast_equals(axioms[i], node)) {
            return true;
        }
    }

    return false;
}

void clear_memory(ast **table) {
    table[0] = NULL;
    table[1] = NULL;
    table[2] = NULL;
}

bool is_blank(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) {
            return false;
        }
    }
    return true;
}