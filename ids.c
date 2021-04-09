#include "headers/symbol_table.h"
#include "headers/generator.h"
#include "headers/ids.h"
#include <stdio.h>
#include <stdlib.h>

//int max_temp = 0;

bool is_var_name(string s)
{
    // if the second character is an 'L', it is a temp label name, and hence it is not a variable
    if (s[1] == 'L') return false;
    return true;
}


void check_id(string s)
{
    if (! lookup(s) && is_var_name(s)){
        enter(s);
        generateData((string *) ".balign 4", (string *) "", (string *) "", (string *) "");
        generateData((string *) s, (string *) ": ", (string *) ".word ", (string *) "0");
    } else if (!lookup(s)){
        enter(s);
    }
}

char *get_temp(char *type)
{
    static int max_temp = 0;
    char *tempname;
    tempname = malloc(sizeof(char)*MAX_ID_LEN);

    max_temp++;
    sprintf(tempname, type, max_temp);
    check_id(tempname);
    return tempname;
}