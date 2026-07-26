// Header file for CSE 13S Section 1 asgn7
// path.h
// Made by Jess Srinivas
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

void path_print(const Path *p, FILE *f, const Graph *g);

#endif

