#include "headers/symbol_table.h"
#include "headers/generator.h"
#include <stdio.h>

void check_id(string s)
{
    if (! lookup(s)){
        enter(s);
        generate((string *) "Declare", (string *) s, (string *) "Integer", (string *) "");
    }
}

char *get_temp(void)
{
    static int max_temp = 0;
    static char tempname[MAX_ID_LEN];

    max_temp++;
    sprintf(tempname, "Temp&%d", max_temp);
    check_id(tempname);
    return tempname;
}