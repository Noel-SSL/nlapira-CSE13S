/*
*
* CSE 13S - Spring 2026 - Assignment 7
*
* graph.c
*
*/

#include "graph.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//What does each mean?
// verticies - the places in our graph
// directed - True if this is directed graph and only going one way
// visited - places that you visted or haven't visited and all starts with false
// Names are the places your going to visit


typedef struct graph {
    int vertices;
    bool directed;
    bool *visited;
    char **names;
    int **weights;
} Graph;

/*  Purpose: Creates a new graph structure and intialized all of directed to false


    Parameters: vertcies - the number of places in our graph
                
                directed - If this is a directed graph

    Returns: g (To access the graph)
*/


Graph *graph_create(int vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;

    // use calloc() to initialize everything with zeroes
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));

    // allocate g->weights with a pointer to each row
    g->weights = calloc(vertices, sizeof(g->weights[0]));

    // allocate each row in the adjacency matrix
    for (int i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }

    return g;
}
/*  Purpose: To free everything from memory and even the individual names and weights.
            We have loops for names and weights due to them being ** (pointer to a pointer) 
            and have to set each one free
    
    Parameters: **gp - A pointer to a pointer

    Returns: Nothing
*/

void graph_free(Graph **gp) {
    if( gp == NULL || *gp == NULL){
        return;
    }

    // In our loops, we want to free everything, including every weight and name
    // We free everything and not just our structure 

    for (int i = 0; i < (*gp) -> vertices; ++i) {
        free((*gp) -> weights[i]);
    }
    free((*gp) -> weights);

    for (int i = 0; i < (*gp) -> vertices; ++i) {
        free((*gp) -> names[i]);
    }
    free((*gp) -> names);

    free((*gp) -> visited);
    
    free(*gp);

     *gp = NULL;
    //Free **gp by free(*gp)
    //Before this remember to free the stuff in your structure 
    }


/*  Purpose: Gives the city at vertex v the name passed in. They will later copy and store it in 
            the graph 

    Parameters: *g - A pointer of our graph
                
                name - The name that's being copied 

                v- represents our vertex of the listed verticies

    Returns: Nothing
*/


void graph_add_vertex(Graph *g, const char *name, int v) {
    assert(0 <= v && v < g->vertices);

    // if the vertex already has a name, replace it
    if (g->names[v]) {
        free(g->names[v]);
    }

    g->names[v] = strdup(name);
    
}
/*  Purpose: Gets the name of the city with vertex v from the array of city names.
    
    Parameters: *g - A pointer from our Graph

                 v - represents our vertex of the listed verticies

    Returns: g -> names[v]
    The name that's stored in the graph 
*/

const char *graph_get_vertex_name(const Graph *g, int v) {
        assert(0 <= v && v < g -> vertices); // Checks the range within our graph
        return g -> names[v];  //Return the name that's being pointed on the graph
}

/*  Purpose: Gets the names of the every city in an array. 
    
    Parameters: *g - A pointer from our Graph

    Returns: g -> names (A double pointer of an array of strings)
    
*/

char **graph_get_names(const Graph *g) {
    return g-> names;
}

/*  Purpose: Finds the number of vertices in a graph
    
    Parameters: *g - A pointer from our Graph

    Returns: g -> vertices (Returns the number of verticies)
    
*/

int graph_vertices(const Graph *g) {
     return g -> vertices;
}

/*  Purpose: Adds an edge between start and end with weight weight to the adjacency matrix of the graph.
    
    Parameters: *g - A pointer from our Graph
                
                start- The start of our edge
                
                end- The end of our edge

                weight - Amount of time it takes to travel in either directions

    Returns: Nothing
    
*/

void graph_add_edge(Graph *g, int start, int end, int weight) {
    // A directed graph
    g-> weights[start][end] = weight;

    // if undirected
    if(!g -> directed) {
        g ->weights[end][start] = weight;
    }
}

/*  Purpose: Looks up the weight of the edge between start and end and returns it
    
    Parameters: *g - A pointer from our Graph
                
                start- The start of our edge
                
                end- The end of our edge

    Returns: g-> weights[start][end] (The weight between start and end)
    
*/

