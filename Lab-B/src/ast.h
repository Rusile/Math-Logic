#ifndef MATH_LOG_1_EXPRESSION_H
#define MATH_LOG_1_EXPRESSION_H

#include <stdio.h>
#include "hash_map.h"

struct ast {
    enum {
        AST_VAR,
        AST_UNOP,
        AST_BINOP
    } type;
    union {
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
};

struct ast* make_binop(enum binop_type type, struct ast* left, struct ast* right); 
struct ast* make_unop(enum unop_type type, struct ast* child); 
struct ast* make_var(char* name);
void ast_to_string(struct ast* ast, char* buf);
void add_var_to_map(HashTable** table, struct ast *ast_var);
int64_t execute_ast_expression(struct ast *ast, int64_t mask, HashTable* table);

#endif
