
/// graph.c
/// Header for the generic graph implementation
/// Brendan Dileo - December 16 2025


#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Defines the Graph struct type
typedef struct Graph {
    // struct LinkedList **adjacency_list;      // Pointer to an array of pointers to linked lists representing the list of adjacent vertices
    int num_vertices;                           // Number of vertices in the graph
} Graph;


#endif