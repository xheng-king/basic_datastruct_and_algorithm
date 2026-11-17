/*
 * File: bfs_min_distance_20260714.cpp
 * Purpose: Compute the shortest distances from a single source vertex to all other vertices
 *          in an unweighted directed graph using Breadth-First Search (BFS). The graph
 *          is represented by an adjacency matrix. The results include the distance array,
 *          the predecessor (path) array, and the final visited marker array.
 * Input:  The number of arcs, followed by the arc list (each arc as "tail head"), and
 *         finally the source vertex index. All vertex indices are assumed to be in the
 *         range [0, VERTEX_NUM-1] where VERTEX_NUM is defined as 7.
 * Output: Three lines: the first line prints the distance array (distance from source
 *         to each vertex, with INT_MAX/3 for unreachable vertices), the second line
 *         prints the predecessor array (parent of each vertex in the BFS tree, -1 for
 *         the source and unreachable vertices), and the third line prints the final
 *         visited array (1 if reached, 0 otherwise).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <limits.h>

#define VERTEX_NUM 7

int distance[VERTEX_NUM] = {INT_MAX / 3};
int path[VERTEX_NUM] = {-1};
int final[VERTEX_NUM] = {0};

std::queue<int> my_queue;

typedef struct graph{
    int arc[VERTEX_NUM][VERTEX_NUM]; 
}graph;

graph *init_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(g));
    return g;
}

void add_arc(graph *g, int tail, int head){
    g->arc[tail][head] = 1;
}

void delete_graph(graph *g){
    if(g)
        free(g);
}

void bfs_min_distance(graph *g, int source){
    distance[source] = 0;
    path[source] = -1;
    final[source] = 1;
    my_queue.push(source);
    int current;
    while(!my_queue.empty()){
        current = my_queue.front();
        my_queue.pop();
        for(int i = 0; i < VERTEX_NUM; i++){
            if(g->arc[current][i] == 1 && final[i] == 0){
                distance[i] = distance[current] + 1;
                path[i] = current;
                final[i] = 1;
                my_queue.push(i);
            }
        }
    }
}

int main(){
    int arc_num;
    int head, tail;
    int source;

    graph *g = init_graph();

    printf("arc's num:");
    scanf("%d", &arc_num);

    printf("arcs:");
    for(int i = 0; i < arc_num; i++){
        scanf(" %d %d", &tail, &head);
        add_arc(g, tail, head);
    }

    printf("source:");
    scanf(" %d", &source);
    bfs_min_distance(g, source);

    printf("distance:");
    for(int i = 0; i < VERTEX_NUM; i++){
        printf("%d ", distance[i]);
    }
    printf("\n");

    printf("path:");
    for(int i = 0; i < VERTEX_NUM; i++){
        printf("%d ", path[i]);
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