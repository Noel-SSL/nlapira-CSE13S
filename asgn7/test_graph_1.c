/*
* File:         test_graph_1.c
*
* Purpose:      Test a simple 2-vertex undirected graph.
*
* Exit code:    0 if the test passes.  Non-zero otherwise.
*               (The assert() macro returns non-zero on a failure.)
*/

#include "graph.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Running two-vertex graph test.\n");

    Graph *g = graph_create(2, 0);
    assert(g);

    // Confirm that there is no edge between 0 and 1.
    assert(graph_get_weight(g, 0, 1) == 0);
    assert(graph_get_weight(g, 1, 0) == 0);

    graph_add_edge(g, 0, 1, 3);

    // Confirm that the edge has been added.
    assert(graph_get_weight(g, 0, 1) == 3);
    assert(graph_get_weight(g, 1, 0) == 3);

    // Free up
    graph_free(&g);

    printf("Two-vertex graph test complete.\n");

    return 0;
}

