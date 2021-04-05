#include <stdio.h>
#include "headers/records.h"
#include "headers/generator.h"

// TODO: change parameter names
// TODO: define generate function well
extern FILE * fPtr;

void generate(string * one, string * two, string * three, string * four)
{
    /* Write data to file */
    fputs(*one , fPtr);
    fputs(" " , fPtr);
    fputs(*two , fPtr);
    fputs(" " , fPtr);
    fputs(*three , fPtr);
    fputs(" " , fPtr);
    fputs(*four , fPtr);
    fputs("\n" , fPtr);
};
