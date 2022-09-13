#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "math_funcs.h"

int mode = 0;

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
