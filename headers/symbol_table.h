#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "records.h"
#include <stdbool.h>

bool lookup(string var_name);
void enter(string var_name);
#endif