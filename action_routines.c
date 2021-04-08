#include <stdio.h>
#include <string.h>
#include "headers/records.h"
#include "headers/generator.h"
#include "headers/parser_aux.h"
#include "headers/ids.h"

void start(void)
{
    // No semantic initializations needed
    // TODO: eliminate or modify if needed
    generate((string *) ".global _start", (string *) "", (string *) "", (string *) "");
    generate((string *) ".section .text", (string *) "", (string *) "", (string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");
    generate((string *) "_start:", (string *) "", (string *) "", (string *) "");
}

void finish(void)
{
    // Generates the code to finish the program
    generate((string *) "mov", (string *) "r7,", (string *) "#0x1", (string *) "");
    generate((string *) "mov", (string *) "r0,", (string *) "#13", (string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");
    generate((string *) "swi", (string *) "0", (string *) "", (string *) "");
}

void assign(expr_rec * target, expr_rec * source)
{
    // Generates the code for assignment
    // Target: where the source is going to be saved
    // A := 5 -> target = A
    generate((string *) "Store", (string *) extract_expr(source), (string *) target->name, (string *) "");
}

op_rec process_op()
{
    // Produce operator descriptor
    op_rec o;

    if (current_token == PLUSOP){
        o.operator = PLUS;
    } else {
        o.operator = MINUS;
    }
    return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2)
{
    // Generate code for infix operation
    // Get result temp and set up semantic record for result

    // Sets up temp expression
    expr_rec e_rec;
    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, get_temp());

    generate(extract_op(&op), extract_expr(&e1), extract_expr(&e2), (string *) e_rec.name);
    return e_rec;
}

expr_rec gen_conditional(expr_rec e1, expr_rec e2, expr_rec e3)
{
    expr_rec e_rec;
    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, get_temp());

    generate((string *) "if", extract_expr(&e1), extract_expr(&e2), extract_expr(&e3));
    return e_rec;
}

void read_id(expr_rec in_var)
{
    // Generate code for read
    generate((string *)"Read", (string *)in_var.name, (string *)"Integer", (string *)"");
}

expr_rec process_id(void)
{
    // Declare ID and build a corresponding semantic record
    expr_rec t;

    check_id(token_buffer);
    t.kind = IDEXPR;
    strcpy(t.name, token_buffer);
    return t;
}

expr_rec process_literal(void)
{
    // Converts literal to a numeric representation
    // and builds semantic record

    expr_rec t;
    t.kind = LITERALEXPR;
    sscanf(token_buffer, "%d", & t.val); // lee el número completo en el buffer y lo deja en t.val
    return t;
}

void write_expr(expr_rec out_expr)
{
    // Generate code for write
    generate((string *)"Write", (string *)extract_expr(&out_expr), (string *)"Integer", (string *)"");
}
