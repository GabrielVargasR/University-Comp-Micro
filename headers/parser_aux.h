#ifndef PARSER_AUX_H
#define PARSER_AUX_H
#include "tokens.h"
void match(token t);
token next_token();
void syntax_error(token t);
void init();
#endif