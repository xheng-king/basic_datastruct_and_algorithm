/*
 * File: dijkstra_20260706.c
 * Purpose:
 * Input:
 * Output:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define VERTEX_NUM 8

int distance[VERTEX_NUM];

int final[VERTEX_NUM];

int path[VERTEX_NUM];

typedef struct arc_node{
    int info;
    int tail;
    int head;
    struct arc_node *next_same_tail, *next_same_head;
}arc_node;

typedef struct vertex_node{
    arc_node *first_out;
    arc_node *first_in;
}vertex_node;

typedef struct graph{
    vertex_node vertex_list[VERTEX_NUM];
}graph;

graph *init_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_arc(graph *g, int tail, int head, int info){
    arc_node *new_node = (arc_node *)malloc(sizeof(arc_node));
    new_node->head = head;
    new_node->tail = tail;
    new_node->info = info;
    new_node->next_same_head = g->vertex_list[head].first_in;
    new_node->next_same_tail = g->vertex_list[tail].first_out;

    g->vertex_list[head].first_in = new_node;
    g->vertex_list[tail].first_out = new_node;
}

void dijkstra(graph *g, int source){
    for(int i = 0; i < VERTEX_NUM; i++){
        distance[i] = INT_MAX / 3;
        path[i] = -1;
        final[i] = 0;
    }

    distance[source] = 0;
    path[source] = -1;
    final[source] = 1;

    int current = source;
    for(int i = 1; i < VERTEX_NUM; i++){
        for(arc_node *p = g->vertex_list[current].first_out; p != NULL; p = p->next_same_tail){
            if(final[p->head] == 0 && distance[p->head] > distance[current] + p->info){
                distance[p->head] = distance[current] + p->info;
                path[p->head] = current;
            }
        }
        int min_distance = INT_MAX, min_index;
        for(int j = 0; j < VERTEX_NUM; j++){
            if(final[j] == 0){
                if(min_distance > distance[j]){
                    min_distance = distance[j];
                    min_index = j;
                }
            }
        }
        current = min_index;
        final[current] = 1;
    }
}

int main(){
    graph *g = init_graph();
    int arc_num, tail, head, info, source;

    printf("arc's amount:");
    scanf("%d", &arc_num);
    printf("arc(tail head info):");
    for(int i = 0; i < arc_num; i++){
        scanf(" %d %d %d", &tail, &head, &info);
        add_arc(g, tail, head, info);
    }

    printf("source:");
    scanf(" %d", &source);
    dijkstra(g, source);

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
    
    return 0;
}