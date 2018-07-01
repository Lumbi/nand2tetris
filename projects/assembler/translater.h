#ifndef __TRANSLATER_H__
#define __TRANSLATER_H__

#include "parser.h"
#include "symbol_table.h"

char* translate(const struct instruction* const inst, struct symbol_table* const symbols);

#endif
