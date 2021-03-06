#include <stdbool.h>
#include "headers/scanner.h"
#include "headers/parser.h"
#include "headers/parser_aux.h"
#include "headers/records.h"
#include "headers/action_routines.h"
#include <stdlib.h>

void system_goal(void)
{
    /* 15. <system goal> -> <program> SCANEOF #finish */
    init(); //queue for parser_aux
    program();
    match(SCANEOF);
    finish(); //action routine
}

void program(void)
{
    /* 1. <program> -> #start BEGIN <statement list> END */
    start(); //action routine
    match(BEGIN);
    statement_list();
    match(END);
}

void statement_list(void)
{
    /* 2. <statement list> -> <statement> {<statement>} */
    statement();
    while (true) {
        switch (next_token()) {
            case ID:
            case READ:
            case WRITE:
                statement();
                break;
            default:
                return;
        }
    }
}

void statement(void)
{
    token tok = next_token();
    expr_rec *source, *target;

    switch (tok) {
        case ID:
            /* 3. <statement> -> <ident> := <expression> #assign; */
            target = malloc(sizeof (expr_rec));
            source = malloc(sizeof (expr_rec));

            ident(target);
            match(ASSIGNOP);
            conditional_flag = 0;
            expression(source);
            match(SEMICOLON);
            assign(target, source);
            break;
        case READ:
            /* 4. <statement> -> read (<id list>); */
            match(READ);
            match(LPAREN);
            id_list();
            match(RPAREN);
            match(SEMICOLON);
            break;
        case WRITE:
            /* 5. <statement> -> write (<expr list>); */
            match(WRITE);
            match(LPAREN);
            expr_list();
            match(RPAREN);
            match(SEMICOLON);
            break;
        default:
            syntax_error(tok);
            break;
    }
}

void id_list(void)
{
    /* 6. <id list> -> <ident> #read_id {, <ident> #read_id} */
    expr_rec * expr;
    expr = malloc(sizeof(expr_rec));

    ident(expr); //parser function
    read_id(*expr); //action routine

    while (next_token() == COMMA) {
        match(COMMA);
        ident(expr); //parser function
        read_id(*expr); //action routine
    }
}

void expression(expr_rec *result)
{
    /* 8. <expression> -> <primary> {<add op> <primary> #gen_infix} */
    /* 8. <expression> -> (<expression>|<expression>|<expression>) #gen_conditional */
    expr_rec * left_operand, * right_operand;
    op_rec * op;

    left_operand = malloc(sizeof(expr_rec));
    right_operand = malloc(sizeof(expr_rec));
    op = malloc(sizeof(op_rec));

    primary(left_operand);
    while (next_token() == PLUSOP || next_token() == MINUSOP) {
        add_op(op);
        primary(right_operand);
        *left_operand = gen_infix(*left_operand, *op, *right_operand);
    }

    if (!conditional_flag) conditional(left_operand);

    *result = *left_operand;
}

void conditional(expr_rec *result)
{
    expr_rec *e2, *e3;
    if (next_token()==PIPE){
        e2 = malloc(sizeof(expr_rec));
        e3 = malloc(sizeof(expr_rec));
        match(PIPE);
        conditional_flag = 1;
        expression(e2);
        match(PIPE);
        expression(e3);

        *result = gen_conditional(*result, *e2, *e3);
    }
}

void expr_list(void)
{
    /* 7. <expr list> -> <expression> {, <expression>} */
    expr_rec *result = malloc(sizeof (expr_rec));
    expression(result);
    write_expr(*result);

    while (next_token() == COMMA) {
        match(COMMA);
        expression(result);
        write_expr(*result);
    }
}

void add_op(op_rec * op)
{
    token tok = next_token();

    if (tok == PLUSOP || tok == MINUSOP){
        /* 12. <add op> -> PLUSOP #process_op */
        /* 13. <add op> -> MINUSOP #process_op */
        match(tok);
        *op = process_op();
    } else {
        syntax_error(tok);
    }
}

void primary(expr_rec * expr)
{
    token tok = next_token();

    switch (tok) {
        case LPAREN:
            /* 9. <primary> -> (<expression>) */
            match(LPAREN);
            conditional_flag = 0;
            expression(expr);
            match(RPAREN);
            break;
        case ID:
            /* 10. <primary> -> <ident> */
            ident(expr);
            break;
        case INTLITERAL:
            /* 11. <primary> -> INTLITERAL #process_literal */
            match(INTLITERAL);
            *expr = process_literal();
            break;
        default:
            syntax_error(tok);
            break;
    }
}

void ident(expr_rec * id)
{
    match(ID);
    *id = process_id();
}