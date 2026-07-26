#include "stack.h"


// What does this do?
// We basically create a Stack and did an example and did cases where the functions should not fail



int main(void){
    // Let's Create a graph
    Stack *s = stack_create(2);
    if (!s){
        return 1; // If failed exit
    }

    if(!stack_empty(s)){ // Check that when we make the stack it must be empty
        return 2;
    }
    // Now push the values
    if (!stack_push(s,10)){
        return 3;
    }
    if (!stack_push(s,20)){
        return 4;
    }
    // We need to check if the pushed values are there making the stack
    // If not, then it fails 
    if(!stack_full(s)){
        return 5;
    }

    int v = -1; // This is where we store our pop values later

    // These pop values should pop the values in the stack
    // If failed, return and exit
    if(!stack_pop(s,&v)){
        return 6;
    }
    if(v != 20){
        return 7;
    }

    if(!stack_pop(s,&v)){
        return 8;
    }
    if(v!= 10){
        return 9;
    }

    // After we pop our values, check to see if our stack is empty
    if (!stack_empty(s)){
        return 10;
    }
    // Now free from memory
    stack_free(&s);
    if (s !=  NULL){
        return 11;
    }

    return 0;



}
