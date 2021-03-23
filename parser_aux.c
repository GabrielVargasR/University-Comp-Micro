#include <stdio.h>
#include <stdlib.h>
#include "headers/tokens.h"
#include "headers/scanner.h"

token current_token;

token next_token()
{
    current_token = scanner();
    return current_token; //TODO implementar bien
};

void syntax_error(token t)
{
    //TODO: implementar bien. Este código es temporal
    printf("Syntax error\n");
    exit(1); //TODO: revisar exit codes
};

void match(token t)
{
    if (t != next_token()){
        syntax_error(t);
    }
};