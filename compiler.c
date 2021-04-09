#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "headers/scanner.h"
#include "headers/parser.h"
#define SOURCE_CODE_EXTENSION "micro"
#define TEMP_FILE "./tmp.txt"

bool valid_file_exists(char path[]);
void init_files();
void close_files();
FILE * fPtr;
FILE * fPtrTemp;
char *name;

int main(int argc, char *argv[])
{
    if (argc == 3) {
        if (valid_file_exists(argv[1])){
	        init_files(argv[2]);
            set_file(argv[1]); // sets file for the scanner
            system_goal();
            close_files();
        } else {
            printf("The specified file was not found or was not a .micro file");
            exit(1);
        }
    } else {
        printf("\nExpected (1) argument, got (%d)\n", argc-1);
        printf("Usage: comp <path/to/micro/file> <ASM file name>\n");
    }

    return 0;
}

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

void init_files(char *file_name)
{
    name = malloc(sizeof(char)*100);
    strcat(name, "./");
    strcat(name, file_name);
    fPtr = fopen(name, "w");
    fPtrTemp = fopen(TEMP_FILE, "w");

    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL || fPtrTemp == NULL) {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    fputs(".data" , fPtrTemp);
    fputs("\n" , fPtrTemp);
    fputs(".balign 4\n", fPtrTemp);
    fputs("message : .asciz \"%d\\n\"\n", fPtrTemp);
    fputs(".balign 4\n", fPtrTemp);
    fputs("read_pattern : .asciz \"%d\"\n", fPtrTemp);
}

void close_files()
{
    fclose(fPtrTemp);
    fclose(fPtr);
    fPtr = fopen(name, "a+");
    fPtrTemp = fopen(TEMP_FILE, "a+");

    char c;
    c = fgetc(fPtrTemp);
    while (c != EOF)
    {
        fputc(c,fPtr);
        c = fgetc(fPtrTemp);
    }
    fclose(fPtrTemp);
    fclose(fPtr);
    remove(TEMP_FILE);
}