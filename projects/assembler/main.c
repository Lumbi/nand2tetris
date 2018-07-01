#include <stdio.h>
#include <string.h>
#include "test.h"

#include "parser.h"
#include "translater.h"
#include "symbol_table.h"

int main(int argc, char *argv[])
{
  #ifdef DEBUG
  printf("Debug on\n");
  #endif

  if (argc != 3) {
    printf("Usage: Assember <path to assembly file> <output file>\n");
    exit(EXIT_FAILURE);
  }

  const char* input_file_path = argv[1];
  const char* output_file_path = argv[2];

  #ifdef TEST
  runTests();
  #endif

  FILE *file = fopen(input_file_path, "r");

  const size_t LINE_BUFFER_WIDTH = 255;
  char line_buffer[LINE_BUFFER_WIDTH];

  // Count number of lines
  int file_length = 0;
  while(fgets(line_buffer, LINE_BUFFER_WIDTH, file) != NULL) 
  {
    file_length++;
  }
  rewind(file);

  // Init symbol table
  struct symbol_table* symbols = init_symbol_table();

  // Parse instructions
  int line_number = 0;
  int instruction_address = 0;
  struct instruction** instructions = malloc(file_length * sizeof (struct instruction*));

  while(fgets(line_buffer, LINE_BUFFER_WIDTH, file) != NULL)
  {
    struct instruction* inst = parse(line_buffer, instruction_address);
    instructions[line_number] = inst;

    if (inst->type == L) {
      set_symbol(inst->label, inst->address, symbols);
    }

    line_number++;
    if (inst->type != EMPTY && inst->type != L)
      instruction_address++;
  }

  // Translate

  FILE *out = fopen(output_file_path, "w");

  const char* translation = NULL;
  for (int i = 0; i < file_length; i++) {
    if (instructions[i] != NULL) {
       translation = translate(instructions[i], symbols);
      if (translation != NULL) {
        fprintf(out, "%s\n", translation);
        free((void*)translation);
      }
    }
  }

  // Clean up

  fclose(file);
  fclose(out);

  for (int i = 0; i < file_length; i++) {
    if (instructions[i] != NULL)
      free(instructions[i]);
  }

  exit(EXIT_SUCCESS);
}