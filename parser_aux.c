#include <stdio.h>
#include <stdlib.h>
#include "headers/tokens.h"
#include "headers/scanner.h"
#include "headers/parser_aux.h"

typedef struct queue_node {
    token tok;
    struct queue_node *prev;
} queue_node;

typedef struct queue {
    int size;
    queue_node *head;
    queue_node *tail;
} queue;

void push(token tok);
token get_next_token();
queue *current_tokens;

void print_token(token t); // TODO: borrar

token next_token()
{
    // if the queue is empty, a token needs to be added to the queue by calling the scanner
    if (current_tokens->size == 0) {
        push(scanner());
    }
    current_token = current_tokens->head->tok;
    return current_token; //returns the head of the queue without removing it from the queue (no pop)
};

void syntax_error(token t)
{
    //TODO: implementar bien. Este código es temporal
    printf("Syntax error\n");
    exit(1); //TODO: revisar exit codes
};

void match(token t)
{
    // if the queue is empty, a token needs to be added to the queue by calling the scanner
    if (current_tokens->size == 0) {
        push(scanner());
    }

    // gets the element at the head of the queue and removes it from the queue
    current_token = get_next_token();

    // if t is not of the same type as the current type, the code has a syntax error
    if (t != current_token){
        // TODO: delete prints
        print_token(t);
        printf(" vs. ");
        print_token(current_token);
        syntax_error(t);
    }
};

// TODO: move queue code elsewhere?
void push(token tok)
{
    queue_node *node;
    node = (queue_node *) malloc(sizeof(queue_node));
    node->tok = tok;

    if (current_tokens->size == 0) {
        current_tokens->head = current_tokens->tail = node;
    } else {
        current_tokens->tail->prev = node;
        current_tokens->tail = node;
    }
    current_tokens->size++;
};

void pop()
{
    if (current_tokens->size > 0) {
        current_tokens->head = current_tokens->head->prev;
    }
    current_tokens->size--;
};

token get_next_token()
{
    if (current_tokens->size > 0) {
        token tok = current_tokens->head->tok;
        pop();
        return tok;
    }
    return -1;
};

void init()
{
    current_tokens = (queue *) malloc(sizeof (queue));
    current_tokens->size = 0;
};

// TODO: evaluate if this should be kept for use of syntax_error
void print_token(token t)
{
    switch(t) {
        case BEGIN:
            printf("BEGIN ");
            break;
        case END:
            printf("END ");
            break;
        case READ:
            printf("READ ");
            break;
        case WRITE:
            printf("WRITE ");
            break;
        case ID:
            printf("ID ");
            break;
        case INTLITERAL:
            printf("INTLITERAL ");
            break;
        case LPAREN:
            printf("LPAREN ");
            break;
        case RPAREN:
            printf("RPAREN ");
            break;
        case SEMICOLON:
            printf("SEMICOLON ");
            break;
        case COMMA:
            printf("COMMA ");
            break;
        case ASSIGNOP:
            printf("ASSIGNOP ");
            break;
        case PLUSOP:
            printf("PLUSOP ");
            break;
        case MINUSOP:
            printf("MINUSOP ");
            break;
        case SCANEOF:
            printf("SCANEOF ");
            break;
        default:
            printf("UNKNOWN");
            break;
    }
};