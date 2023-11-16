#ifndef __PRINT_H
#define __PRINT_H
#include "uart.h"

void print(char* str);
void println(char* str);
void printlnHex(char* str, unsigned int hex);

#endif
