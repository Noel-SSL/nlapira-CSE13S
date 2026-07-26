#include "path.h"
#include "graph.h"


//


int main(void){
    // Let's create a graph and make sure it doesn't fail
    Graph *g = graph_create(3,false);
    if(!g){
        return 1;
    }

    graph_add_edge(g,0,1,5);
    graph_add_edge(g,1,2,7); // Remember it's 1 to 2 and have a weight of 7

    Path *p = path_create(3);
    if(!p){
        return 2;
    }
    
    path_add(p,0,g);
    // Check for path_add and the distance should be 0
    if(path_distance(p) != 0){
        return 3;
    }
     // Check for path_add and the distance should be 5
    path_add(p,1,g);
    if(path_distance(p) !=5){
        return 4;
    }
     // Check for path_add and the distance should be 12
    path_add(p,2,g);
    if (path_distance(p)!= 12){
        return 5;
    }
    // Remove a path and go back and make suring that distance is 5
    path_remove(p,g);
    if(path_distance(p) !=5){
        return 6;
    }
    // Remove a path and go back and make suring that distance is 0
    path_remove(p,g);
    if(path_distance(p) != 0){
        return 7;
    }
    // Free and check our pointers 
    path_free(&p);
    graph_free(&g);

    if (p != NULL || g != NULL){
        return 8;
    }

    return 0;

    












}