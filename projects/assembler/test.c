#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "parser.h"
#include "test.h"

void assert_strings_are_equal(const char* a, const char* b)
{
  assert(a == NULL && b == NULL || a != NULL && b != NULL && strcmp(a, b) == 0);
}

void testA(const char* line, const char* symbol)
{
  struct instruction* result = parse(line, 0);
  assert(strcmp(result->symbol, symbol) == 0);
  delete_instruction(result);
}

void testC(const char* line, const char* dst, const char* cmd, const char* jmp)
{
  struct instruction* result = parse(line, 0);
  assert_strings_are_equal(result->dst, dst);
  assert_strings_are_equal(result->cmd, cmd);
  assert_strings_are_equal(result->jmp, jmp);
  delete_instruction(result);
}

void testL(const char* line, const char* label)
{
  struct instruction* result = parse(line, 0);
  assert_strings_are_equal(result->label, label);
  delete_instruction(result);
}

void runTests()
{
  testA("@He  \t l l o // here is a comment", "Hello");
  testC("ADM=D+1;JMP", "ADM", "D+1", "JMP");
  testC("ADM=D+1", "ADM", "D+1", NULL);
  testC("D+1;JMP", NULL, "D+1", "JMP");
  testC("D+1", NULL, "D+1", NULL);
  testC(";JMP", NULL, NULL, "JMP");
  testC("0;JMP", NULL, "0", "JMP");
  testL("(LABEL)", "LABEL");
}
