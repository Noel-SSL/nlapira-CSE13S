// Header file for CSE 13S Section 1 asgn7
// stack.h
// Made by Jess Srinivas
// DO NOT remove any functions from this file.


#include <stdbool.h>
#include <stdio.h>

#ifndef STACK
#define STACK

typedef struct stack Stack;

Stack *stack_create(int capacity);

void stack_free(Stack **sp);

bool stack_push(Stack *s, int val);

bool stack_pop(Stack *s, int *val);

bool stack_peek(const Stack *s, int *val);

bool stack_empty(const Stack *s);

bool stack_full(const Stack *s);

int stack_size(const Stack *s);

void stack_copy(Stack *dst, const Stack *src);

void stack_print(const Stack *s, FILE *f, char *vals[]);

#endif

