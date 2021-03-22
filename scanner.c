#include <stdio.h>
#include <ctype.h>
#include "headers/scanner_aux.h"
#include "headers/tokens.h"

token scanner(void)
{
	int in_char, c;

	clear_buffer();
	if (feof(stdin)) {
		return SCANEOF;
	}

	while ((in_char = getchar()) != EOF) {
		if (isspace(in_char)) {
			continue; /* do nothing */
		}
		else if (isalpha(in_char)) {
			/*
			 * ID ::= LETTER | ID LETTER
			 *				 | ID DIGIT
			 *				 | ID UNDERSCORE
			 */
			buffer_char(in_char);
			for (c = getchar(); isalnum(c) || c == '_'; c = getchar()) {
				buffer_char(c);
			}
			ungetc(c, stdin); // para no perder el que se acaba de leer que no es alnum
			return check_reserved();
		} else if (isdigit(in_char)) {
			/*
			 * INTLITERAL ::= DIGIT |
			 *				  INTLITERAL DIGIT
			 */
			buffer_char(c);
			for (c = getchar(); isdigit(c); c = getchar()){
				buffer_char(c);
			}
			ungetc(c, stdin);
			return INTLITERAL;
		} else if (in_char == '(') {
			return LPAREN;
		} else if (in_char == ')') {
			return RPAREN;
		} else if (in_char == ';') {
			return SEMICOLON;
		} else if (in_char == ',') {
			return COMMA;
		} else if (in_char == '+') {
			return PLUSOP;
		} else if (in_char == ':') {
			/*Looking for ':=' */
			c = getchar();
			if (c == '=') {
				return ASSIGNOP;
			} else {
				ungetc(c, stdin);
				lexical_error(in_char);
			}
		} else if (in_char == '-') {
			/* Check for comment or Minusop*/
			c = getchar();
			if (c == '-') {
				do {
					in_char = getchar();
				} while (in_char != '\n');
			} else {
				ungetc(c, stdin); // regresa el char que acaba de leer (que no era '-' a stdin)
				return MINUSOP;
			}
		} else {
			lexical_error(in_char);
		}
	}
}