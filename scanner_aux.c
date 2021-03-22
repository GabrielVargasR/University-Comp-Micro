#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/tokens.h"
#include "headers/scanner_aux.h"

char token_buffer[MAX_ID_LEN];

void clear_buffer()
{
	printf("clear buffer\n");
};

void buffer_char(char c)
{
	printf("buffer char %c\n", c);
};

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

int main(){return 0;}

