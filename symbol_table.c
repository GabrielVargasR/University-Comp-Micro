#include "headers/symbol_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 255

string table[TABLE_SIZE];
int counter = 0;

bool lookup(string var_name)
{
    for (int i = 0; i < counter; i++)
    {
        if (!strcmp(table[i],var_name)) return true;
    }
    return false;
};

void enter(string var_name)
{
    if (counter < TABLE_SIZE) {
        strcpy(table[counter], var_name);
        counter++;
    } else {
        printf("Symbol table out of space\n");
        exit(1);
    }
};