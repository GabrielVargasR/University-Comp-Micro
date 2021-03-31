#include "headers/records.h"
int extract_op(op_rec op)
{
    return op.operator;
}

string * extract_expr(expr_rec * expr)
{
    switch (expr->kind) {
        case LITERALEXPR:
            return (string *) expr->val;
        case IDEXPR:
        case TEMPEXPR:
        default:
            return (string *) expr->name;
    }
}