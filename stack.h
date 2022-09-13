#ifndef stack_h
#define stack_h

#define MAX_STACK_DEPTH 1000000

typedef struct stackStruct {
  int depth;
  int ptr;
  long double data[MAX_STACK_DEPTH];
} stackStruct;

#endif
