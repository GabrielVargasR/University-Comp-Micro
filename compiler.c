#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "headers/scanner.h"
#include "headers/parser.h"
#define SOURCE_CODE_EXTENSION "micro"

bool valid_file_exists(char path[]);
/*
#include "headers/records.h"
int main()
{
    string table[100];

    strcpy(table[0], "hola");
    strcpy(table[1], "adios");

    for(int i = 0; i < 100; i++)
    {
        if (!strcmp(table[i], "adios")) {
            printf("sí");
            break;
        }
    }
}
*/
///*
int main(int argc, char *argv[])
{
    if (argc == 2) {
        if (valid_file_exists(argv[1])){
            set_file(argv[1]); // sets file for the scanner
            system_goal();
        } else {
            printf("The specified file was not found or was not a .micro file");
            exit(1);
        }
    } else {
        printf("\nExpected (1) argument, got (%d)\n", argc-1);
        printf("Usage: comp <path/to/micro/file>\n");
    }
    return 0;
}
//*/
bool valid_file_exists(char path[])
{
    char *extension = strrchr(path, '.');
    extension = extension+1;

    // if file exists and has the right extension
    if (access(path, R_OK) == 0 && !(strcmp(extension, SOURCE_CODE_EXTENSION))) {
        return true;
    }
    return false;
}