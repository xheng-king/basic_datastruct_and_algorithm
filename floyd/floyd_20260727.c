/*
 * File: floyd_20260727.c
 * Purpose: Implement Floyd-Warshall algorithm to compute all-pairs shortest paths
 *          in a directed weighted graph with 8 vertices (0 to 7). The graph is
 *          stored as an adjacency matrix, and the result is printed as distance
 *          matrices for each source vertex.
 * Input:  The number of arcs (edges) followed by that many triples, each
 *         consisting of tail (source vertex), head (destination vertex), and
 *         weight (info). Vertices are indexed from 0 to 7. The graph is
 *         directed and weights are positive integers (less than INT_MAX/3).
 * Output: For each vertex i (0..7), prints a line "the distance from i to
 *         other vertexs:" followed by the 8 shortest distances from i to all
 *         vertices j (0..7) in order. If no path exists, the distance remains
 *         as INT_MAX/3 (representing infinity). 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define VERTEX_NUM 8

int dist[VERTEX_NUM][VERTEX_NUM];

typedef struct graph{
    int arc[VERTEX_NUM][VERTEX_NUM];
}graph;

graph *creat_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    for(int i = 0; i < VERTEX_NUM; i++){
        for(int j = 0; j < VERTEX_NUM; j++){
            g->arc[i][j] = INT_MAX / 3;
        }
    }
    for(int i = 0; i < VERTEX_NUM; i++){
        g->arc[i][i] = 0;
    }
    return g;
}

void delete_graph(graph *g){
    if(g != NULL)
        free(g);
}

void add_arc(graph *g, int tail, int head, int info){
    g->arc[tail][head] = info;
}

void floyd(graph *g){
    for(int i = 0; i < VERTEX_NUM; i++){
        for(int j = 0; j < VERTEX_NUM; j++){
            dist[i][j] = g->arc[i][j];
        }
    }
    for(int current = 0; current < VERTEX_NUM; current++){
        for(int i = 0; i < VERTEX_NUM; i++){
            for(int j = 0; j < VERTEX_NUM; j++){
                if((dist[i][current] + dist[current][j]) < dist[i][j])
                    dist[i][j] = dist[i][current] + dist[current][j];
            }
        }
    }
}

int main(){
    int arc_num;
    int tail, head, info;

    graph *g = creat_graph();

    printf("input arcs' num:");
    scanf("%d", &arc_num);

    printf("input arcs:");
    for(int i = 0; i < arc_num; i++){
        scanf(" %d %d %d", &tail, &head, &info);
        add_arc(g, tail, head, info);
    }
    floyd(g);

    for(int i = 0; i < VERTEX_NUM; i++){
        printf("the distance from %d to other vertexs:\n", i);
        for(int j = 0; j < VERTEX_NUM; j++){
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    delete_graph(g);
    return 0;
}