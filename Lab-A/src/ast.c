#include "ast.h"
#include <stdlib.h>
#include <string.h>

struct ast *make_binop(enum binop_type type, struct ast *left, struct ast *right) {
    struct ast *res = malloc(sizeof(struct ast));
    res->type = AST_BINOP;
    res->as_binop.type = type;
    res->as_binop.left = left;
    res->as_binop.right = right;
    return res;
}

struct ast *make_unop(enum unop_type type, struct ast *child) {
    struct ast *res = malloc(sizeof(struct ast));
    res->type = AST_UNOP;
    res->as_unop.type = type;
    res->as_unop.subtree = child;
    return res;
}

struct ast *make_var(char *name) {
    struct ast *res = malloc(sizeof(struct ast));
    res->type = AST_VAR;
    size_t name_size = strlen(name);
    char *name_copy = malloc(sizeof(char) * name_size + 1);
    memcpy(name_copy, name, name_size + 1);
    res->as_var.name = name_copy;
    return res;
}

static size_t _ast_to_string(struct ast *ast, char *buf);

static size_t ast_binop_to_string(struct ast_binop *binop, char *buf) {
    char* ptr = buf;

    ptr++[0] = '(';

    switch (binop->type) {
        case BINOP_AND:
            ptr++[0] = '&';
            break;
        case BINOP_IMP:
            ptr++[0] = '-';
            ptr++[0] = '>';
            break;
        case BINOP_OR:
            ptr++[0] = '|';
            break;
    }

    ptr++[0] = ',';
    ptr += _ast_to_string(binop->left, ptr);
    ptr++[0] = ',';
    ptr += _ast_to_string(binop->right, ptr);
    ptr++[0] = ')';

    return ptr - buf;
}

static size_t ast_unop_to_string(struct ast_unop *unop, char *buf) {
    char* ptr = buf;

    ptr++[0] = '(';
    switch (unop->type) {
        case UNOP_NEG:
            ptr++[0] = '!';
            break;
    }

    ptr += _ast_to_string(unop->subtree, ptr);
    ptr++[0] = ')';

    return ptr - buf;
}

static size_t ast_var_to_string(struct ast_name* var, char* buf) {
    size_t len = strlen(var->name);

    memcpy(buf, var->name, len);
    return len;
}

static size_t _ast_to_string(struct ast *ast, char *buf) {
    switch (ast->type) {
        case AST_BINOP:
            return ast_binop_to_string(&(ast->as_binop), buf);
        case AST_UNOP:
            return ast_unop_to_string(&(ast->as_unop), buf);
        case AST_VAR:
            return ast_var_to_string(&(ast->as_var), buf);
    }
}

void ast_to_string(struct ast *ast, char *buf) {
    size_t size = _ast_to_string(ast, buf);
    buf[size] = '\0';
}

