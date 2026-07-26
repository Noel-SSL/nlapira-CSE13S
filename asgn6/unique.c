/*
* Which other #include files are needed?
* Put them below.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For string comparsion
#include <ctype.h> // Added to have a function to check if it's not a digit (!isdigit)
#include <stdbool.h> // Need to have this to check if something was seen in our tree
#include "tree.h" // If we didn't have this, most of our functions in our main
// will be "undeclared"

void print_usage(void) {
    printf("Usage:  unique NUM NUM NUM ...       (normal output)\n");
    printf("        unique -d NUM NUM NUM ...    (debugging output)\n");
    exit(0);
}
/*  Purpose: It loops to check if it's not a digit, 
            if it's not a digit call print_usage()

    Parameters: s - Pointer to a string

    Returns: Nothing
*/

void check_number(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) { // Checking the value one at a time  
        if (!isdigit(s[i])) {
            print_usage();
        }
    }
}
/*  Purpose: This will set a new tree and now makes a tree and use all the functions
            like tree_add, check_number etc. This wil add on into our tree and it takes
            notes like if "-d" was seen. The purpose of this function is to add the roots to our
            tree based on our argc

    Parameters: argc- Basically how much is on our command line 

                argv - The values on the command line (111, 222, 333 etc)

    Returns: Nothing
*/

int main(int argc, char **argv) {
    // Make sure you put necessary files on top
    // If you don't, you will have a lot of variables "undeclared"
    Tree *tree = tree_alloc();
    bool seen = false;

    //Now let's loop and check each argc and see if argv[i], "-d" was seen
    for(int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-d") == 0) {
            seen = true;
            continue;
        }else{
            //If not then checks if it's not a digit and adds to the tree
            check_number(argv[i]);
            // Atoi basically means converts string into an int (I was confused about that)
            tree_add(tree, atoi(argv[i]));
        }
    }
    if (seen == true) {
        tree_dump(tree);
    }else {
        tree_print(tree);
    }

    tree_free(&tree);


}
