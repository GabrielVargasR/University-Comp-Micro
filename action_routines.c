#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "headers/records.h"
#include "headers/generator.h"
#include "headers/parser_aux.h"
#include "headers/ids.h"

string* type_expr(string * expr){
    string *str;
    str = malloc(sizeof(string));
    if (isalpha(*expr[0])) {
    	strcpy(*str, "=");
        strcat(*str,*expr);
    }else{
	strcpy(*str, "#");
        strcat(*str,*expr);
    }
    return str; 
}

void start(void)
{
    // No semantic initializations needed
    // TODO: eliminate or modify if needed
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
    if (*type_expr(extract_expr(source))[0] == '='){
    	generate((string *) "ldr", (string *) "r8,", type_expr(extract_expr(source)), (string *) "");
        generate((string *) "ldr", (string *) "r8,", (string *) "[r8]", (string *) "");
    }else{
        generate((string *) "mov", (string *) "r8,", type_expr(extract_expr(source)), (string *) "");
    }
    generate((string *) "ldr", (string *) "r9,", type_expr((string *)target->name), (string *) "");
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
    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, get_temp());

    generate((string *)"@_operation:", (string *)"", (string *)"", (string *)""); //TODO: eliminate

    // Prepares first operand
    if (e1.kind == LITERALEXPR) {
        generate((string *) "mov", (string *) "r0,", type_expr(extract_expr(&e1)), (string *) "");
    } else {
        generate((string *) "ldr", (string *) "r0,", type_expr(extract_expr(&e1)), (string *) "");
        generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
    }

    // Prepares second operand
    if (e2.kind == LITERALEXPR) {
        generate((string *) "mov", (string *) "r1,", type_expr(extract_expr(&e2)), (string *) "");
    } else {
        generate((string *) "ldr", (string *) "r1,", type_expr(extract_expr(&e2)), (string *) "");
        generate((string *) "ldr", (string *) "r1,", (string *) "[r1]", (string *) "");
    }

    // Makes operation and stores in temp value
    generate(extract_op(&op), (string *) "r0,", (string *) "r0,", (string *) "r1");
    generate((string *) "ldr", (string *) "r9,", type_expr((string *)e_rec.name), (string *) "");
    generate((string *) "str", (string *) "r0,", (string *) "[r9]",(string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");

    return e_rec;
}

expr_rec gen_conditional(expr_rec e1, expr_rec e2, expr_rec e3)
{
    expr_rec e_rec;
    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, get_temp());

    string tag1 = "_";
    string tag2 = "_";
    strcat(tag1, get_temp());
    strcat(tag2, get_temp());

    //prepares e1 for comparison
    if (e1.kind == LITERALEXPR) {
        generate((string *) "mov", (string *)"r0,", type_expr(extract_expr(&e1)), (string *)"");
    } else {
        generate((string *) "ldr", (string *) "r0,", type_expr(extract_expr(&e1)), (string *) "");
        generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
    }

    //compares e1
    generate((string *) "cmp", (string *) "r0,", (string *)"#0", (string *) "");
    generate((string *) "beq", &tag1, (string *) "", (string *) "");

    //assigns e2 if no branch (e1 != 0)
    if (e2.kind == LITERALEXPR) {
        generate((string *) "mov", (string *) "r0,", type_expr(extract_expr(&e2)), (string *) "");
    } else {
        generate((string *) "ldr", (string *) "r0,", type_expr(extract_expr(&e2)), (string *) "");
        generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
    }
    generate((string *) "b", &tag2, (string *) "", (string *) "");

    //assigns e3 if beq branches (e1 == 0)
    generate(&tag1, (string *) ":", (string *) "", (string *) "");
    if (e3.kind == LITERALEXPR) {
        generate((string *) "mov", (string *) "r0,", type_expr(extract_expr(&e3)), (string *) "");
    } else {
        generate((string *) "ldr", (string *) "r0,", type_expr(extract_expr(&e3)), (string *) "");
        generate((string *) "ldr", (string *) "r0,", (string *) "[r0]", (string *) "");
    }
    generate(&tag2, (string *) ":", (string *) "", (string *) "");


    generate((string *) "ldr", (string *) "r9,", type_expr((string *)e_rec.name), (string *) "");
    generate((string *) "str", (string *) "r0,", (string *) "[r9]",(string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");
  
    return e_rec;
}

void read_id(expr_rec in_var)
{
    generate((string *)"@_read:", (string *)"", (string *)"", (string *)"");
    generate((string *)"ldr", (string *)"r0,", (string *)"=read_pattern", (string *)"");
    if (*type_expr(extract_expr(&in_var))[0] == '='){
    	generate((string *)"ldr", (string *)"r1,", type_expr(extract_expr(&in_var)), (string *)"");
    }else{
        generate((string *)"mov", (string *)"r1,", type_expr(extract_expr(&in_var)), (string *)"");
    }
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
    if (*type_expr(extract_expr(&out_expr))[0] == '='){
    	generate((string *)"ldr", (string *)"r1,", type_expr(extract_expr(&out_expr)), (string *)"");
    }else{
        generate((string *)"mov", (string*)"r1,", type_expr(extract_expr(&out_expr)), (string *)"");
    }
    generate((string *)"ldr", (string *)"r1,",(string *)"[r1]", (string *)"");
    generate((string *) "bl", (string *) "printf", (string *) "", (string *) "");
    generate((string *) "", (string *) "", (string *) "", (string *) "");   
}
