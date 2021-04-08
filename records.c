#include "headers/records.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
string * extract_op(op_rec * op)
{
    string * str;
    str = malloc(sizeof(string));

    switch (op->operator) {
        case PLUS:
            strcpy(str, "add");
            return str;
        case MINUS:
            strcpy(str, "sub");
            return str;
        default:
            break;
    }
}

string * extract_expr(expr_rec * expr)
{
    string *str;
    switch (expr->kind) {
        case LITERALEXPR:
            str = malloc(sizeof(string));
            sprintf(str, "%d", expr->val);
            return str;
        case IDEXPR:
        case TEMPEXPR:
        default:
            return (string *) expr->name;
    }
}
