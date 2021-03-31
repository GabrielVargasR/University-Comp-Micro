#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/tokens.h"
#include "headers/scanner_aux.h"

char token_buffer[MAX_ID_LEN] = {};
int token_buffer_index = 0; // current index for token_buffer

void clear_buffer()
{
    for (int i = 0; i < MAX_ID_LEN; i++){
        token_buffer[i] = '\0';
    };

    token_buffer_index = 0;
}

void buffer_char(char c)
{
    token_buffer[token_buffer_index] = c;
    token_buffer_index++;
    if (token_buffer_index > MAX_ID_LEN) lexical_error(c);
}

token check_reserved()
{
	char word[MAX_ID_LEN];
	sscanf(token_buffer, "%s", word);

	// TODO: implement toLower()
	if (strcmp(word, "read") == 0) {
		return READ;
	} else if (strcmp(word, "write") == 0) {
		return WRITE;
	} else if (strcmp(word, "begin") == 0) {
		return BEGIN;
	} else if (strcmp(word, "end") == 0) {
		return END;
	} else {
		return ID;
	}
};

void lexical_error(char c)
{
	printf("lexical error: %c\n", c);
	exit(1); //TODO: revisar exit codes
};

