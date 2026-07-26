/*
* File:         test_path_1.c
*
* Purpose:      Test a simple 3-item path.
*
* Exit code:    0 if the test passes.  Non-zero otherwise.
*               (The assert() macro returns non-zero on a failure.)
*/

#include "path.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Running three-item path test.\n");

    // Create a simple graph.
    Graph *g = graph_create(2, 1);
    graph_add_edge(g, 0, 1, 3);
    graph_add_edge(g, 1, 0, 4);

    // Create a path that can only hold three items.
    Path *p = path_create(3);

    // Is the path empty?
    assert(path_vertices(p) == 0);
    assert(path_distance(p) == 0);

    // Add vertexes to the path, checking the total length after each addition.
    path_add(p, 0, g);
    assert(path_vertices(p) == 1);
    assert(path_distance(p) == 0);
    
    path_add(p, 1, g);
    assert(path_vertices(p) == 2);
    assert(path_distance(p) == 3);
    
    path_add(p, 0, g);
    assert(path_vertices(p) == 3);
    assert(path_distance(p) == 7);

    // Remove vertexes from the path, checking the total length.
    path_remove(p, g);
    assert(path_vertices(p) == 2);
    assert(path_distance(p) == 3);
    
    path_remove(p, g);
    assert(path_vertices(p) == 1);
    assert(path_distance(p) == 0);
    
    path_remove(p, g);
    assert(path_vertices(p) == 0);
    assert(path_distance(p) == 0);

    // Free up
    path_free(&p);
    graph_free(&g);

    printf("Three-item path test complete.\n");

    return 0;
}

