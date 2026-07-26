#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* =======================================================================
* Here are several functions that manually create trees of various sizes.
* =======================================================================
*/

/*
* Allocate an empty tree.
*/
Tree *alloc_empty_tree(void) {
    Tree *t = calloc(1, sizeof(Tree));
    return t;
}

/*
* Allocate a one-node tree.
*
*        1
*       N N
*/
Tree *alloc_one_node_tree(void) {
    Node *n = calloc(1, sizeof(Node));

    n->key = 100;
    n->count = 1;

    Tree *t = calloc(1, sizeof(Tree));
    t->root = n;
    return t;
}


/*
* Allocate a three-node tree that skews to the right.
*
*      1
*     N \
*        2
*       N \
*          3
*         N N
*/
Tree *alloc_right_skewed_tree(void) {
    // allocate nodes four nodes (ignore node 0)
    Node *n = calloc(4, sizeof(Node));

    for (int i = 1; i <= 3; ++i) {
        n[i].key = 100 * i;
        n[i].count = i;
    }

    n[1].right = &n[2];
    n[2].right = &n[3];

    Tree *t = calloc(1, sizeof(Tree));
    t->root = &n[1];
    return t;
}

/*
* Allocate a three-node tree that skews to the left.
*
*          3
*         / N
*        2
*       / N
*      1
*     N N
*/
Tree *alloc_left_skewed_tree(void) {
    // allocate nodes four nodes (ignore node 0)
    Node *n = calloc(4, sizeof(Node));

    for (int i = 1; i <= 3; ++i) {
        n[i].key = 100 * i;
        n[i].count = i;
    }

    n[3].left = &n[2];
    n[2].left = &n[1];

    Tree *t = calloc(1, sizeof(Tree));
    t->root = &n[3];
    return t;
}

/*
* Allocate a balanced three-node tree.
*
*         2
*       /   \
*      1     3
*     N N   N N
*/
Tree *alloc_three_node_tree(void) {
    // allocate four nodes (ignore node 0)
    Node *n = calloc(4, sizeof(Node));

    for (int i = 1; i <= 3; ++i) {
        n[i].key = 100 * i;
        n[i].count = i;
    }

    n[2].left  = &n[1];
    n[2].right = &n[3];

    Tree *t = calloc(1, sizeof(Tree));
    t->root = &n[2];
    return t;
}

/*
* Allocate a balanced seven-node tree.
*
*               4
*            /     \
*         2           6
*       /   \       /   \
*      1     3     5     7
*     N N   N N   N N   N N
*/
Tree *alloc_seven_node_tree(void) {
    // allocate nodes eight nodes (ignore node 0)
    Node *n = calloc(8, sizeof(Node));

    for (int i = 1; i <= 7; ++i) {
        n[i].key = 100 * i;
        n[i].count = i;
    }

    n[4].left  = &n[2];
    n[4].right = &n[6];
    n[2].left  = &n[1];
    n[2].right = &n[3];
    n[6].left  = &n[5];
    n[6].right = &n[7];

    Tree *t = calloc(1, sizeof(Tree));
    t->root = &n[4];
    return t;
}

/*
* ===========================================
* Test printing the manually allocated trees.
* ===========================================
*/

/*
* Test printing empty tree.
*/
void test_print_empty(void) {
    Tree *t = alloc_empty_tree();
    printf("expect no output\n");
    printf("-----\n");
    tree_print(t);
    printf("-----\n");

}

/*
* Test printing one-node tree.
*/
void test_print_one_node(void) {
    Tree *t = alloc_one_node_tree();
    printf("expect one line \"1 100\"\n");
    printf("-----\n");
    tree_print(t);
    printf("-----\n");
}

/*
* Test printing right-skewed tree.
*/
void test_print_right_skewed(void) {
    Tree *t = alloc_right_skewed_tree();
    printf("expect three lines \"1 100\", \"2 200\", \"3 300\"\n");
    printf("-----\n");
    tree_print(t);
    printf("-----\n");
}

/*
* Test printing left-skewed tree.
*/
void test_print_left_skewed(void) {
    Tree *t = alloc_left_skewed_tree();
    printf("expect three lines \"1 100\", \"2 200\", \"3 300\"\n");
    printf("-----\n");
    tree_print(t);
    printf("-----\n");
}

/*
* Test printing three-node tree.
*/
void test_print_three_nodes(void) {
    Tree *t = alloc_three_node_tree();
    printf("expect three lines \"1 100\", \"2 200\", \"3 300\"\n");
    printf("-----\n");
    tree_print(t);
    printf("-----\n");
}

