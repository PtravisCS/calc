#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int push(long double num, struct stackStruct * stack) {

  if (stack->depth < MAX_STACK_DEPTH) {

    stack->data[stack->depth] = num;
    stack->depth++;
    stack->ptr++;
    return stack->depth;

  } else {

    printf("Stack Overflow\nCould not push %Lf onto stack, stack is full\n", num);
    exit(EXIT_FAILURE);

  }

}

long double pop(struct stackStruct * stack) {

  if (stack->depth > 0) {

    long double num = stack->data[stack->depth - 1];
    stack->data[stack->depth] = 0;
    stack->depth--;
    stack->ptr--;

    return num;

  } else {

    printf("Stack Undeflow\n");
    exit(EXIT_FAILURE);

  }

}

long double peek(stackStruct * stack) {

  return stack->data[stack->depth - 1];

}

void swap(stackStruct * stack) {

  long double num1 = pop(stack);
  long double num2 = pop(stack);

  push(num1, stack);
  push(num2, stack);

  return;

}

void over(stackStruct * stack) {

  long double num1 = pop(stack);
  long double num2 = pop(stack);
  long double num3 = pop(stack);

  push(num1, stack);
  push(num2, stack);
  push(num3, stack);

}

void add(stackStruct * stack) {

   push(pop(stack) + pop(stack), stack);

}

void subtract(stackStruct * stack) {

  push(pop(stack) - pop(stack), stack);

}

void multiply(stackStruct * stack) {

  push(pop(stack) * pop(stack), stack);

}

void divide(stackStruct * stack) {

  push(pop(stack) / pop(stack), stack);

}

void exponent(stackStruct * stack) {

  push(powl(pop(stack), pop(stack)), stack);

}

void root(stackStruct * stack) {

  long double val = pow(pop(stack), 1.0 / pop(stack));
  push(val, stack);

}

void logarithm(stackStruct * stack) {

  push(log(pop(stack)) / log(pop(stack)), stack);

}

void absolute(stackStruct * stack) {

  push(fabsl(pop(stack)), stack);

}

void print_stack(stackStruct * stack) {

  printf("\n");
  
  for (int i = 0; i < stack->depth; i++) {

    printf("%Lg ", stack->data[i]);

  }

  printf("\n");

}
