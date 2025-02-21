/**
 * @file
 *
 * This file contains the code for the Print traversal.
 * The traversal has the uid: PRT
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "palm/dbug.h"

/**
 * @fn PRTprogram
 */
node_st *PRTprogram(node_st *node) {
  
    TRAVdecls(node);

  return node;
}

/**
 * @fn PRTdecls
 */
node_st *PRTdecls(node_st *node) {
  printf("decls");
  return node;
}

/**
 * @fn PRTexprs
 */
node_st *PRTexprs(node_st *node) {

    TRAVexpr(node);

    if(EXPRS_NEXT(node) != NULL)
    {
        TRAVnext(node);
    }

  printf("exprs");

  return node;
}

/**
 * @fn PRTarrexpr
 */
node_st *PRTarrexpr(node_st *node) {
  printf("arrayexpr");
  return node;
}

/**
 * @fn PRTids
 */
node_st *PRTids(node_st *node) {
  printf("ids");
  return node;
}

/**
 * @fn PRTexprstmt
 */
node_st *PRTexprstmt(node_st *node) {
  printf("exprstmt");
  return node;
}

/**
 * @fn PRTreturn
 */
node_st *PRTreturn(node_st *node) {
  printf("return");
  return node;
}

/**
 * @fn PRTfuncall
 */
node_st *PRTfuncall(node_st *node) {
  printf("funcall");
  return node;
}

/**
 * @fn PRTcast
 */
node_st *PRTcast(node_st *node) {

  char* type;

  switch(CAST_TYPE(node))
  {
    case CT_int:
        type = "int";
        break;
    case CT_float:
        type = "float";
        break;
    case CT_bool:
        type = "bool";
        break;
    case CT_void:
        type = "void";
        break;
    default:
    case CT_NULL:
        printf("Found unknown type for cast.");
  }

  printf("Cast(%s, ", type);

  TRAVexpr(node);

  printf(")");

  return node;
}

/**
 * @fn PRTfundefs
 */
node_st *PRTfundefs(node_st *node) {
  printf("fundefs");
  return node;
}

/**
 * @fn PRTfundef
 */
node_st *PRTfundef(node_st *node) {
  printf("fundef");
  return node;
}

/**
 * @fn PRTfunbody
 */
node_st *PRTfunbody(node_st *node) {
  printf("funbody");
  return node;
}

/**
 * @fn PRTifelse
 */
node_st *PRTifelse(node_st *node) {
  printf("ifelse");
  return node;
}

/**
 * @fn PRTwhile
 */
node_st *PRTwhile(node_st *node) {
  printf("while");
  return node;
}

/**
 * @fn PRTdowhile
 */
node_st *PRTdowhile(node_st *node) {
  printf("dowhile");
  return node;
}

/**
 * @fn PRTfor
 */
node_st *PRTfor(node_st *node) {
  printf("for");
  return node;
}

/**
 * @fn PRTglobdecl
 */
node_st *PRTglobdecl(node_st *node) {
  printf("globdecl");
  return node;
}

/**
 * @fn PRTglobdef
 */
node_st *PRTglobdef(node_st *node) {
  printf("globdef");
  return node;
}

/**
 * @fn PRTparam
 */
node_st *PRTparam(node_st *node) {
  printf("param");
  return node;
}

/**
 * @fn PRTvardecl
 */
node_st *PRTvardecl(node_st *node) {
  printf("vardecl");
  return node;
}

/**
 * @fn PRTstmts
 */
node_st *PRTstmts(node_st *node) {
  printf("stmts");
  return node;
}

/**
 * @fn PRTassign
 */
node_st *PRTassign(node_st *node) {
  printf("assign");
  return node;
}

/**
 * @fn PRTbinop
 */
node_st *PRTbinop(node_st *node) {
  
    printf("BinOp(");

    TRAVleft(node);

    char* op;

    switch(BINOP_OP(node))
    {
        case BO_add:
            op = "+";
            break;
        case BO_sub:
            op = "-";
            break;
        case BO_mul:
            op = "*";
            break;
        case BO_div:
            op = "/";
            break;
        case BO_mod:
            op = "%%";
            break;
        case BO_lt:
            op = "<";
            break;
        case BO_le:
            op = "<=";
            break;
        case BO_gt:
            op = ">";
            break;
        case BO_ge:
            op = ">=";
            break;
        case BO_eq:
            op = "==";
            break;
        case BO_ne:
            op = "!=";
            break;
        case BO_and:
            op = "&&";
            break;
        case BO_or:
            op = "||";
            break;
        default:
        case BO_NULL:
            DBUG_ASSERT(false, "Found unknown binop.");
    }

    printf(" %s ", op);

    TRAVright(node);

    printf(")");

  return node;
}

/**
 * @fn PRTunop
 */
node_st *PRTunop(node_st *node) {
  
    char op;
    switch(UNOP_OP(node))
    {
        case UO_not:
            op = '!';
            break;
        case UO_neg:
            op = '-';
            break;
        default:
        case UO_NULL:
            DBUG_ASSERT(false, "Found unknown unop.");
    }

    printf("UnOp(%c", op);

    TRAVoperand(node);

    printf(")");


  return node;
}

/**
 * @fn PRTvarlet
 */
node_st *PRTvarlet(node_st *node) {
  printf("varlet");
  return node;
}

/**
 * @fn PRTvar
 */
node_st *PRTvar(node_st *node) {
  printf("Var(%s)", VAR_NAME(node));
  return node;
}

/**
 * @fn PRTnum
 */
node_st *PRTnum(node_st *node) {

  printf("Num[%d]", NUM_VAL(node));

  return node;
}

/**
 * @fn PRTfloat
 */
node_st *PRTfloat(node_st *node) {
  
    printf("Float[%f]", FLOAT_VAL(node));

  return node;
}

/**
 * @fn PRTbool
 */
node_st *PRTbool(node_st *node) {

  printf("Bool[%s]", BOOL_VAL(node)? "true" : "false");

  return node;
}