/*
* Test printing seven-node tree.
*/
void test_print_seven_nodes(void) {
    Tree *t = alloc_seven_node_tree();
    printf("expect seven lines \"1 100\", \"2 200\", ... \"7 700\"\n");
    printf("-----\n");
    tree_print(t);
    printf("-----\n");
}

/*
* =======================================
* Test allocating trees of various sizes.
* =======================================
*/

/*
* Test allocating an empty tree.
*/
void test_alloc_empty(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    // verify empty tree
    assert(tree->root == NULL);

    printf("PASS\n");
}

/*
* Test allocating a one-node tree.
*
*       200
*      N   N
*/
void test_alloc_one_node(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    tree_add(tree, 200);  // key is 2
    tree_add(tree, 200);  // now count is 2.

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 200);
    assert(tree->root->count == 2);
    assert(tree->root->left == NULL);
    assert(tree->root->right == NULL);

    printf("PASS\n");
}

/*
* Test allocating a three-node tree that skews to the right.
*
*      1
*     N \
*        2
*       N \
*          3
*         N N
*/
void test_alloc_right_skew(void) {
    Tree *tree = tree_alloc();

    // order of nodes defines tree structure
    assert(tree);
    tree_add(tree, 100);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // increment some counts
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 100);
    assert(tree->root->count == 1);
    assert(tree->root->left == NULL);
    assert(tree->root->right != NULL);

    assert(tree->root->right->key == 200);
    assert(tree->root->right->count == 2);
    assert(tree->root->right->left == NULL);
    assert(tree->root->right->right != NULL);

    assert(tree->root->right->right->key == 300);
    assert(tree->root->right->right->count == 3);
    assert(tree->root->right->right->left == NULL);
    assert(tree->root->right->right->right == NULL);

    printf("PASS\n");
}

/*
* Test allocating a three-node tree that skews to the left.
*
*          3
*         / N
*        2
*       / N
*      1
*     N N
*/
void test_alloc_left_skew(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    // order of nodes defines tree structure
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 100);

    // increment some counts
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 300);
    assert(tree->root->count == 3);
    assert(tree->root->left != NULL);
    assert(tree->root->right == NULL);

    assert(tree->root->left->key == 200);
    assert(tree->root->left->count == 2);
    assert(tree->root->left->left != NULL);
    assert(tree->root->left->right == NULL);

    assert(tree->root->left->left->key == 100);
    assert(tree->root->left->left->count == 1);
    assert(tree->root->left->left->left == NULL);
    assert(tree->root->left->left->right == NULL);

    printf("PASS\n");
}

/*
* Test allocating a three-node balanced tree.
*
*          2
*        /   \
*      1       3
*     N N     N N
*/
void test_alloc_three_nodes(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    // order of nodes defines tree structure
    tree_add(tree, 200);
    tree_add(tree, 300);
    tree_add(tree, 100);

    // increment some counts
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 200);
    assert(tree->root->count == 2);
    assert(tree->root->left != NULL);
    assert(tree->root->right != NULL);

    assert(tree->root->left->key == 100);
    assert(tree->root->left->count == 1);
    assert(tree->root->left->left == NULL);
    assert(tree->root->left->right == NULL);

    assert(tree->root->right->key == 300);
    assert(tree->root->right->count == 3);
    assert(tree->root->right->left == NULL);
    assert(tree->root->right->right == NULL);

    printf("PASS\n");
}

