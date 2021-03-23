#ifndef TOKENS_H
#define TOKENS_H
typedef enum token_types {
	BEGIN, END, READ, WRITE, ID, INTLITERAL, LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP, PLUSOP, MINUSOP, SCANEOF
} token;
#endif