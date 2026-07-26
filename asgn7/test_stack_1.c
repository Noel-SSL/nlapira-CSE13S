/*
* File:         test_stack_1.c
*
* Purpose:      Test a simple 1-item stack.
*
* Exit code:    0 if the test passes.  Non-zero otherwise.
*               (The assert() macro returns non-zero on a failure.)
*/

#include "stack.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Running one-item stack test.\n");

    // Create a stack that can only hold one item
    Stack *s = stack_create(1);

    // Add 10 to the stack
    assert(stack_push(s, 10));

    // make srue that the top of the stack is 10 when we peek!
    int x = 0;
    assert(stack_peek(s, &x));
    assert(x == 10);

    // make sure the stack is full!
    assert(stack_full(s));

    // Make sure we can remove the item from the stack
    x = 2;
    stack_pop(s, &x);
    assert(x == 10);
    assert(stack_empty(s));

    // Free up
    stack_free(&s);

    printf("One-item stack tests complete.\n");

    return 0;
}

