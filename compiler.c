#include <stdio.h>
#include "headers/parser.h"

int main(int argc, char *argv[])
{
    if (argc == 2) {
        printf("%s\n", argv[1]);
    } else {
        printf("\nExpected (1) argument, got (%d)\n", argc-1);
        printf("Usage: comp <path/to/micro/file>\n");
    }
    return 0;
}