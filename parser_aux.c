#include <stdio.h>
#include <stdlib.h>
#include "headers/tokens.h"

void match(token t)
{
    // TODO implementar
};

token next_token()
{
    return ID; //TODO implementar bien
};

void syntax_error(token t)
{
    //TODO: implementar bien. Este código es temporal
    printf("Syntax error\n");
    exit(1); //TODO: revisar exit codes
};