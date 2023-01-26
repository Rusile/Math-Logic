#ifndef MATH_LOG_1_EXPRESSION_H
#define MATH_LOG_1_EXPRESSION_H

#include <stdio.h>
#include <stdbool.h>


typedef struct ast {
    enum {
        AST_PLACE,
        AST_VAR,
        AST_UNOP,
        AST_BINOP
    } type;
    union {
        struct ast_place {
            struct ast** value;
        } as_place;
        struct ast_name {
            char* name;
        } as_var;
        struct ast_unop {
            enum unop_type{
                UNOP_NEG
            } type;
            struct ast* subtree;
        } as_unop;
        struct ast_binop {
            enum binop_type {
                BINOP_OR,
                BINOP_AND,
                BINOP_IMP
            } type;
            struct ast* left;
            struct ast* right;
        } as_binop;
    };
} ast;

struct ast* make_binop(enum binop_type type, struct ast* left, struct ast* right);
struct ast* make_unop(enum unop_type type, struct ast* child);
struct ast* make_var(char* name);

struct ast* impl(struct ast* left, struct ast* right);
struct ast* conj(struct ast* left, struct ast* right);
struct ast* disj(struct ast* left, struct ast* right);
struct ast* neg(struct ast* tree);
struct ast* place(struct ast** value);

void ast_to_string(struct ast* ast, char* buf);
bool ast_equals(ast *left, ast *right);

#endif
