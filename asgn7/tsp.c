/*
*
* CSE 13S - Spring 2026 - Assignment 7
*
* tsp.c
*
*/

#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <bits/getopt_core.h> // Deleted before
#include <getopt.h> // Deleted before



int start_vertex = 0;


char *help =
"Usage: tsp [options]\n"
"\n"
"-i infile    Specify the input file path containing the cities and edges\n"
"             of a graph. If not specified, the default input should be\n"
"             set as stdin.\n"
"\n"
"-o outfile   Specify the output file path to print to. If not specified,\n"
"             the default output should be set as stdout.\n"
"\n"
"-d           Specifies the graph to be directed.\n"
"\n"
"-h           Prints out a help message describing the purpose of the\n"
"             graph and the command-line options it accepts, exiting the\n"
"             program afterwards.\n";


/*
* procedure DFS (G,v):
*     label v as visited
*
*     for all edges from v to w in G. adjacentEdges (v) do
*         if vertex w is not labeled as visited then
*             recursively call DFS (G,w)
*
*     label v as unvisited
*/



void dfs(Graph *G, int v, Path *curr, Path *shortest, FILE *outfile) {
    graph_visit_vertex(G,v);
    path_add(curr, v, G);


    //See if we visited all cities and go back to the start point
    if (path_vertices(curr) == graph_vertices(G)) {
        int w = graph_get_weight(G, v, start_vertex);
        if (w > 0) {
            path_add(curr, start_vertex, G);
            
            if(path_vertices(shortest) == 0 || path_distance(curr) < path_distance(shortest)){
                path_copy(shortest,curr);
            }
            path_remove(curr,G);
        }
    }else{
        //Check every city that's not been visited
        for(int u = 0; u < graph_vertices(G); u++) {
            if(!graph_visited(G,u) && graph_get_weight(G,v,u) > 0){
                dfs(G, u, curr, shortest, outfile); // Explore the next city using recursion
            
            }
        }
    } 
    // Allows us to backtrack and go to other paths 
    graph_unvisit_vertex(G,v);
    path_remove(curr,G);
}



/*
* Purpose:      Traveling Salesman Problem
*
*               Read an input description of an undirected graph, find its
*               shortest cycle, and print it.
*
*               -h              If present, print a help message and exit.
*               -i filename     If present, read filename instead of stdin.
*               -o filename     If present, write filename instead of stdout.
*               -d              If present, input specifies a directed graph.
*
*               If either of the -i or -o command-line options is repeated,
*               then use the last filename given.
*
* Parameters:   Standard argc, argv.
*
* Returns:      1 on error, 0 otherwise.
*/
int main(int argc, char **argv) {
    bool directed = false;
    char *infile = NULL;
    char *outfile = NULL;
    int n = 0;
    int start = 0;

    int opt;
    while ((opt =getopt(argc,argv, "hi:o:d")) != -1) {
        switch (opt){
        case 'h':
            printf("Usage: tsp [-hd] [-i infile] [-o outfile]\n");
            return 0;
        case 'i':
            infile = optarg;
            break;
        case 'o':
            outfile = optarg;
            break;
        case 'd':
            directed = true;
            break;
        default:
            fprintf(stderr, "Unknown option\n");
            return 1;
        }
    }

    FILE *in = stdin;
    if(infile != NULL) {
        in = fopen(infile, "r");
        if (!in){
            fprintf(stderr, "Failed to open input file\n");
            return 1;
        }
    }


    FILE *out = stdout;
    if(outfile != NULL){
        out  = fopen(outfile, "w");
        if (!out){
            fprintf(stderr, "Failed to open output file\n");
            if (infile) fclose(in);
            return 1;
        }
    }

        //use sscanf
    
    Graph *g = graph_read(in, directed);
    

   
    Path *curr = path_create(n+1);
    Path *shortest = path_create(n+1);

    for (int i = 0; i < n; i++) {
        graph_unvisit_vertex(g, i);
    }

    dfs(g, start, curr, shortest, out);

    if(path_vertices(shortest) == 0){
        fprintf(out, "No path found! Alissa is lost!\n");
    }else {
        fprintf(out, "Alissa starts at:\n");
        path_print(shortest, out, g);
    }

    path_free(&curr);
    path_free(&shortest);
    graph_free(&g);

    if (infile) fclose(in);
    if (outfile) fclose(out);

    return 0;
}

