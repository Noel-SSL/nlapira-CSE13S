/*
*
* CSE 13S - Spring 2026 - Assignment 7
*
* path.c
*
*/

#include "path.h"

#include <assert.h>
#include <stdlib.h>

typedef struct path {
    int total_weight;
    Stack *vertices;
} Path;

/* Purpose: Creates a path data structure, containing a Stack and a weight of zero

Parameters: Capacity - Basically the size 

Returns: P (The pointer back to the user)

*/

Path *path_create(int capacity) {
    // Most of the assert are checking if we have something corrupted in memory or we somehow have NULL
    Path *p = calloc(1, sizeof(Path));
    assert(p);
    p -> total_weight = 0;
    p -> vertices = stack_create(capacity);

    return p;
    
}


/* Purpose: Frees a path, and all its associated memory

Parameters: **pp - a pointer to a pointer in our Path

Returns: Nothing

*/

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        if ((*pp)-> vertices != NULL){
            stack_free(&(*pp)-> vertices);
        }
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }

}

/* Purpose: Finds the distance covered by a path.

Parameters: *p - our pointer for our Graph

Returns: total_weight (Basically your total distance)

*/


int path_distance(const Path *p) {
    return p -> total_weight;
}

/*
* Purpose:      Add an item to the path.
*
*                   Path Before:    [0] --> [3] --> [5]
*
*                   Call:           path_add(p, 7, G);
*
*                   Path After:     [0] --> [3] --> [5] --> [7]
*
*               Uses graph G to get the weight from node [5] to node [7].
*
*               Also update the total_weight (total distance) of the path,
*               based on the weight from the current last item of the path
*               and the item that we are adding.
*
* Parameters:   The path, item to add, and the graph (for the edge weights).
*
* Returns:      Nothing.
*/
void path_add(Path *p, int v, const Graph *G) {

    if(stack_empty(p -> vertices)){
        stack_push(p -> vertices, v);
        return;
    }

    // You don't add any weight if like path_add(7) or a []
    // Do an if statement to check if we haven't move yet or have [] path
    // We have to figure out what happens to total_weight and stack
    int last_visted_vertex;
    stack_peek(p-> vertices, & last_visted_vertex);
    int weight = graph_get_weight(G, last_visted_vertex, v); // V basically means destination
    p -> total_weight += weight;
    
    
    
    stack_push(p->vertices, v);
}

/*
* Purpose:      Remove the last item of the path.
*
*                   Path Before:    [0] --> [3] --> [5] --> [7]
*
*                   Call:           path_remove(p, G);
*
*                   Path After:     [0] --> [3] --> [5]
*
*                   Returns:        7
*
*               Uses graph G to get the weight from node [5] to node [7].
*
*               Also update the total_weight (total distance) of the path,
*               based on the weight from the current last item of the path
*               and the item that we are adding.
*
* Parameters:   The path and the graph (for the edge weights).
*
* Returns:      The item that was removed.
*/
int path_remove(Path *p, const Graph *G) {
    //Implent when a path is empty
    // implement when path has one vertex
    //How should total_weight be updated?

    // We have to define every condition and if there's 2+ vertices
    //Update the distance and length of the path

    // If None
    if(stack_empty(p -> vertices)){
        return 0;
    }
    

    int removed;
    stack_pop(p -> vertices, &removed);

    if (stack_empty(p->vertices)){
        p -> total_weight = 0;
        return removed;
    }


    int new_last_vertex;
    stack_peek(p -> vertices, &new_last_vertex);

    int weight = graph_get_weight(G, new_last_vertex, removed); // Confused by this line, but
    //it basically gets the weight and after subtracts the total_weight
    p -> total_weight -= weight;
    
    
    
    return removed;
}

/*
* Purpose:      Print the current path.
* Parameters:   Path, file to print to, and the graph (for the city names).
* Returns:      Nothing.
*/
void path_print(const Path *p, FILE *f, const Graph *g) {
    // This is like a safeguard and the parameters given and what you're printing
    // check if it's valid befire printing
    if (p == NULL || p -> vertices == NULL || g == NULL || f == NULL){
        return;
    }
    stack_print(p -> vertices, f, graph_get_names(g));
    fprintf(f, "Total Distance: %d\n", p->total_weight);
}

/*
* Purpose:      Finds the number of vertices in a path
* Parameters:   *p - Our pointer for our Path
* Returns:      stack_size(p -> vertices) <- Number of vertices
*/

int path_vertices(const Path *p) {
    if (p == NULL ||p -> vertices == NULL){
        return 0;
    }

    return stack_size(p -> vertices);
}


/*
* Purpose:      Copies a path from src to dst.

* Parameters:   dst- Destiniation of where it's being copied

                src - The source that's being copied

* Returns:      Nothing
*/

void path_copy(Path *dst, const Path *src) {
    if (dst == NULL || src == NULL || dst -> vertices == NULL || src ->vertices == NULL ){
        return;
    }
    dst -> total_weight = src -> total_weight;

    stack_copy(dst -> vertices,src -> vertices );
}

