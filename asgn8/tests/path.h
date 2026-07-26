// Header file for CSE 13S Section 1 asgn7
// path.h
// Copied from asgn7
// Removed path_print()
// DO NOT modify this file.

#include "graph.h"
#include "stack.h"

#include <stdbool.h>

#ifndef PATH
#define PATH

typedef struct path Path;

Path *path_create(int capacity);

void path_free(Path **pp);

int path_vertices(const Path *p);

int path_distance(const Path *p);

void path_add(Path *p, int val, const Graph *g);

int path_remove(Path *p, const Graph *g);

void path_copy(Path *dst, const Path *src);

#endif

