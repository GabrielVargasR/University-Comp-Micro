#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/records.h"
#include "headers/generator.h"
#include "headers/parser_aux.h"
#include "headers/ids.h"

string *prep_name(expr_rec *e)
{
    string *str;
    str = malloc(sizeof(string));

    if (e->kind == LITERALEXPR){
        strcpy(*str, "#");
        strcat(*str, *extract_expr(e));
    } else {
        strcpy(*str, "=");
        strcat(*str, *extract_expr(e));
    }
    return str;
}

void start(void)
{
    // Generates the code to start the program
    generate((string *) ".global main", (string *) "", (string *) "", (string *) "");
    generate((string *) ".section .text", (string *) "", (string *) "", (string *) "");
    generate((string *) ".extern printf", (string *) "", (string *) "", (string *) "");
    generate((string *) ".extern scanf", (string *) "", (string *) "", (string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");
    generate((string *) "main:", (string *) "", (string *) "", (string *) "");
}

void finish(void)
{
    // Generates the code to finish the program
    generate((string *)"_end:", (string *)"", (string *)"", (string *)"");
    generate((string *) "mov", (string *) "r7,", (string *) "#0x1", (string *) "");
    generate((string *) "mov", (string *) "r0,", (string *) "#13", (string *) "");
    generate((string *) "swi", (string *) "0", (string *) "", (string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");
}

void assign(expr_rec * target, expr_rec * source)
{
    // Generates the code for assignment
    // Target: where the source is going to be saved
    // A := 5 -> target = A
    generate((string *)"@_assign:", (string *)"", (string *)"", (string *)"");
    if (source->kind == LITERALEXPR){
        generate((string *) "mov", (string *) "r8,", prep_name(source), (string *) "");
    }else{
        generate((string *) "ldr", (string *) "r8,", prep_name(source), (string *) "");
        generate((string *) "ldr", (string *) "r8,", (string *) "[r8]", (string *) "");
    }
    generate((string *) "ldr", (string *) "r9,", prep_name(target), (string *) "");
    generate((string *) "str", (string *) "r8,", (string *) "[r9]",(string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");
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

    int res;
    if (e1.kind == LITERALEXPR && e2.kind == LITERALEXPR){
        if (op.operator == PLUS) res = e1.val + e2.val;
        else res = e1.val - e2.val;

        printf("%d %s %d = %d\n", e1.val, extract_op(&op), e2.val, res);
        e_rec.kind = LITERALEXPR;
        e_rec.val = res;
    } else {
        e_rec.kind = TEMPEXPR;
        strcpy(e_rec.name, get_temp(VARIABLE));

        generate((string *)"@_operation:", (string *)"", (string *)"", (string *)""); //TODO: eliminate

        // Prepares first operand
        if (e1.kind == LITERALEXPR) {
            generate((string *) "mov", (string *) "r0,", prep_name(&e1), (string *) "");
        } else {
            generate((string *) "ldr", (string *) "r0,", prep_name(&e1), (string *) "");
            generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
        }

        // Prepares second operand
        if (e2.kind == LITERALEXPR) {
            generate((string *) "mov", (string *) "r1,", prep_name(&e2), (string *) "");
        } else {
            generate((string *) "ldr", (string *) "r1,", prep_name(&e2), (string *) "");
            generate((string *) "ldr", (string *) "r1,", (string *) "[r1]", (string *) "");
        }

        // Makes operation and stores in temp value
        generate(extract_op(&op), (string *) "r0,", (string *) "r0,", (string *) "r1");
        generate((string *) "ldr", (string *) "r9,", prep_name(&e_rec), (string *) "");
        generate((string *) "str", (string *) "r0,", (string *) "[r9]",(string *) "");
        generate((string *) "", (string *) "", (string *) "", (string *) "");
    }



    return e_rec;
}

expr_rec gen_conditional(expr_rec e1, expr_rec e2, expr_rec e3)
{
    expr_rec e_rec;
    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, get_temp(VARIABLE));

    string *tag1 = (string *) get_temp(LABEL);
    string *tag2 = (string *) get_temp(LABEL);

    //prepares e1 for comparison
    if (e1.kind == LITERALEXPR) {
        generate((string *) "mov", (string *)"r0,", prep_name(&e1), (string *)"");
    } else {
        generate((string *) "ldr", (string *) "r0,", prep_name(&e1), (string *) "");
        generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
    }

    //compares e1
    generate((string *) "cmp", (string *) "r0,", (string *)"#0", (string *) "");
    generate((string *) "beq", tag1, (string *) "", (string *) "");

    //assigns e2 if no branch (e1 != 0)
    if (e2.kind == LITERALEXPR) {
        generate((string *) "mov", (string *) "r0,", prep_name(&e2), (string *) "");
    } else {
        generate((string *) "ldr", (string *) "r0,", prep_name(&e2), (string *) "");
        generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
    }
    generate((string *) "b", tag2, (string *) "", (string *) "");

    //assigns e3 if beq branches (e1 == 0)
    generate(tag1, (string *) ":", (string *) "", (string *) "");
    if (e3.kind == LITERALEXPR) {
        generate((string *) "mov", (string *) "r0,", prep_name(&e3), (string *) "");
    } else {
        generate((string *) "ldr", (string *) "r0,", prep_name(&e3), (string *) "");
        generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
    }
    generate(tag2, (string *) ":", (string *) "", (string *) "");


    generate((string *) "ldr", (string *) "r9,", prep_name(&e_rec), (string *) "");
    generate((string *) "str", (string *) "r0,", (string *) "[r9]",(string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");
  
    return e_rec;
}

void read_id(expr_rec in_var)
{
    generate((string *)"@_read:", (string *)"", (string *)"", (string *)"");
    generate((string *)"ldr", (string *)"r0,", (string *)"=read_pattern", (string *)"");
    generate((string *)"ldr", (string *)"r1,", prep_name(&in_var), (string *)"");
    generate((string *) "bl", (string *) "scanf", (string *) "", (string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");  
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
    generate((string *)"@_write:", (string *)"", (string *)"", (string *)"");
    generate((string *)"ldr", (string *)"r0,", (string *)"=message", (string *)"");
    if (out_expr.kind == LITERALEXPR){
    	generate((string *)"mov", (string*)"r1,", prep_name(&out_expr), (string *)"");
    }else{
        generate((string *)"ldr", (string *)"r1,", prep_name(&out_expr), (string *)"");
    }
    generate((string *)"ldr", (string *)"r1,",(string *)"[r1]", (string *)"");
    generate((string *) "bl", (string *) "printf", (string *) "", (string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");   
}
