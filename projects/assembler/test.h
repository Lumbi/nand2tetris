#ifndef __TEST_H__
#define __TEST_H__

void assert_strings_are_equal(const char* a, const char* b);

void testA(const char* line, const char* symbol);

void testC(const char* line, const char* dst, const char* cmd, const char* jmp);

void testL(const char* line, const char* label);

void runTests();

#endif

