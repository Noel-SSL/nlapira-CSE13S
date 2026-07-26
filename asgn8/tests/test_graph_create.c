#include "graph.h"
#include <stdio.h>

// What is this testing? 
//Had to search to get an idea, but this is basically testing creation of our graph
// then if going the correction direction or edges are not stored 
// we also MUST check after all this work it's free and also make sure the pointers
// are set to NULL, otherwise it may be used again
// Testing an undirected and directed graph in both cases


int main(void) {
    //Let's test with vertices
    //What if we have 3?
    Graph *g = graph_create(3, false); // Have 3 vertices and an undirected graph
    if (!g){ // If failed
        return 1;
    }

    graph_add_edge(g,0,1,5); // We need to have an edge going to 0 to 1 with weight of 5

    // Though, we need have statements if it's not 5

    if (graph_get_weight(g,0,1) != 5) {
        return 2;
    }
    if(graph_get_weight(g,1,0)!= 5) {
        return 3;
    }

    Graph *d = graph_create(3,true);
    if(!d){
        return 4;
    }

    graph_add_edge(d,0,1,7);

    if(graph_get_weight(d,0,1) != 7) {
        return 5;
    }
    if (graph_get_weight(d,1,0)!= 0) {
        return 6;
    }

    graph_free(&g);
    graph_free(&d);

    if( g!= NULL || d != NULL){
        return 7;
    }


    return 0;

}