int graph_get_weight(const Graph *g, int start, int end) {
    return g-> weights[start][end];
}
/*
 Purpose: Adds the vertex v to the list of visited vertices.
    
 Parameters: *g - A pointer from our Graph
            
            v - represents our vertex of the listed verticies
               
Returns: Nothing
    
*/

void graph_visit_vertex(Graph *g, int v) {
    assert(0 <= v && v < g -> vertices);
    g -> visited[v] = true;
        
}

/*
 Purpose: Removes the vertex v from the list of visited vertices.
    
 Parameters: *g - A pointer from our Graph
            
            v - represents our vertex of the listed verticies
               
Returns: Nothing
    
*/

void graph_unvisit_vertex(Graph *g, int v) {
    assert(0 <= v && v < g -> vertices);
    g -> visited[v] = false;
}

/*
 Purpose: Returns true if vertex v is visited in graph g, false otherwise.
    
 Parameters: *g - A pointer from our Graph
            
            v - represents our vertex of the listed verticies
               
Returns: True if visited, false otherwise
    
*/

bool graph_visited(const Graph *g, int v) {
    assert(0 <= v && v < g -> vertices);
    return g -> visited[v];
}

/*
 Purpose: Prints a human-readable representation of a graph. This tests to see if our graph is
            overall correct
    
 Parameters: *g - A pointer from our Graph
            
               
Returns: Nothing
*/

void graph_print(const Graph *g) {
    assert(g!= NULL);
    int n = g ->vertices; //Number of vertices

    printf("Graph with %d verticies:\n", n);

    for(int i = 0; i < n; i++) {
        printf("%d: %s\n",i, g-> names[i]);
    }
    printf("\nAdjacency matrix: \n");

    printf("   ");
    for(int i = 0; i < n; i++) {
        printf("%3d", i);
    }
    printf("\n");

    for(int i = 0; i < n; i++) {
        printf("%3d", i);
        for(int j = 0; j < n; j++) {
             printf("%3d", g-> weights[i][j]);
        }
        printf("\n");
    }
    
}

/*
* Purpose:      Create a new graph, and read an input file in this format:
*               (See Section 2.4 of the assignment PDF for more details.)
*
* 4 <- Number of vertices
* Asgard
* Elysium <- The names of our vertex
* Olympus
* Shangri-La
* 4 <- number of edges
* 0 3 5
* 3 2 4
* 2 1 10
* 1 0 2 <- Start, end and weight
*
* Parameters:   f:          An open FILE * pointer.
*               directed:   true if this is a directed graph.
*
* Returns:      A pointer to the new graph.
*/
Graph *graph_read(FILE *f, bool directed) {
    if(f == NULL) {
        return NULL;
    }
    int num_vertices = 0;

    // Let's see if verticies are valid
    if (fscanf( f, "%d", &num_vertices) != 1 || num_vertices <= 0){
        fprintf(stderr, "tsp:  error reading number of vertices\n");
        exit(1);
    }

    Graph *g = graph_create(num_vertices, directed);

    char namebuf[NAME_BUFFER_SIZE];

    // Go through every vertex name 
    for (int i = 0; i < num_vertices; i++){
        if(fscanf(f, "%s", namebuf)!= 1) {
            graph_add_vertex(g, namebuf, i);
            
        }
    }

    // Let's see the number of edges we have 
    int num_edges = 0;
    if (fscanf( f, "%d", &num_edges) != 1 || num_edges < 0){
        fprintf(stderr, "tsp:  must provide number of edges\n");
        exit(1);
    }

    // Now read through our edges
    int start, end, weight;
    for (int i = 0; i < num_edges; i++){
        if(fscanf(f, "%d %d %d", &start, &end, &weight)!= 3) {
            graph_add_edge(g, start, end, weight);
        }
    }
    return g;
}

// Edges -  line connecting two vertices
// Remember when using scanf, remember to put & when accessung, otherwise it won't know 
// where to access


