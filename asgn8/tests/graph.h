// Header file for CSE 13S section 01 asgn8
// graph.h
// Copied from asgn7
// Removed graph_print()
// Added graph_read()
// DO NOT modify this file.

#include <stdbool.h>
#include <stdio.h>

#ifndef GRAPH
#define GRAPH

#define NAME_BUFFER_SIZE 50

typedef struct graph Graph;

Graph *graph_create(int vertices, bool directed);

void graph_free(Graph **gp);

int graph_vertices(const Graph *g);

void graph_add_edge(Graph *g, int start, int end, int weight);

int graph_get_weight(const Graph *g, int start, int end);

void graph_visit_vertex(Graph *g, int v);

void graph_unvisit_vertex(Graph *g, int v);

bool graph_visited(const Graph *g, int v);

char **graph_get_names(const Graph *g);

void graph_add_vertex(Graph *g, const char *name, int v);

const char *graph_get_vertex_name(const Graph *g, int v);

Graph *graph_read(FILE *f, bool directed);

#endif

