#include <stdio.h>
#include "headers/records.h"
#include "headers/generator.h"

// TODO: change parameter names
// TODO: define generate function well
extern FILE * fPtr;
extern FILE * fPtrTemp;

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

void generateData(string * one, string * two, string * three, string * four)
{
    /* Write data to file */
    fputs(*one , fPtrTemp);
    fputs(" " , fPtrTemp);
    fputs(*two , fPtrTemp);
    fputs(" " , fPtrTemp);
    fputs(*three , fPtrTemp);
    fputs(" " , fPtrTemp);
    fputs(*four , fPtrTemp);
    fputs("\n" , fPtrTemp);
};
