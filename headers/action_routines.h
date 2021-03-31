#ifndef ACTION_ROUTINES_H
#define ACTION_ROUTINES_H
#include "records.h"

void start(void);
void finish(void);
void assign(expr_rec * target, expr_rec * source);
op_rec process_op(void);
expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2);
void read_id(expr_rec in_var);
expr_rec process_id(void);
expr_rec process_literal(void);
void write_expr(expr_rec out_expr);

#endif