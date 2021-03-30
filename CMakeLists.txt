cmake_minimum_required(VERSION 3.15.3)

project(comp)

add_executable(${PROJECT_NAME} compiler.c parser.c parser_aux.c action_routines.c records.c generator.c symbol_table.c ids.c scanner.c scanner_aux.c)