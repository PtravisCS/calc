#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STACK_DEPTH 1000000

typedef struct stackStruct {
  int depth;
  int ptr;
  long double data[MAX_STACK_DEPTH];
} stackStruct;

struct stackStruct stack = {
  .depth = 0,
  .ptr = 0,
  .data[0] = 0
};

int push(long double num) {

  if (stack.depth < MAX_STACK_DEPTH) {

    stack.data[stack.depth + 1] = num;
    stack.depth++;
    stack.ptr++;
    return stack.depth;

  } else {

    printf("Stack Overflow\nCould not push %Lf onto stack, stack is full\n", num);
    exit(EXIT_FAILURE);

  }

}

long double pop() {

  if (stack.depth > 0) {

    long double num = stack.data[stack.depth];
    stack.data[stack.depth] = 0;
    stack.depth--;
    stack.ptr--;

    return num;

  } else {

    printf("Stack Undeflow\n");
    exit(EXIT_FAILURE);

  }

}

long double peek() {

  return stack.data[stack.depth];

}

void add() {

   push(pop() + pop());

}

void subtract() {

  push(pop() - pop());

}

void multiply() {

  push(pop() * pop());

}

void divide() {

  push(pop() / pop());

}

void exponent() {

  push(powl(pop(), pop()));

}

void root() {

  long double val = pow(pop(), 1.0 / pop());
  push(val);

}

void logarithm() {

  push(log(pop()) / log(pop()));

}

void absolute() {

  push(fabsl(pop()));

}

void parse_token(char * ptoken) {

  if (strcmp(ptoken, "+") == 0) {
    add();
    return;
  } else if (strcmp(ptoken, "-") == 0) {
    subtract();
    return;
  } else if (strcmp(ptoken, "*") == 0) {
    multiply();
    return;
  } else if (strcmp(ptoken, "/") == 0) {
    divide();
    return;
  } else if (strcmp(ptoken, "^") == 0) {
    exponent();
    return;
  } else if (strcmp(ptoken, "root") == 0) {
    root();
    return;
  } else if (strcmp(ptoken, "log") == 0) {
    logarithm();
    return;
  } else if (strcmp(ptoken, "abs") == 0) {
    absolute();
    return;
  } else if (strcmp(ptoken, ".") == 0) {
    printf("%Lg\n", peek());
    return;
  } else if (strtold(ptoken, NULL) != 0 || strcmp(ptoken, "0") == 0) {
    push(strtold(ptoken, NULL));
    return;
  }

  printf("Unrecognized Token %s", ptoken);
  exit(EXIT_FAILURE);

  return;

}

long double parseExpression(char * expression) {

  char * ptoken = strtok(expression, " ");
  while (ptoken != NULL) {

    parse_token(ptoken);
    ptoken = strtok(NULL, " ");

  }

  return 5.0;

}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		char c = '\0';
		while ((c = getopt(argc, argv, "f:e:")) != -1) {
			switch (c) {
				case 'f':
					break;
				case 'e':
          parseExpression(optarg);
					break;
				case '?':
					printf("\nRPN calculation interpreter.\n");
					printf("syntax: calc [-e command][-f file][-?]\n\n");
					printf("DESCRIPTION\n");
					printf("calc is an RPN (prefix-notation) calculation interpreter\n");
					printf("calc can be called with a file in order to parse that file\n");
					printf("-f \t the name of a file to parse\n");
					printf("-e \t an expression to parse\n");
					exit(EXIT_FAILURE);
				default:
					printf("Unrecognised option, try -?\n");
					exit(EXIT_FAILURE);
			}
		}

	}
}
