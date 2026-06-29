/*
 * File: dijkstra.c
 * Purpose: Implements Dijkstra's shortest-path algorithm on an undirected,
 *          weighted graph with a fixed number of vertices (VERTEX_NUM = 8).
 *          The program reads interactive commands to incrementally build
 *          the graph and compute single-source shortest distances.
 * Input:  Interactive commands from stdin:
 *         - 'a' <arc_num> <v1> <v2> <info> ... : adds <arc_num> undirected
 *           edges. Each edge is specified by two vertices (v1, v2) and a
 *           positive integer weight (info). The graph accumulates edges.
 *         - 'f' <vertex> : executes Dijkstra's algorithm starting from
 *           <vertex>. The vertex must be in [0, VERTEX_NUM-1].
 *         - 'd' : deletes all existing edges from the graph, resetting it.
 *         - any other character : terminates the program immediately.
 * Output: For each 'f' command, prints three lines to stdout:
 *         "distance:" followed by the computed shortest distances from the
 *         source. Unreachable vertices are represented by INT_MAX.
 *         "path:" followed by the predecessor of each vertex in the
 *         shortest-path tree (-1 for the source or unreachable vertices).
 *         "final:" followed by the finalized status of each vertex (1 if
 *         the shortest distance is finalized, 0 otherwise).
 *         No output is produced for 'a', 'd', or other commands.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define VERTEX_NUM 8

int final[VERTEX_NUM];

int distance[VERTEX_NUM];

int path[VERTEX_NUM];

typedef struct edge_node{
    int info;
    int adjacent_vertex;
    struct edge_node *next_edge;
}edge_node;

typedef struct vertex_node{
    edge_node *first_edge;
}vertex_node;

typedef struct graph{
    vertex_node vertex_list[VERTEX_NUM];
}graph;

graph *init_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_edge(graph *g, int i, int j, int info){
    edge_node *new_node = (edge_node *)malloc(sizeof(edge_node));
    new_node->info = info;
    new_node->adjacent_vertex = i;

    new_node->next_edge = g->vertex_list[j].first_edge;
    g->vertex_list[j].first_edge = new_node;

    new_node = (edge_node *)malloc(sizeof(edge_node));
    new_node->info = info;
    new_node->adjacent_vertex = j;

    new_node->next_edge = g->vertex_list[i].first_edge;
    g->vertex_list[i].first_edge = new_node;
}

void dijkstra(graph *g, int vertex){
    for(int i = 0; i < VERTEX_NUM; i++){
        path[i] = -1;
        distance[i] = INT_MAX;
        final[i] = 0;
    }

    final[vertex] = 1;
    distance[vertex] = 0;
    path[vertex] = -1;

    int current = vertex;

    for(int round = 0; round < VERTEX_NUM - 1; round++){
        //num of vertex minus 1 is round
        for(edge_node *p = g->vertex_list[current].first_edge; p != NULL; 
            p = p->next_edge){
            if(final[p->adjacent_vertex] == 0 
                && distance[p->adjacent_vertex] > distance[current] + p->info){
                distance[p->adjacent_vertex] = distance[current] + p->info;
                path[p->adjacent_vertex] = current;
            }
        }

        int min_dist_vertex = 0;
        int min_dist = INT_MAX;
        for(int i = 0; i <VERTEX_NUM; i++){
            if(final[i] == 0 && distance[i] < min_dist){
                min_dist_vertex = i;
                min_dist = distance[i];
            }
        }

        current = min_dist_vertex;
        final[current] = 1;
    }

    printf("distance:");
    for(int i = 0; i < VERTEX_NUM; i++)
        printf("%d ", distance[i]);

    printf("\npath:");
    for(int i = 0; i < VERTEX_NUM; i++)
        printf("%d ", path[i]);

    printf("\nfinal:");
    for(int i = 0; i < VERTEX_NUM; i++)
        printf("%d ", final[i]);

    printf("\n");
}

void delete_edge(graph *g){
    for(int i = 0; i < VERTEX_NUM; i++){
        edge_node *p = g->vertex_list[i].first_edge;
        edge_node *next = NULL;
        while(p != NULL){
            next = p->next_edge;
            free(p);
            p = next;
        }
    }
    memset(g, 0, sizeof(graph));
}

void delete_graph(graph *g){
    free(g);
}

int main(){
    graph *g = init_graph();
    char choice;
    int v1, v2, info;

    printf("input example:\n");
    printf("a 2 0 1 1 3 4 2: add 2 arcs between 0&1 and 3&4\n");
    printf("             , and 0&1 arc's info is 1, 3&4 arc's info is 2\n");
    printf("f 0: find distance between vertex 0 to other vertex\n");
    printf("d: delete all edges\n");

    while(1){
        scanf(" %c", &choice);
        switch(choice){
            case 'a':
                int arc_num;
                scanf(" %d", &arc_num);
                for(int i = 0; i < arc_num; i++){
                    scanf(" %d %d %d", &v1, &v2, &info);
                    add_edge(g, v1, v2, info);
                }
                break;
            
            case 'f':
                int vertex;
                scanf(" %d", &vertex);
                dijkstra(g, vertex);
                break;

            case 'd':
                delete_edge(g);
                break;

            default:
                delete_edge(g);
                delete_graph(g);
                return 0;
        }
    }
}
