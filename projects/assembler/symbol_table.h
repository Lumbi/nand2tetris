#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

struct symbol_assoc
{
  char* symbol;
  int address;
};

struct symbol_table
{
  int _free_variable_address;
  struct symbol_assoc** _array;
};

#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

#define SYMBOL_TABLE_SIZE 4096

struct symbol_table* new_symbol_table();

void delete_symbol_table(struct symbol_table* table);

int get_address(const char* const symbol, const struct symbol_table* const table);

void set_symbol(const char* const symbol, const int address, struct symbol_table* const table);

int set_variable(const char* const variable, struct symbol_table* const table);

void print_symbol_table(const struct symbol_table* const table);

struct symbol_table* init_symbol_table();

#endif
