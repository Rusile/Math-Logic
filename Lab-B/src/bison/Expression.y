%{
#include "ast.h"
#include "hash_map.h"

int yylex(void);
void yyerror(const char *);

struct ast* result = 0;
HashTable* map = 0;
%}

%union {
struct ast* e;
char* name;
}

%token <name> NAME
%token IMP OR AND NEG
%token LEFT RIGHT
%token END

%right IMP
%left OR
%left AND
%left NEG

%type <e> Input Expression

%start Input

%%
Input: Expression { result = $1; }
     ;

Expression: Expression IMP Expression { $$ = make_binop(BINOP_IMP, $1, $3); }
    	  | Expression OR Expression  { $$ = make_binop(BINOP_OR,  $1, $3); }
    	  | Expression AND Expression { $$ = make_binop(BINOP_AND, $1, $3); }
          | NEG Expression            { $$ = make_unop(UNOP_NEG, $2);       }
          | LEFT Expression RIGHT     { $$ = $2;                            }
          | NAME                      { $$ = make_var($1);
          				          add_var_to_map(&map, $$);  		    }
          ;

%%