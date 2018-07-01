#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void print_instruction(const struct instruction* inst)
{
  printf("{\n");
  printf("\taddress: %d\n", inst->address);
  switch (inst->type) {
    case INVALID: printf("\ttype: INVALID\n"); break;
    case EMPTY: printf("\ttype: EMPTY\n"); break;
    case A: printf("\ttype: A\n"); break;
    case C: printf("\ttype: C\n"); break;
    case L: printf("\ttype: L\n"); break;
  }
  printf("\tsymbol: %s\n", inst->symbol);
  printf("\tdst: %s\n", inst->dst);
  printf("\tcmd: %s\n", inst->cmd);
  printf("\tjmp: %s\n", inst->jmp);
  printf("\tlabel: %s\n", inst->label);
  printf("}\n");
}

const char* remove_spaces(const char* str)
{
  char* result = (char*)malloc(strlen(str) * sizeof (char));
  strcpy(result, str);
  int i = 0, j = 0;
  while (result[i])
  {
    if (result[i] != ' ' && result[i] != '\t' && result[i] != '\n' && result[i] != '\r')
        result[j++] = result[i];
    i++;
  }
  result[j] = '\0';
  return result;
}

const char* remove_comment(const char* str)
{
  const char* ptr_to_comment = strstr(str, "//");
  if (ptr_to_comment != NULL)
  {
    size_t len = ptr_to_comment - str;
    char* result = (char*)malloc(len * sizeof (char));
    memcpy(result, str, len);
    return result;
  } else {
    return str;
  }
}

struct instruction* new_instruction()
{
  struct instruction* inst = malloc(sizeof (struct instruction));
  inst->type = INVALID;
  inst->address = -1;
  inst->symbol = NULL;
  inst->dst = NULL;
  inst->cmd = NULL;
  inst->jmp = NULL;
  inst->label = NULL;
  return inst;
}

void delete_instruction(struct instruction* inst)
{
  if (inst != NULL)
  {
    if (inst->symbol != NULL) free(inst->symbol);
    if (inst->dst != NULL) free(inst->dst);
    if (inst->cmd != NULL) free(inst->cmd);
    if (inst->jmp != NULL) free(inst->jmp);
    if (inst->label != NULL) free(inst->label);
    free(inst);
  }
}

char* parse_dst(const char* str)
{
  const char* ptr_to_equal = strchr(str, '=');
  if (ptr_to_equal != NULL)
  {
    size_t len = ptr_to_equal - str;
    char* dst = (char*)malloc(len * sizeof (char));
    memcpy(dst, str, len);
    return dst;
  } else {
    return NULL;
  }
}

char* parse_cmd(const char* str)
{
  const char* ptr_to_equal = strchr(str, '=');
  const char* ptr_to_semicolumn = strchr(str, ';');
  const char* start = ptr_to_equal != NULL ? ptr_to_equal+1 : str;
  const char* end = ptr_to_semicolumn != NULL ? ptr_to_semicolumn : str + strlen(str);
  if (end > start)
  {
    const size_t len = (end - start);
    char* cmd = (char*)malloc(len * sizeof (char));
    memcpy(cmd, start, len);
    return cmd;
  } else {
    return NULL;
  }
}

char* parse_jmp(const char* str)
{
  const char* ptr_to_semicolumn = strchr(str, ';');
  if (ptr_to_semicolumn != NULL)
  {
    size_t len = str + strlen(str) - ptr_to_semicolumn;
    char* jmp = (char*)malloc(len * sizeof (char));
    memcpy(jmp, ptr_to_semicolumn+1, len);
    return jmp;
  } else {
    return NULL;
  }
}

char* parse_label(const char* str)
{
  const char* ptr_to_left_paren = strchr(str, '(');
  const char* ptr_to_right_paren = strchr(str, ')');
  if (ptr_to_left_paren != NULL && ptr_to_right_paren != NULL &&
      ptr_to_right_paren > ptr_to_left_paren)
  {
    size_t len = ptr_to_right_paren - ptr_to_left_paren - 1;
    char* label = (char*)malloc(len * sizeof (char));
    memcpy(label, ptr_to_left_paren+1, len);
    return label;
  } else {
    return NULL;
  }
}

struct instruction* parse(const char* str, const int address)
{
  #ifdef DEBUG
  printf("Parsing: %s", str);
  #endif
  const char* line = remove_comment(remove_spaces(str));
  struct instruction* inst = new_instruction();
  inst->address = address;

  if (line[0] == '@')
  {
    inst->type = A;
    size_t symbol_len = strlen(line)-1;
    inst->symbol = (char*)malloc(symbol_len * sizeof (char));
    memcpy(inst->symbol, &line[1], symbol_len);
  } else if (line[0] == '(')
  {
    inst->type = L;
    inst->label = parse_label(line);
  } else if (strlen(line) > 0)
  {
    inst->type = C;
    inst->dst = parse_dst(line);
    inst->cmd = parse_cmd(line);
    inst->jmp = parse_jmp(line);
  } else
  {
    inst->type = EMPTY;
  }

  return inst;
}
