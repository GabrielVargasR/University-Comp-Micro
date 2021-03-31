#include <stdbool.h>
#include "headers/scanner.h"
#include "headers/parser.h"
#include "headers/parser_aux.h"
#include "headers/records.h"
#include "headers/action_routines.h"

#include <stdio.h>
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

// TODO: update to include action symbols
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

// TODO: update to include action symbols
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
    expr_rec * left_operand, * right_operand;
    op_rec * op;

    left_operand = malloc(sizeof(expr_rec));
    right_operand = malloc(sizeof(expr_rec));
    op = malloc(sizeof(op_rec));

    primary(left_operand); //TODO: edit primary
    while (next_token() == PLUSOP || next_token() == MINUSOP) {
        add_op(op); // TODO: edit add_op
        primary(right_operand);
        *left_operand = gen_infix(*left_operand, *op, *right_operand); //TODO: change pointer/value
    }
    *result = *left_operand;
}

// TODO: update to include action symbols
void expr_list(void)
{
    /* 7. <expr list> -> <expression> {, <expression>} */
    expr_rec *result = malloc(sizeof (expr_rec));
    expression(result);

    while (next_token() == COMMA) {
        match(COMMA);
        expression(result); //TODO: change value of result? call action routine before that?
    }
}

void add_op(op_rec * op)
{
    token tok = next_token();

    if (tok == PLUSOP || tok == MINUSOP){
        /* 12. <add op> -> PLUSOP #process_op */
        match(tok);
        *op = process_op();
    } else {
        /* 13. <add op> -> MINUSOP #process_op */
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
            expression(expr);
            match(RPAREN);
            break;
        case ID:
            /* 10. <primary> -> <ident> */
            match(ID);
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