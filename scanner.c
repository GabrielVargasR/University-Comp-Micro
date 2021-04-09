#include <stdio.h>
#include <ctype.h>
#include "headers/scanner_aux.h"
#include "headers/tokens.h"

FILE *file;

token scanner(void)
{
	int in_char, c;

	if (feof(file)) {
	    fclose(file);
		return SCANEOF;
	}

	while ((in_char = fgetc(file)) != EOF) {
		if (isspace(in_char)) {
			continue; /* do nothing */
		}
		else if (isalpha(in_char)) {
			/*
			 * ID ::= LETTER | ID LETTER
			 *				 | ID DIGIT
			 *				 | ID UNDERSCORE
			 */
			clear_buffer();
			buffer_char(in_char);
			for (c = fgetc(file); isalnum(c) || c == '_'; c = fgetc(file)) {
				buffer_char(c);
			}
			ungetc(c, file); // para no perder el que se acaba de leer que no es alnum
			return check_reserved();
		} else if (isdigit(in_char)) {
			/*
			 * INTLITERAL ::= DIGIT |
			 *				  INTLITERAL DIGIT
			 */
			clear_buffer();
			buffer_char(in_char);
			for (c = fgetc(file); isdigit(c); c = fgetc(file)){
				buffer_char(c);
			}
			ungetc(c, file);
			return INTLITERAL;
		} else if (in_char == '(') {
			return LPAREN;
		} else if (in_char == ')') {
			return RPAREN;
		} else if (in_char == '|') {
		    return PIPE;
		} else if (in_char == ';') {
			return SEMICOLON;
		} else if (in_char == ',') {
			return COMMA;
		} else if (in_char == '+') {
			return PLUSOP;
		} else if (in_char == ':') {
			/*Looking for ':=' */
			c = fgetc(file);
			if (c == '=') {
				return ASSIGNOP;
			} else {
				ungetc(c, file);
				lexical_error(in_char);
			}
		} else if (in_char == '-') {
			/* Check for comment or MINUSOP*/
			c = fgetc(file);
			if (c == '-') {
				do {
					in_char = fgetc(file);
				} while (in_char != '\n');
			} else {
				ungetc(c, file); // returns el char que acaba de leer (que no era '-' a stdin)
				return MINUSOP;
			}
		} else {
			lexical_error(in_char);
		}
	}
	// Warning can be removed with a return here
}

void set_file(char *path)
{
    file = fopen(path, "r");
}