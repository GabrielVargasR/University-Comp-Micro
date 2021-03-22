#include <stdio.h>
#include <stdbool.h>
#include "headers/scanner.h"
#include "headers/parser.h"
#include "headers/parser_aux.h"

int main()
{
    printf("hello world\n");
    return 0;
}

void system_goal(void)
{
    /* 14. <system goal> -> <program> SCANEOF */
    program();
    match(SCANEOF); // TODO Impl
}

void program(void)
{
    /* 1. <program> -> BEGIN <statement list> END */
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

    switch (tok) {
        case ID:
            /* 3. <statement> -> ID := <expression>; */
            match(ID);
            match(ASSIGNOP);
            expression();
            match(SEMICOLON);
            break;
        case READ:
            /* 4. <statement> -> READ (<id list>); */
            match(READ);
            match(LPAREN);
            id_list();
            match(RPAREN);
            match(SEMICOLON);
            break;
        case WRITE:
            /* 5. <statement> -> WRITE (<expr list>); */
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
    /* 6. <id list> -> ID {, ID} */
    match(ID);

    while (next_token() == COMMA) {
        match(COMMA);
        match(ID);
    }
}

void expression(void)
{
    token t;
    /* 8. <expression> -> <primary> {<add op> <primary>} */
    primary();
    for (t = next_token(); t == PLUSOP || t == MINUSOP; t = next_token()) {
        add_op();
        primary();
    }
}

void expr_list(void)
{
    /* 7. <expr list> -> <expression> {, <expression>} */
    while (next_token() == COMMA) {
        match(COMMA);
        expression();
    }
}

void add_op(void)
{
    token tok = next_token();

    /*  */
    if (tok == PLUSOP || tok == MINUSOP){
        match(tok);
    } else {
        syntax_error(tok);
    }
}

void primary(void)
{
    token tok = next_token();

    switch (tok) {
        case LPAREN:
            /* 9. <primary> -> (<expression>) */
            match(LPAREN);
            expression();
            match(RPAREN);
            break;
        case ID:
            /* 10. <primary> -> ID */
            match(ID);
            break;
        case INTLITERAL:
            /* 11. <primary> -> INTLITERAL */
            match(INTLITERAL);
            break;
        default:
            syntax_error(tok);
            break;
    }
}