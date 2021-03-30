#include <stdio.h>
#include <string.h>
#include "headers/records.h"
#include "headers/generator.h"
#include "headers/parser_aux.h"
#include "headers/ids.h"

void start(void)
{
    // No semantic initializations needed
}

void finish(void)
{
    // Generates the code to finish the program
    generate("Halt", "", "", "");
}

void assign(expr_rec target, expr_rec source)
{
    // Generates the code for assignment
    generate("Store", extract(source), target.name, "");
}

op_rec process_op(void)
{
    // Produce operator descriptor
    op_rec o;

    // TODO: check if next_token() is the desired function here
    if (next_token() == PLUSOP){
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

    generate(extract(op), extract(e1), extract(e2), e_rec.name);
    return e_rec;
}


void read_id(expr_rec in_var)
{
    // Generate code for read
    generate("Read", in_var.name, "Integer", "");
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
    // and build semantic record

    expr_rec t;
    t.kind = LITERALEXPR;
    /*(void)*/ sscanf(token_buffer, "%d", & t.val); // lee el número completo en el buffer y lo deja en t.val
    return t;
}

void write_expr(expr_rec out_expr)
{
    // Generate code for write
    generate("Write", extract(out_expr), "Integer", "");
}