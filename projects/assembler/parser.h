#ifndef __PARSER_H__
#define __PARSER_H__

enum instruction_type { INVALID, EMPTY, A, C, L };

struct instruction
{
  enum instruction_type type;
  int address;
  char* symbol;
  char* dst;
  char* cmd;
  char* jmp;
  char* label;
};

struct instruction* new_instruction();

void delete_instruction(struct instruction*);

void print_instruction(const struct instruction*);

struct instruction* parse(const char*, const int address);

#endif
