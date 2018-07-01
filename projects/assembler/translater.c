#include "translater.h"

#include <stdlib.h>
#include <stdio.h>

char* translate_binary(const int number) {
  int i = number;
  char* bits = malloc(17 * sizeof(char));
  strcpy(bits, "0000000000000000");
  bits[16] = '\0';
  int bits_index = 15;
  while (i > 0) {
    bits[bits_index--] = (i & 1) + '0';
    i = (i >> 1);
  }
  return bits;
}

char* translateCMD(const char* const cmp)
{
  if (strcmp(cmp, "0") == 0)   return "0101010";
  if (strcmp(cmp, "1") == 0)   return "0111111";
  if (strcmp(cmp, "-1") == 0)  return "0111010";
  if (strcmp(cmp, "D") == 0)   return "0001100";
  if (strcmp(cmp, "A") == 0)   return "0110000";
  if (strcmp(cmp, "M") == 0)   return "1110000";
  if (strcmp(cmp, "!D") == 0)  return "0001101";
  if (strcmp(cmp, "!A") == 0)  return "0110001";
  if (strcmp(cmp, "!M") == 0)  return "1110001";
  if (strcmp(cmp, "-D") == 0)  return "0001111";
  if (strcmp(cmp, "-A") == 0)  return "0110011";
  if (strcmp(cmp, "-M") == 0)  return "1110011";
  if (strcmp(cmp, "D+1") == 0) return "0011111";
  if (strcmp(cmp, "A+1") == 0) return "0110111";
  if (strcmp(cmp, "M+1") == 0) return "1110111";
  if (strcmp(cmp, "D-1") == 0) return "0001110";
  if (strcmp(cmp, "A-1") == 0) return "0110010";
  if (strcmp(cmp, "M-1") == 0) return "1110010";
  if (strcmp(cmp, "D+A") == 0) return "0000010";
  if (strcmp(cmp, "D+M") == 0) return "1000010";
  if (strcmp(cmp, "D-A") == 0) return "0010011";
  if (strcmp(cmp, "D-M") == 0) return "1010011";
  if (strcmp(cmp, "A-D") == 0) return "0000111";
  if (strcmp(cmp, "M-D") == 0) return "1000111";
  if (strcmp(cmp, "D&A") == 0) return "0000000";
  if (strcmp(cmp, "D&M") == 0) return "1000000";
  if (strcmp(cmp, "D|A") == 0) return "0010101";
  if (strcmp(cmp, "D|M") == 0) return "1010101";
  return NULL;
}

char* translateDST(const char* const dst)
{
  if (dst == NULL || strlen(dst) == 0) return "000";
  if (strcmp(dst, "M") == 0)   return "001";
  if (strcmp(dst, "D") == 0)   return "010";
  if (strcmp(dst, "MD") == 0)  return "011";
  if (strcmp(dst, "A") == 0)   return "100";
  if (strcmp(dst, "AM") == 0)  return "101";
  if (strcmp(dst, "AD") == 0)  return "110";
  if (strcmp(dst, "AMD") == 0) return "111";
  return NULL;
}

char* translateJMP(const char* const jmp)
{
  if (jmp == NULL || strlen(jmp) == 0) return "000";
  if (strcmp(jmp, "JGT") == 0)  return "001";
  if (strcmp(jmp, "JEQ") == 0)  return "010";
  if (strcmp(jmp, "JGE") == 0)  return "011";
  if (strcmp(jmp, "JLT") == 0)  return "100";
  if (strcmp(jmp, "JNE") == 0)  return "101";
  if (strcmp(jmp, "JLE") == 0)  return "110";
  if (strcmp(jmp, "JMP") == 0)  return "111";
  return NULL;
}

char* translateC(const char* const cmd, const char* const dst, const char* const jmp)
{
  char* result = malloc(16 * sizeof (char));
  result[0] = '\0';

  const char* const translated_cmd = translateCMD(cmd);
  const char* const translated_dst = translateDST(dst);
  const char* const translated_jmp = translateJMP(jmp);

  if (translated_cmd == NULL)
  {
    #ifdef DEBUG
    printf("Invalid command: %s\n", cmd);
    #endif
    return NULL;
  }

  if (translated_dst == NULL)
  {
    #ifdef DEBUG
    printf("Invalid destination: %s\n", dst);
    #endif
    return NULL;
  }

  if (translated_jmp == NULL)
  {
    #ifdef DEBUG
    printf("Invalid jump: %s\n", jmp);
    #endif
    return NULL;
  }

  strcpy(result, "111");
  strcat(result, translated_cmd);
  strcat(result, translated_dst);
  strcat(result, translated_jmp);

  return result;
}

char* translate(const struct instruction* const inst, struct symbol_table* const symbols)
{
  int address = -1;
  switch (inst->type) {
    case A:
      address = get_address(inst->symbol, symbols);
      int binary = 0;
      if (address >= 0 && address < 32768) { // Symbol exists
        binary = address;
      } else if (inst->symbol[0] == '0') { // Symbol is '0'
        binary = 0;
      } else {
        const int decimal_symbol = atoi(inst->symbol);
        if (decimal_symbol) { // Symbol is decimal
          binary = decimal_symbol;
        } else { // Symbol is a variable
          binary = set_variable(inst->symbol, symbols);
        }
      }
      return translate_binary(binary);

    case C:
      return translateC(inst->cmd, inst->dst, inst->jmp);

    default:
      return NULL;
  }
}
