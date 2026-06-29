/*
 * File: floyd_20260627.c
 * Purpose:
 *   Implements Floyd-Warshall algorithm to compute all-pairs shortest paths
 *   in an undirected weighted graph with 8 vertices. The graph is built
 *   interactively by adding edges (arcs) with integer weights. The program
 *   supports displaying the final distance matrix and deleting all edges.
 * Input:
 *   Interactive commands from standard input:
 *     - 'a' <num_edges> followed by <num_edges> triples (v1 v2 weight):
 *         add undirected edges between vertex v1 and v2 with given weight.
 *         Vertices are numbered 0 to 7.
 *     - 'f' : compute and print the all-pairs shortest distance matrix.
 *     - 'd' : delete all edges (clear the graph).
 *     - any other character : terminate the program.
 * Output:
 *   When 'f' is entered, prints the distance matrix with 8 rows, each row
 *   labeled "source i:" followed by 8 integers representing the shortest
 *   distances from vertex i to every other vertex. Unreachable vertices are
 *   shown as 100 (MAX_INFO). Other outputs include prompts for user input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INFO 100

#define VERTEX_NUM 8

typedef struct edge_type{
    int info;
    int adjacent_vertex;
    struct edge_type *next;
}edge_type;

typedef struct vertex_type{
    edge_type *first_edge;
}vertex_type;

typedef struct graph{
    vertex_type vertex_list[VERTEX_NUM];
}graph;

graph *init_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_edge(graph *g, int vertex_i, int vertex_j, int info){
    edge_type *new_edge = (edge_type *)malloc(sizeof(edge_type));
    new_edge->info = info;
    new_edge->adjacent_vertex = vertex_j;
    new_edge->next = g->vertex_list[vertex_i].first_edge;
    g->vertex_list[vertex_i].first_edge = new_edge;

    new_edge = (edge_type *)malloc(sizeof(edge_type));
    new_edge->info = info;
    new_edge->adjacent_vertex = vertex_i;
    new_edge->next = g->vertex_list[vertex_j].first_edge;
    g->vertex_list[vertex_j].first_edge = new_edge;
}

void delete_edge(graph *g){
    for(int i = 0; i < VERTEX_NUM; i++){
        edge_type *current = g->vertex_list[i].first_edge;
        while(current != NULL){
            edge_type *next = current->next;
            free(current);
            current = next;
        }
    }

    for(int i = 0; i < VERTEX_NUM; i++){
        g->vertex_list[i].first_edge = NULL;
    }
}

void delete_graph(graph *g){
    free(g);
}

int find_distance(graph *g, int vertex_i, int vertex_j){
    int distance = MAX_INFO;
    if(vertex_i == vertex_j)
        distance = 0;
    else{
        edge_type *current = g->vertex_list[vertex_i].first_edge;
        while(current != NULL){
            if(current->adjacent_vertex == vertex_j){
                distance = current->info;
                break;
            }
            current = current->next;
        }
    }
    
    return distance;
}

void floyd(graph *g){
    int distance[VERTEX_NUM][VERTEX_NUM];
    for(int i = 0; i < VERTEX_NUM; i++){
        for(int j = 0; j <VERTEX_NUM; j++){
            distance[i][j] = find_distance(g, i, j);
        }
    }
    
    for(int round = 0; round < VERTEX_NUM; round++){
        for(int i = 0; i < VERTEX_NUM; i++){
            for(int j = 0; j < VERTEX_NUM; j++){
                if(distance[i][round] + distance[round][j] < distance[i][j])
                    distance[i][j] = distance[i][round] + distance[round][j];
            }
        }
    }

    for(int i = 0; i < VERTEX_NUM; i++){
        printf("source %d:", i);
        for(int j = 0; j <VERTEX_NUM; j++){
            printf("%d ", distance[i][j]);
        }
        printf("\n");
    }
}

int main(){
    graph *g = init_graph();
    char choice;
    int v1, v2, info;

    printf("input example:\n");
    printf("a 2 0 1 1 3 4 2: add 2 arcs between 0&1 and 3&4\n");
    printf("             , and 0&1 arc's info is 1, 3&4 arc's info is 2\n");
    printf("f: print min-distance matrix\n");
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
                floyd(g);
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
