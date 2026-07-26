#include "graph.h"

// Were just going to test if when doing graph_add_edge function
// it can be rewritten


int main(void){
    Graph *g = graph_create(2,false);
    if(!g){
        return 1;
    }
    // Let's set our edges
    graph_add_edge(g,0,1,5);
    graph_add_edge(g,0,1,8);

    // Check to make sure  0 to 1 has a weight of 8 
    if (graph_get_weight(g,0,1)!=8){
        return 2;
    }
    // Check to make sure 1 to 0 has a weight of 8 (Remember do this for only undirected graph)
    if (graph_get_weight(g,1,0)!=8){
        return 3;
    }

    graph_free(&g);
    if(g != NULL){
        return 4;
    }
    
    return 0;


}