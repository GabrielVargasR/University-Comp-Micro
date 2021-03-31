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
    expr_rec * exp = malloc(sizeof (expr_rec));
    exp->kind = IDEXPR;
    strcpy(exp->name, "abc");

    expr_rec * exp2 = malloc(sizeof (expr_rec));
    exp2->kind = LITERALEXPR;
    exp2->val = 532;

    printf("%s %d \n", extract_expr(exp), extract_expr(exp2));
}
*/
///*
int main(int argc, char *argv[])
{
    if (argc == 2) {
        // printf("%s\n", argv[1]);
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