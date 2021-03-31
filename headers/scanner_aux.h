#ifndef SCANNER_AUX_H
#define SCANNER_AUX_H

#include "tokens.h"
#define MAX_ID_LEN 33
extern char token_buffer[];
void clear_buffer();
void buffer_char(char c);
token check_reserved();
void lexical_error(char c);
void print_buffer(); //TODO: delete

#endif