%{


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "palm/memory.h"
#include "palm/ctinfo.h"
#include "palm/dbug.h"
#include "palm/str.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "global/globals.h"

static node_st *parseresult = NULL;
extern int yylex();
int yyerror(char *errname);
extern FILE *yyin;
void AddLocToNode(node_st *node, void *begin_loc, void *end_loc);


%}

%union {
 char               *id;
 int                 cint;
 float               cflt;
 node_st             *node;
}

%locations

%token BRACKET_L BRACKET_R SQUARE_L SQUARE_R CURLY_L CURLY_R SEMICOLON
%token TRUEVAL FALSEVAL
%token IF WHILE DO FOR RETURN
%token VOID EXTERN EXPORT

%left COMMA
%right LET
%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left STAR SLASH PERCENT
%right NOT

%token <cint> INT
%token <cflt> FLOAT
%token <id> ID

%type <node> intval floatval boolval constant expr
%type <node> stmts stmt assign varlet program
%type <node> binop unop

%start program

%%

program:    stmts
            {
                parseresult = ASTprogram($1);
            }
            ;

stmts:  stmt stmts
        {
            $$ = ASTstmts($1, $2);
        }
        | stmt
        {
            $$ = ASTstmts($1, NULL);
        }
        ;

stmt:   assign
        {
            $$ = $1;
        }
        ;

assign: varlet LET expr SEMICOLON
        {
            $$ = ASTassign($1, $3);
        }
        ;

varlet: ID
        {
            $$ = ASTvarlet($1);
            AddLocToNode($$, &@1, &@1);
        }
        ;


expr:   BRACKET_L expr BRACKET_R
        {
            $$ = $2;
        } 
        | constant
        {
            $$ = $1;
        }
        | ID
        {
            $$ = ASTvar($1);
        }
        | binop
        {
            $$ = $1;
        }
        | unop
        {
            $$ = $1;
        }
        ;

constant:   floatval
            {
                $$ = $1;
            }
            | intval
            {
                $$ = $1;
            }
            | boolval
            {
                $$ = $1;
            }
            ;

floatval:   FLOAT
            {
                $$ = ASTfloat($1);
            }
            ;

intval: INT
        {
        $$ = ASTnum($1);
        }
        ;

boolval:    TRUEVAL
            {
                $$ = ASTbool(true);
            }
            | FALSEVAL
            {
                $$ = ASTbool(false);
            }
            ;

binop:  expr[left] PLUS expr[right] 
        {
            $$ = ASTbinop($left, $right, BO_add);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] MINUS expr[right]
        {
            $$ = ASTbinop($left, $right, BO_sub);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] STAR expr[right]
        {
            $$ = ASTbinop($left, $right, BO_mul);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] SLASH expr[right]
        {
            $$ = ASTbinop($left, $right, BO_div);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] PERCENT expr[right]
        {
            $$ = ASTbinop($left, $right, BO_mod);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] LE expr[right]
        {
            $$ = ASTbinop($left, $right, BO_le);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] LT expr[right]
        {
            $$ = ASTbinop($left, $right, BO_lt);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] GE expr[right]
        {
            $$ = ASTbinop($left, $right, BO_ge);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] GT expr[right]
        {
            $$ = ASTbinop($left, $right, BO_gt);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] EQ expr[right]
        {
            $$ = ASTbinop($left, $right, BO_eq);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] NE expr[right]
        {
            $$ = ASTbinop($left, $right, BO_ne);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] OR expr[right]
        {
            $$ = ASTbinop($left, $right, BO_or);
            AddLocToNode($$, &@left, &@right);
        }
        | expr[left] AND expr[right]
        {
            $$ = ASTbinop($left, $right, BO_and);
            AddLocToNode($$, &@left, &@right);
        }
        ;

unop:   MINUS[op] expr[right]
        {
            $$ = ASTunop($right, UO_neg);
            AddLocToNode($$, &@op, &@right);
        }
        | NOT[op] expr[right]
        { 
            $$ = ASTunop($right, UO_not);
            AddLocToNode($$, &@op, &@right);
        }
        ;

%%

void AddLocToNode(node_st *node, void *begin_loc, void *end_loc)
{
    // Needed because YYLTYPE unpacks later than top-level decl.
    YYLTYPE *loc_b = (YYLTYPE*)begin_loc;
    YYLTYPE *loc_e = (YYLTYPE*)end_loc;
    NODE_BLINE(node) = loc_b->first_line;
    NODE_BCOL(node) = loc_b->first_column;
    NODE_ELINE(node) = loc_e->last_line;
    NODE_ECOL(node) = loc_e->last_column;
}

int yyerror(char *error)
{
    CTI(CTI_ERROR, true, "line %d, col %d\nError parsing source code: %s\n",
                global.line, global.col, error);
    CTIabortOnError();
    return 0;
}

node_st *SPdoScanParse(node_st *root)
{
    DBUG_ASSERT(root == NULL, "Started parsing with existing syntax tree.");
    yyin = fopen(global.input_file, "r");
    if (yyin == NULL) {
        CTI(CTI_ERROR, true, "Cannot open file '%s'.", global.input_file);
        CTIabortOnError();
    }
    yyparse();
    return parseresult;
}
