#include "headers/symbol_table.h"
#include "headers/generator.h"
#include <stdio.h>

void check_id(string s)
{
    if (! lookup(s)){
        enter(s);
        generateData((string *) ".balign 4", (string *) "", (string *) "", (string *) "");
        generateData((string *) s, (string *) ": ", (string *) ".word ", (string *) "0");
    }
}

char *get_temp(void)
{
    static int max_temp = 0;
    static char tempname[MAX_ID_LEN];

    max_temp++;
    sprintf(tempname, "Temp%d", max_temp);
    check_id(tempname);
    return tempname;
}
