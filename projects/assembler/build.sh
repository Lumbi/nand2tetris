#!/bin/bash

cc -g -DDEBUG=1 -O0 \
  main.c \
  parser.c \
  symbol_table.c \
  translater.c \
  test.c \
  -o Assembler
