#ifndef math_funcs_h
#define math_funcs_h

#include "stack.h"

int push(long double num, struct stackStruct * stack);

long double pop(struct stackStruct * stack);

long double peek(stackStruct * stack);

void swap(stackStruct * stack);

void over(stackStruct * stack);

void add(stackStruct * stack);

void subtract(stackStruct * stack);

void multiply(stackStruct * stack);

void divide(stackStruct * stack);

void exponent(stackStruct * stack);

void root(stackStruct * stack);

void logarithm(stackStruct * stack);

void absolute(stackStruct * stack);

void print_stack(stackStruct * stack);

#endif
