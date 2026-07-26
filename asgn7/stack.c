/*
*
* CSE 13S - Spring 2026 - Assignment 7
*
* stack.c
*
*/

#include "stack.h"

#include <assert.h>
#include <stdlib.h>

typedef struct stack {
    int capacity;       // Maximum number of items in the stack.

    int num_items;      // The number of items in the stack.
                        // Also, the index of the next free space.

    int *items;         // Array of ints that are in the stack.
} Stack;

/*
* Purpose:      Create a Stack
* Parameter:    Maximum number of items that can be in the stack.
* Returns:      A pointer to the new stack.
*/
Stack *stack_create(int capacity) {
    // Attempt to allocate memory for a stack
    Stack *s = calloc(1, sizeof(Stack));
    assert(s);

    s->num_items = 0;
    s->capacity = capacity;
    // We need enough memory for <capacity> numbers
    s->items = calloc(capacity, sizeof(int));
    assert(s->items);

    // We created our stack, return it!
    return s;
}

/*
* Purpose:      Free a Stack
*
* Parameter:    A pointer to a pointer to a Stack.
*
*               First, free the stack at *sp.  After that, set *sp to NULL.
*
* Returns:      Nothing
*/
void stack_free(Stack **sp) {
    // sp is a double pointer, so we have to check if it,
    // or the pointer it points to is null;
    if (sp != NULL && *sp != NULL) {
        // Of course, we have to remember to free the
        // memory for the array of items first,
        // as that was also dynamically allocated!
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        // Free memory allocated for the stack
        free(*sp);
    }
    // Set the pointer to null! This ensures we dont ever do a double free!
    if (sp != NULL) {
        *sp = NULL;
    }
}

/*
* Purpose:      Push an int on the stack.
* Parameters:   A pointer to a Stack and the int to push.
* Returns:      false if the stack is full; true otherwise.
*/
bool stack_push(Stack *s, int val) {
    if (stack_full(s)) {
        return false;
    }

    // Set val
    s->items[s->num_items] = val;

    // Move the top of the stack.
    s->num_items++;

    return true;
}
/* Purpose: Sets the integer pointed to by val to the last item on the stack, and removes the last item on the stack.

    Parameters: s - our pointer of the stack

                val - A pointer that points to an integer (This will help of where to store the pop item)
    
    Returns: True if successful, otherwise False 

*/
bool stack_pop(Stack *s, int *val) {
    if (stack_empty(s)){
        return false;
    }
    s -> num_items -= 1;
    *val = s ->items[s-> num_items];
    
    return true; // Comment
}

/* Purpose: Sets the integer pointed to by val to the last item on the stack, but does not modify the stack.

    Parameters: s - our pointer of the stack

                val - A pointer that points to an integer (This helps pointing to the last item in the stack)
    
    Returns: True if successful, otherwise False 

*/

bool stack_peek(const Stack *s, int *val) {
    if (stack_empty(s)){
        return false;
    }
    *val = s-> items[s->num_items - 1];

    return true; 
}

/* Purpose: Checks true or false if a stack is empty

    Parameters: s - our pointer of the stack

    
    Returns: True if empty, otherwise False 

*/

bool stack_empty(const Stack *s) {
    return s -> num_items == 0;
}

/* Purpose: Checks true or false if a stack is equal to the capacity 

    Parameters: s - our pointer of the stack

    
    Returns: True if full, otherwise False 

*/
bool stack_full(const Stack *s) {
    return s-> num_items == s -> capacity;
}


/* Purpose: Checks the number of items in our stack

    Parameters: s - our pointer of the stack

    
    Returns: The number of items in our stack

*/

int stack_size(const Stack *s) {
    return s -> num_items;
}

/* Purpose: Copies source and stores it into destination and knows how many items are in the stack

    Parameters: dst - Destiniation (Basically where we copying it and storing it)

                src- Source (The source we're copying)

    
    Returns: Nothing

*/
void stack_copy(Stack *dst, const Stack *src) {
    // Remember dst means destiniation and src means source
    // In the assignment description, we need to make sure
    // dst has enough storage from src so let's check
    assert(dst -> capacity >= src -> num_items);
    //Now go through every item
    for (int i = 0; i < src -> num_items; i++){
        dst -> items[i] = src -> items[i];
    }
    //Update to make sure you know how many items are in the stack
    dst -> num_items = src -> num_items;
}

/*
* Purpose:      Print the items of a Stack
* Parameters:   A pointer to a Stack, the output file, and an array of city
*               names to identify each item of the stack.
* Returns:      Nothing
*/
void stack_print(const Stack *s, FILE *outfile, char *cities[]) {
    for (int i = 0; i < s->num_items; i += 1) {
        fprintf(outfile, "%s\n", cities[s->items[i]]);
    }
}

