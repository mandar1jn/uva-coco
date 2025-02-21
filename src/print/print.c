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
  printf("TODO");
  return node;
}

/**
 * @fn PRTdecls
 */
node_st *PRTdecls(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTexprs
 */
node_st *PRTexprs(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTarrexpr
 */
node_st *PRTarrexpr(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTids
 */
node_st *PRTids(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTexprstmt
 */
node_st *PRTexprstmt(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTreturn
 */
node_st *PRTreturn(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTfuncall
 */
node_st *PRTfuncall(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTcast
 */
node_st *PRTcast(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTfundefs
 */
node_st *PRTfundefs(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTfundef
 */
node_st *PRTfundef(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTfunbody
 */
node_st *PRTfunbody(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTifelse
 */
node_st *PRTifelse(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTwhile
 */
node_st *PRTwhile(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTdowhile
 */
node_st *PRTdowhile(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTfor
 */
node_st *PRTfor(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTglobdecl
 */
node_st *PRTglobdecl(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTglobdef
 */
node_st *PRTglobdef(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTparam
 */
node_st *PRTparam(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTvardecl
 */
node_st *PRTvardecl(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTstmts
 */
node_st *PRTstmts(node_st *node) {
  printf("TODO");
  return node;
}

/**
 * @fn PRTassign
 */
node_st *PRTassign(node_st *node) {
  printf("TODO");
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
  printf("TODO");
  return node;
}

/**
 * @fn PRTvar
 */
node_st *PRTvar(node_st *node) {
  printf("TODO");
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
