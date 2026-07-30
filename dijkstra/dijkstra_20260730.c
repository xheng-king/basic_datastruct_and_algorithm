/*
 * File: dijkstra_20260730.c
 * Purpose: Implement Dijkstra's algorithm to compute the shortest paths from a fixed source vertex (vertex 0) 
 *          in a directed weighted graph with exactly 8 vertices. The graph is stored using adjacency lists.
 * Input:   The first line is an integer indicating the number of directed arcs. Then each of the following 
 *          lines contains three integers: tail, head, and weight (info) of an arc. All vertices are numbered 
 *          from 0 to 7 (inclusive).
 * Output:  Three lines are printed:
 *          1. "path:" followed by the predecessor of each vertex ( -1 for the source or unreachable vertices),
 *          2. "dist:" followed by the shortest distance from the source to each vertex (a large value for unreachable),
 *          3. "final:" followed by a flag (1 if finalized, 0 otherwise) for each vertex.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VERTEX_NUM 8

typedef struct arc_node{
    int info;
    int head;
    struct arc_node *next_arc;
}arc_node;

typedef struct vertex_node{
    arc_node *first_arc;
}vertex_node;

typedef struct graph{
    vertex_node vertex_list[VERTEX_NUM];
}graph;

graph *creat_graph(){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void delete_graph(graph *g){
    if(g){
        for(int i = 0; i < VERTEX_NUM; i++){
            arc_node *p = g->vertex_list[i].first_arc, *q;
            while(p!=NULL){
                q = p;
                p = p->next_arc;
                free(q);
            }
        }
        free(g);
    }
}

void add_arc(graph *g, int tail, int head, int info){
    arc_node *new_arc = (arc_node *)malloc(sizeof(arc_node));
    new_arc->head = head;
    new_arc->info = info;
    new_arc->next_arc = g->vertex_list[tail].first_arc;
    g->vertex_list[tail].first_arc = new_arc;
}

int path[VERTEX_NUM];
int dist[VERTEX_NUM];
int final[VERTEX_NUM];

void dijkstra(graph *g, int source){
    for(int i = 0; i < VERTEX_NUM; i++){
        path[i] = -1;
        dist[i] = __INT_MAX__ / 3;
        final[i] = 0;
    }
    dist[source] = 0;
    path[source] = -1;
    final[source] = 1;

    int current = source;

    for(int i = 0; i < VERTEX_NUM - 1; i++){
        for(arc_node *p = g->vertex_list[current].first_arc; 
            p != NULL;
            p = p->next_arc){
                if(final[p->head] == 0 &&
                    dist[current] + p->info < dist[p->head]){
                    dist[p->head] = dist[current] + p->info;
                    path[p->head] = current;
                }
        }
        int min_distance = __INT_MAX__/3;
        int min_index;
        for(int i = 0; i < VERTEX_NUM; i++){
            if(final[i] == 0 && min_distance > dist[i]){
                min_distance = dist[i];
                min_index = i;
            }
        }
        current = min_index;
        final[current] = 1;
    }
}

int main(){
    int tail, head, info;
    graph *g = creat_graph();
    int arc_num;

    printf("input arc's num:");
    scanf("%d", &arc_num);

    printf("input arcs:");
    for(int i = 0; i < arc_num; i++){
        scanf(" %d %d %d", &tail, &head, &info);
        add_arc(g, tail, head, info);
    }

    dijkstra(g, 0);

    printf("path:");
    for(int i = 0; i < VERTEX_NUM; i++){
        printf("%d ", path[i]);
    }
    printf("\n");
    printf("dist:");
    for(int i = 0; i < VERTEX_NUM; i++){
        printf("%d ", dist[i]);
    }
    printf("\n");
    printf("final:");
    for(int i = 0; i < VERTEX_NUM; i++){
        printf("%d ", final[i]);
    }
    printf("\n");

    delete_graph(g);

    return 0;
}