#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"

#define SYMBOL_TABLE_SIZE 4096

struct symbol_assoc* new_symbol_assoc(const char* const symbol, const int address)
{
  struct symbol_assoc* assoc = malloc(sizeof (struct symbol_assoc));
  assoc->symbol = malloc(strlen(symbol) * sizeof (char));
  strcpy(assoc->symbol, symbol);
  assoc->address = address;
  return assoc;
}

void delete_symbol_assoc(struct symbol_assoc* assoc)
{
  if (assoc != NULL)
  {
    if (assoc->symbol != NULL) {
      free(assoc->symbol);
    }
    free(assoc);
  }
}

struct symbol_table* new_symbol_table()
{
  struct symbol_table* table = malloc(sizeof (struct symbol_table));
  table->_free_variable_address = 16;
  table->_array = malloc(sizeof (struct symbol_assoc) * SYMBOL_TABLE_SIZE);
  return table;
}

void delete_symbol_table(struct symbol_table* table)
{
  if (table != NULL)
  {
    if (table->_array != NULL)
    {
      for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
      {
        if (table->_array[i] != NULL) delete_symbol_assoc(table->_array[i]);
      }
    }
    free(table);
  }
}

int get_address(const char* const symbol, const struct symbol_table* const table)
{
  for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
  {
    const struct symbol_assoc* const candidate = table->_array[i];
    if (candidate != NULL &&
        candidate->symbol != NULL &&
        strcmp(symbol, candidate->symbol) == 0)
    {
      return candidate->address;
    }
  }
  return -1;
}

void set_symbol(const char* const symbol, const int address, struct symbol_table* const table)
{
  int has_symbol = 0;
  int last_symbol = -1;
  for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
  {
    const struct symbol_assoc* const candidate = table->_array[i];
    if (candidate != NULL)
    {
      last_symbol = i;
      if (candidate->symbol != NULL && strcmp(symbol, candidate->symbol) == 0)
      {
        has_symbol = 1;
        break;
      }
    }
  }

  if (has_symbol) {
    table->_array[last_symbol]->address = address;
  } else {
    table->_array[last_symbol+1] = new_symbol_assoc(symbol, address);
  }
}

int set_variable(const char* const variable, struct symbol_table* const table)
{
  int variable_address = table->_free_variable_address;
  set_symbol(variable, table->_free_variable_address, table);
  table->_free_variable_address++;
  return variable_address;
}

void print_symbol_table(const struct symbol_table* const table)
{
  printf("{\n");
  for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
  {
    const struct symbol_assoc* const assoc = table->_array[i];
    if (assoc != NULL) {
      printf("\t%s: %d\n", assoc->symbol, assoc->address);
    } else {
      break;
    } 
  }
  printf("}\n");
}

struct symbol_table* init_symbol_table()
{
  struct symbol_table* const table = new_symbol_table();

  set_symbol("R0", 0, table);
  set_symbol("R1", 1, table);
  set_symbol("R2", 2, table);
  set_symbol("R3", 3, table);
  set_symbol("R4", 4, table);
  set_symbol("R5", 5, table);
  set_symbol("R6", 6, table);
  set_symbol("R8", 7, table);
  set_symbol("R8", 8, table);
  set_symbol("R9", 9, table);
  set_symbol("R10", 10, table);
  set_symbol("R11", 11, table);
  set_symbol("R12", 12, table);
  set_symbol("R13", 13, table);
  set_symbol("R14", 14, table);
  set_symbol("R15", 15, table);

  set_symbol("SP", 0, table);
  set_symbol("LCL", 1, table);
  set_symbol("ARG", 2, table);
  set_symbol("THIS", 3, table);
  set_symbol("THAT", 4, table);

  set_symbol("SCREEN", 16384, table);
  set_symbol("KBD", 24576, table);

  return table;
}
