#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STACK_DEPTH 1000000
int mode = 0;

typedef struct stackStruct {
  int depth;
  int ptr;
  long double data[MAX_STACK_DEPTH];
} stackStruct;

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

void parse_token(char * ptoken, stackStruct * stack) {

  if (strcmp(ptoken, "+") == 0) {
    add(stack);
    return;
  } else if (strcmp(ptoken, "-") == 0) {
    subtract(stack);
    return;
  } else if (strcmp(ptoken, "*") == 0) {
    multiply(stack);
    return;
  } else if (strcmp(ptoken, "/") == 0) {
    divide(stack);
    return;
  } else if (strcmp(ptoken, "^") == 0) {
    exponent(stack);
    return;
  } else if (strcmp(ptoken, "root") == 0) {
    root(stack);
    return;
  } else if (strcmp(ptoken, "log") == 0) {
    logarithm(stack);
    return;
  } else if (strcmp(ptoken, "abs") == 0) {
    absolute(stack);
    return;
  } else if (strcmp(ptoken, ".") == 0) {
    printf("%Lg\n", peek(stack));
    return;
  } else if (strcmp(ptoken, ".*") == 0) {
    print_stack(stack);
    return;
  } else if (strcmp(ptoken, "drop") == 0) {
    pop(stack);
    return;
  } else if (strcmp(ptoken, "swap") == 0) {
    swap(stack);
    return;
  } else if (strcmp(ptoken, "over") == 0) {
    over(stack);
    return;
  } else if (strtold(ptoken, NULL) != 0 || strcmp(ptoken, "0") == 0) {
    push(strtold(ptoken, NULL), stack);
    return;
  } else if (strcmp(ptoken, "exit") == 0 || strcmp(ptoken, "q") == 0) {
    return;
  }

  printf("Unrecognized Token %s\n", ptoken);
  if (mode == 0) {
    exit(EXIT_FAILURE);
  }

  return;

}

void parse_expression(char * expression, stackStruct * stack) {

  char * ptoken = strtok(expression, " ");
  while (ptoken != NULL) {

    parse_token(ptoken, stack);
    ptoken = strtok(NULL, " ");

  }

  return;

}

void interactive_console(stackStruct * stack) {

  char buff[1001];


  while (strcmp(buff, "exit") != 0 && strcmp(buff, "q") != 0) {

    printf("\n> ");  
    fgets(buff, 1000, stdin);
    if ((strlen(buff) > 0) && (buff[strlen(buff) - 1] == '\n')) {
      buff[strlen (buff) - 1] = '\0';
    }
    parse_expression(buff, stack);
    
  }

  return;

}

int main(int argc, char *argv[]) {

  static struct stackStruct stack = {
    .depth = 0,
    .ptr = 0,
    .data[0] = 0
  };

	if (argc > 1) {
		char c = '\0';
		while ((c = getopt(argc, argv, "f:e:")) != -1) {
			switch (c) {
				case 'f':
					break;
				case 'e':
          parse_expression(optarg, &stack);
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

	} else {

    mode = 1;
    interactive_console(&stack);

  }

}