/*
* Test a seven-node balanced tree.
*
*               4
*            /     \
*         2           6
*       /   \       /   \
*      1     3     5     7
*     N N   N N   N N   N N
*/
void test_alloc_seven_nodes(void) {
    Tree *tree = tree_alloc();

    // order of nodes defines tree structure
    assert(tree);
    tree_add(tree, 400);
    tree_add(tree, 600);
    tree_add(tree, 500);
    tree_add(tree, 200);
    tree_add(tree, 100);
    tree_add(tree, 300);
    tree_add(tree, 700);

    // increment some counts
    for (int i = 0; i < 1; ++i) tree_add(tree, 200);
    for (int i = 0; i < 2; ++i) tree_add(tree, 300);
    for (int i = 0; i < 3; ++i) tree_add(tree, 400);
    for (int i = 0; i < 4; ++i) tree_add(tree, 500);
    for (int i = 0; i < 5; ++i) tree_add(tree, 600);
    for (int i = 0; i < 6; ++i) tree_add(tree, 700);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 400);
    assert(tree->root->count == 4);
    assert(tree->root->left != NULL);
    assert(tree->root->right != NULL);

    assert(tree->root->left->key == 200);
    assert(tree->root->left->count == 2);
    assert(tree->root->left->left != NULL);
    assert(tree->root->left->right != NULL);

    assert(tree->root->right->key == 600);
    assert(tree->root->right->count == 6);
    assert(tree->root->right->left != NULL);
    assert(tree->root->right->right != NULL);

    assert(tree->root->left->left->key == 100);
    assert(tree->root->left->left->count == 1);
    assert(tree->root->left->left->left == NULL);
    assert(tree->root->left->left->right == NULL);

    assert(tree->root->left->right->key == 300);
    assert(tree->root->left->right->count == 3);
    assert(tree->root->left->right->left == NULL);
    assert(tree->root->left->right->right == NULL);

    assert(tree->root->right->left->key == 500);
    assert(tree->root->right->left->count == 5);
    assert(tree->root->right->left->left == NULL);
    assert(tree->root->right->left->right == NULL);

    assert(tree->root->right->right->key == 700);
    assert(tree->root->right->right->count == 7);
    assert(tree->root->right->right->left == NULL);
    assert(tree->root->right->right->right == NULL);

    printf("PASS\n");
}

/*
* ===================================================
* Test allocating and freeing trees of various sizes.
* ===================================================
*/

/*
* Allocate and free an empty tree.
*/
void test_alloc_free_empty(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    // verify empty tree
    assert(tree->root == NULL);

    tree_free(&tree);
    assert(tree == NULL);

    printf("PASS\n");
}

/*
* Allocate and free a one-node tree.
*
*       200
*      N   N
*/
void test_alloc_free_one_node(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    tree_add(tree, 200);  // key is 200
    tree_add(tree, 200);  // now count is 2.

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 200);
    assert(tree->root->count == 2);
    assert(tree->root->left == NULL);
    assert(tree->root->right == NULL);

    tree_free(&tree);
    assert(tree == NULL);

    printf("PASS\n");
}

/*
* Allocate and free a three-node tree that skews to the right.
*
*      1
*     N \
*        2
*       N \
*          3
*         N N
*/
void test_alloc_free_right_skew(void) {
    Tree *tree = tree_alloc();

    // order of nodes defines tree structure
    assert(tree);
    tree_add(tree, 100);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // increment some counts
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 100);
    assert(tree->root->count == 1);
    assert(tree->root->left == NULL);
    assert(tree->root->right != NULL);

    assert(tree->root->right->key == 200);
    assert(tree->root->right->count == 2);
    assert(tree->root->right->left == NULL);
    assert(tree->root->right->right != NULL);

    assert(tree->root->right->right->key == 300);
    assert(tree->root->right->right->count == 3);
    assert(tree->root->right->right->left == NULL);
    assert(tree->root->right->right->right == NULL);

    tree_free(&tree);
    assert(tree == NULL);

    printf("PASS\n");
}

/*
* Test allocating a three-node tree that skews to the left.
*
*          3
*         / N
*        2
*       / N
*      1
*     N N
*/
void test_alloc_free_left_skew(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    // order of nodes defines tree structure
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 100);

    // increment some counts
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 300);
    assert(tree->root->count == 3);
    assert(tree->root->left != NULL);
    assert(tree->root->right == NULL);

    assert(tree->root->left->key == 200);
    assert(tree->root->left->count == 2);
    assert(tree->root->left->left != NULL);
    assert(tree->root->left->right == NULL);

    assert(tree->root->left->left->key == 100);
    assert(tree->root->left->left->count == 1);
    assert(tree->root->left->left->left == NULL);
    assert(tree->root->left->left->right == NULL);

    tree_free(&tree);
    assert(tree == NULL);

    printf("PASS\n");
}

/*
* Test a three-node balanced tree.
*
*          2
*        /   \
*      1       3
*     N N     N N
*/
void test_alloc_free_three_nodes(void) {
    Tree *tree = tree_alloc();
    assert(tree);

    // order of nodes defines tree structure
    tree_add(tree, 200);
    tree_add(tree, 300);
    tree_add(tree, 100);

    // increment some counts
    tree_add(tree, 300);
    tree_add(tree, 200);
    tree_add(tree, 300);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 200);
    assert(tree->root->count == 2);
    assert(tree->root->left != NULL);
    assert(tree->root->right != NULL);

    assert(tree->root->left->key == 100);
    assert(tree->root->left->count == 1);
    assert(tree->root->left->left == NULL);
    assert(tree->root->left->right == NULL);

    assert(tree->root->right->key == 300);
    assert(tree->root->right->count == 3);
    assert(tree->root->right->left == NULL);
    assert(tree->root->right->right == NULL);

    tree_free(&tree);
    assert(tree == NULL);

    printf("PASS\n");
}

