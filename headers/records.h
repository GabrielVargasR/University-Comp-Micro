#ifndef RECORDS_H
#define RECORDS_H
#include "headers/scanner_aux.h"
typedef char string[MAX_ID_LEN];

enum expr { IDEXPR, LITERALEXPR, TEMPEXPR};

typedef struct operator {
    enum op {PLUS, MINUS} operator;
} op_rec;

typedef struct expression {
    enum expr kind;
    union {
        string name; // for IDEXPR, TEMPEXPR
        int val; // for LITERALEXPR
    };
} expr_rec;
#endif