/*
* Test a seven-node balanced tree.
*
*               4
*            /     \
*         2           6
*       /   \       /   \
*      1     3     5     7
*     N N   N N   N N   N N
*/
void test_alloc_free_seven_nodes(void) {
    Tree *tree = tree_alloc();

    // order of nodes defines tree structure
    assert(tree);
    tree_add(tree, 400);
    tree_add(tree, 600);
    tree_add(tree, 500);
    tree_add(tree, 200);
    tree_add(tree, 100);
    tree_add(tree, 300);
    tree_add(tree, 700);

    // increment some counts
    for (int i = 0; i < 1; ++i) tree_add(tree, 200);
    for (int i = 0; i < 2; ++i) tree_add(tree, 300);
    for (int i = 0; i < 3; ++i) tree_add(tree, 400);
    for (int i = 0; i < 4; ++i) tree_add(tree, 500);
    for (int i = 0; i < 5; ++i) tree_add(tree, 600);
    for (int i = 0; i < 6; ++i) tree_add(tree, 700);

    // verify tree structure
    assert(tree->root != NULL);

    assert(tree->root->key == 400);
    assert(tree->root->count == 4);
    assert(tree->root->left != NULL);
    assert(tree->root->right != NULL);

    assert(tree->root->left->key == 200);
    assert(tree->root->left->count == 2);
    assert(tree->root->left->left != NULL);
    assert(tree->root->left->right != NULL);

    assert(tree->root->right->key == 600);
    assert(tree->root->right->count == 6);
    assert(tree->root->right->left != NULL);
    assert(tree->root->right->right != NULL);

    assert(tree->root->left->left->key == 100);
    assert(tree->root->left->left->count == 1);
    assert(tree->root->left->left->left == NULL);
    assert(tree->root->left->left->right == NULL);

    assert(tree->root->left->right->key == 300);
    assert(tree->root->left->right->count == 3);
    assert(tree->root->left->right->left == NULL);
    assert(tree->root->left->right->right == NULL);

    assert(tree->root->right->left->key == 500);
    assert(tree->root->right->left->count == 5);
    assert(tree->root->right->left->left == NULL);
    assert(tree->root->right->left->right == NULL);

    assert(tree->root->right->right->key == 700);
    assert(tree->root->right->right->count == 7);
    assert(tree->root->right->right->left == NULL);
    assert(tree->root->right->right->right == NULL);

    tree_free(&tree);
    assert(tree == NULL);

    printf("PASS\n");
}

#define NUM_TESTS 18

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./unittests NUMBER_OF_TESTS (1 to %d)\n", NUM_TESTS);
        exit(0);
    }

    int m = atoi(argv[1]);

    if (m > NUM_TESTS) {
        printf("Usage: ./unittests NUMBER_OF_TESTS (1 to %d)\n", NUM_TESTS);
        exit(0);
    }

    printf("Running %d of %d tests\n", m, NUM_TESTS);

    for (int i = 1; i <= m; ++i) {
        printf("\ntest %d:\n", i);

        switch (i) {
            case 1: test_print_empty(); break;
            case 2: test_print_one_node(); break;
            case 3: test_print_right_skewed(); break;
            case 4: test_print_left_skewed(); break;
            case 5: test_print_three_nodes(); break;
            case 6: test_print_seven_nodes(); break;

            case 7: test_alloc_empty(); break;
            case 8: test_alloc_one_node(); break;
            case 9: test_alloc_right_skew(); break;
            case 10: test_alloc_left_skew(); break;
            case 11: test_alloc_three_nodes(); break;
            case 12: test_alloc_seven_nodes(); break;

            case 13: test_alloc_free_empty(); break;
            case 14: test_alloc_free_one_node(); break;
            case 15: test_alloc_free_right_skew(); break;
            case 16: test_alloc_free_left_skew(); break;
            case 17: test_alloc_free_three_nodes(); break;
            case 18: test_alloc_free_seven_nodes(); break;
            // Rememeber to update NUM_TESTS
        }
    }

    printf("\n");
    printf("Have we proven that your Tree ADT has no bugs?\n");
    printf("No.  We cannot prove that a program works.\n");
    printf("We can only show when it doesn't work.\n");

    return 0;
}

